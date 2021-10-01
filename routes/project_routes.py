from bson.objectid import ObjectId

from libs import Cloud_Storage, Mongodb

from flask import request, flash, jsonify, render_template, make_response, redirect
from werkzeug.utils import secure_filename

from services.project import get_file_data, list_dir, delete_project_storage

from services.user.auth import isLogged

from utils import timestamp

def allowed_file(filename):
    ALLOWED_EXTENSIONS = {'txt', 'c', 'js', 'py', 'html', 'h', 'png', 'jpg', 'jpeg', 'gif'}
    return '.' in filename and \
           filename.rsplit('.', 1)[-1].lower() in ALLOWED_EXTENSIONS

def path_join(*argv):
    return ('/'.join(map(str, argv))) + '/'

IMAGE_MIMETYPE = {'image/png', 'image/jpeg', 'image/jpg'}

def project(app):
    mongo = Mongodb().client
    bucket = Cloud_Storage().bucket
    # Ruta para ver los proyectos en modo texto
    @app.route('/project/<username>/<project_name>/', methods=['GET', 'POST'])
    def show_project(username, project_name):
        db_project = mongo.db.projects.find_one({ 'author': username, 'project_name': project_name })
        if db_project is None:
            flash('El proyecto no existe')
            return render_template('404.html'), 404

        project_path = db_project['path']
        if request.method == 'POST':
            file = (request.get_json())['filename']
            path_file = (request.get_json())['path']
            file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
            return jsonify(get_file_data(path_file, file, file_ext))

        directory = list_dir(route=project_path)
        download_URI = f'/download-project/{db_project["_id"]}'
        resp = make_response(render_template('show_project/index.html', project_info=db_project, directory=directory, name=project_name, download_URI=download_URI))
        resp.set_cookie('project_id', db_project["_id"].__str__())
        resp.set_cookie('project_path', project_path)
        # set content-type

        return resp

    
    @app.route('/project/<project_id>', methods=['POST', 'PUT', 'DELETE'])
    def addFileOrFolder(project_id):
        user_payload = isLogged('USER_TOKEN')
        if user_payload.get('success'):
            project_id = ObjectId(project_id)
            project = mongo.db.projects.find_one({ '_id': project_id })
            if project is None:
                return jsonify({'success': False, 'message': 'No existe el proyecto', "error": 404})
            else:
                if request.method == 'PUT':
                    # print(request.form.get('folder-path'))
                    # print(request.form.get('folder-name'))
                    path = request.form.get('folder-path') + request.form.get('folder-name') + '/'
                    blob = bucket.blob(path)
                    blob.upload_from_string('', content_type='application/x-www-form-urlencoded;charset=UTF-8')
                    
                    return jsonify({'success': True, 'message': 'Todo Bien c:'})


                if request.method == 'POST':
                    file = request.files['file']
                    path = request.form.get('path') + file.filename
                    blob = bucket.blob(path)
                    # print(path)
                    # print(blob)
                    if blob.exists():
                        return jsonify({'success': False, 'message': 'Ya existe un archivo con este nombre', "error": 403})
                    else:
                        if file and allowed_file(file.filename):
                            blob.upload_from_file(file, content_type=file.content_type)

                    return jsonify({"success": True, "message": "Se ha subido el archivo", "path": path, "filename": file.filename})

                if request.method == 'DELETE':
                    path = request.form.get('filename')
                    blob = bucket.blob(path)
                    if blob.exists():
                        blob.delete()
                        return jsonify({'success': True, 'message': 'Se ha borrado el archivo', "path": path})
                    else:
                        return jsonify({'success': False, 'message': 'No existe el archivo', "error": 404})
        else:
            return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

    @app.route('/projects/<mode>/<filter>')
    def filterProjects(mode, filter):
        if(filter == 'user'):
            data_list = []
            projects = mongo.db.projects.find({
                'mode': mode
            })
            for doc in projects:
                data_list.append({
                    'project_name': doc['project_name'],
                    'author': doc['author'],
                    'description': doc['description'],
                    'mode': doc['mode'],
                    'image': doc['image'],
                })
        if(filter == 'default'):
            data_list = []
            static_projects = mongo.db.static_projects.find({
                'mode': mode
            })
            projects = mongo.db.projects.find({
                'mode': mode
            })

            for doc in static_projects:
                data_list.append({
                    'program_title': doc['program_title'],
                    'mode': doc['mode'],
                    'image': doc['image_route'],
                })

        if(filter == 'all'):
            data_list = {
                'default': [],
                'user': []
            }
            static_projects = mongo.db.static_projects.find({
                'mode': mode
            })
            projects = mongo.db.projects.find({
                'mode': mode
            })
            for doc in projects:
                data_list['user'].append({
                    'project_name': doc['project_name'],
                    'mode': doc['mode'],
                    'image': doc['image'],
                    'author': doc['author'],
                })
            for doc in static_projects:
                data_list['default'].append({
                    'program_title': doc['program_title'],
                    'mode': doc['mode'],
                    'image': doc['image_route'],
                })

        return jsonify({'success': True, 'message': 'Todo Bien c:', 'data': data_list})
    
    @app.route('/delete-project', methods=['DELETE'])
    def delete_project():
        user_payload = isLogged('USER_TOKEN')
        user_info = user_payload.get('info')
        if user_info.get('user_id'):
            project_id = ObjectId(request.form.get('id'))
            find_project = mongo.db.projects.find_one({'_id': project_id})

            if find_project['users_id'] == ObjectId(user_info.get('user_id')):
                project = mongo.db.projects.find_one_and_delete({ 'users_id': ObjectId(user_info.get('user_id')), '_id': project_id})
                mongo.db.users.update_one({'_id': ObjectId(user_info.get('user_id'))}, {'$inc': {'projects_count': -1}})
            else:
                return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

            if project is None:
                return jsonify({'success': False, 'message': 'No existe el proyecto', "error": 404})

            delete_project_storage(project['path'])

            # delete image in bucket
            image_ext = project['image'].split('/')[-1].split('.')[-1]
            bucket.blob(f'project_image/{project["_id"]}.{image_ext}').delete()

            data_cursor = mongo.db.projects.find({ 'users_id': ObjectId(user_info.get('user_id'))})
            data_list = []
            for doc in data_cursor:
                current_project_id = doc['_id'].__str__()
                user_id = doc['users_id'].__str__()
                data_list.append({
                    '_id': current_project_id,
                    'user_id': user_id,
                    'project_name': doc['project_name'],
                    'author': doc['author'],
                    'description': doc['description'],
                    'mode': doc['mode'],
                    'image': doc['image'],
                    'files': doc['files'],
                    'github': doc['github']
                })
            # data = dumps(data_list,default=json_util.default, ensure_ascii=False).encode('utf-8')
            keys = {'_id', 'image', 'users_id'}
            return jsonify({ 'data': data_list, 'delete_info': {x: project[x] for x in project if x not in keys  } }), 200
        else:
            return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

    
    @app.route('/add-project', methods=['GET', 'POST'])
    def addProject():
        user_payload = isLogged('USER_TOKEN')
        user_info = user_payload.get('info')

        if not user_payload['success']:
            return redirect('/login')

        if request.method == 'POST':
            if user_payload['success'] and user_info['user_id']:
                # print(request.files)
                if 'files' not in request.files:
                    flash('No file')
                    return jsonify({'success': False, 'message': 'No file'})

                modo = request.form.get('project_mode')
                if not (modo != 'text_mode' or modo != 'graphic_mode'):
                    return jsonify({'success': False, 'message': 'El modo no existe'})
                    
                files = request.files.getlist('files')
                project_name = request.form.get('projectName')
                description = request.form.get('description')
                github_url = request.form.get('github_url')

                image = request.files['image']
                file_names = []
                # print(session.get('user_id'))
                directory = path_join('project', user_info.get('user_id'), modo, project_name)

                # Valida si el proyecto ya existe
                if not bucket.blob(directory).exists():
                    blob = bucket.blob(directory)
                    blob.upload_from_string('', content_type='application/x-www-form-urlencoded;charset=UTF-8')

                else:
                    return jsonify({'success': False, 'message': 'El proyecto ya existe'})

                for file in files:
                    if file and allowed_file(file.filename):
                        filename = secure_filename(file.filename)
                        if file.mimetype in IMAGE_MIMETYPE:
                            data = file.stream.read()
                        else:
                            data = (file.stream.read()).decode('utf-8')
                        blob = bucket.blob(directory + filename)
                        blob.upload_from_string(data, content_type = file.content_type)
                        file_names.append(filename)

                project_id = ObjectId()

                image_url = 'project_image/' + project_id.__str__() + '.' + image.filename.split('.')[-1]

                upload_image = bucket.blob(image_url)
                upload_image.upload_from_string(image.read(), content_type=image.content_type)
                upload_image.make_public()

                mongo.db.projects.insert({"_id": project_id, "project_name": project_name, 'author': user_info.get('username'), "description": description, 'mode': modo, "users_id": ObjectId(user_info.get('user_id')), "path": directory, **timestamp(), "image": upload_image.public_url, "files": file_names, "github": github_url})
                mongo.db.users.update_one({'_id': ObjectId(user_info.get('user_id'))}, {'$inc': {'projects_count': 1}})
                
                return jsonify({'success': True, 'message': 'Proyecto creado'})
            else:
                return jsonify({'success': False, 'message': 'No tienes permisos'})

        return render_template('user/addCode.html')

    @app.route('/is-owner/<project_id>')
    def isOwner(project_id):
        # GET project_id and verify if the user is the owner in mongodb
        user_payload = isLogged('USER_TOKEN')
        if not user_payload['success']:
            return jsonify({'success': False, 'message': 'No tienes permisos'})

        user_info = user_payload.get('info')
        project = mongo.db.projects.find_one({'_id': ObjectId(project_id)})
        if project and project.get('users_id') == ObjectId(user_info.get('user_id')):
            return jsonify({'success': True, 'message': 'Es tu proyecto'})
        else:
            return jsonify({'success': False, 'message': 'No es tu proyecto'})
