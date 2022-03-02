from bson.objectid import ObjectId

from flask import render_template, redirect, jsonify, request, flash, make_response
from werkzeug.utils import secure_filename
from services.fragments.fragment_action import get_fragments
from services.storage.files_action import delete_file
from services.user.auth import isLogged

from services.fragments import add_fragment, find_fragment, delete_fragment, get_fragments
from services.user import update_user
from services.storage import add_folder, add_file, list_dir, get_file_data, delete_file, delete_fragment_storage

from utils import timestamp

import random

def path_join(*argv):
    return ('/'.join(map(str, argv))) + '/'

def allowed_file(filename):
    ALLOWED_EXTENSIONS = {'txt', 'c', 'js', 'py', 'html', 'h', 'png', 'jpg', 'jpeg', 'gif', 'docx', 'doc'}
    return '.' in filename and \
           filename.rsplit('.', 1)[-1].lower() in ALLOWED_EXTENSIONS

def fragments(app):
    # Ruta para ver los proyectos en modo texto
    @app.route('/fragment/<username>/<fragment_name>/', methods=['GET', 'POST'])
    def show_fragment(username, fragment_name):
        db_fragment = find_fragment({ 'author': username, 'fragment_name': fragment_name })
        if db_fragment is None:
            flash('El proyecto no existe')
            return render_template('404.html'), 404

        fragment_path = db_fragment['path']
        if request.method == 'POST':
            file = (request.get_json())['filename']
            path_file = (request.get_json())['path']
            file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
            
            return jsonify(get_file_data(path_file, file, file_ext))

        directory = list_dir(route=fragment_path)
        download_URI = f'/download-fragment/{db_fragment["_id"]}'
        resp = make_response(render_template('show_fragment/index.html', fragment_info=db_fragment, directory=directory, name=fragment_name, download_URI=download_URI))
        resp.set_cookie('fragment_id', db_fragment["_id"].__str__())
        resp.set_cookie('fragment_path', fragment_path)
        # set content-type

        return resp

    @app.route('/add-fragment', methods=['GET', 'POST'])
    def fragment_page():
        user_payload = isLogged('USER_TOKEN')
        user_info = user_payload.get('info')
        
        if not user_payload['success']:
            return redirect('/login')
        if request.method == 'POST':
            if user_payload['success'] and user_info['user_id']:
                # print(request.files)
                if 'files' not in request.files:
                    return jsonify({'success': False, 'message': 'No file'})

                files = request.files.getlist('files')
                fragment_name = request.form.get('fragmentName')
                description = request.form.get('description')


                if fragment_name is None or fragment_name == '':
                    return jsonify({'success': False, 'message': 'El nombre del fragment no puede estar vacio'})
                
                if description is None or description == '':
                    return jsonify({'success': False, 'message': 'La descripcion del fragment no puede estar vacia'})

                # print(session.get('user_id'))
                directory = path_join('fragment', user_info.get('user_id'), fragment_name)

                # Valida si el proyecto ya existe
                new_folder = add_folder(directory)

                if not new_folder:
                    return jsonify({'success': False, 'message': 'El fragment ya existe'})

                for file in files:
                    if file and allowed_file(file.filename):
                        filename = secure_filename(file.filename)
                        add_file(directory + filename, file, file.content_type)

                fragment_id = ObjectId()

                # random number between 1,2,3
                random_number = random.randint(1, 3)

                add_fragment({"_id": fragment_id, "fragment_name": fragment_name, 'author': user_info.get('username'), "description": description, "users_id": ObjectId(user_info.get('user_id')), "path": directory, **timestamp(), "image": f'static/images/fragments{random_number}.png'})
                update_user({'_id': ObjectId(user_info.get('user_id'))}, {'inc': {'fragments_count': 1}})
                
                return jsonify({'success': True, 'message': 'Proyecto creado'})

        return render_template('user/add-fragment.html')

    @app.route('/fragment/<fragment_id>', methods=['POST', 'PUT', 'DELETE'])
    def addFile(fragment_id):
        user_payload = isLogged('USER_TOKEN')
        if user_payload.get('success'):
            fragment_id = ObjectId(fragment_id)
            fragment = find_fragment({ '_id': fragment_id })
            if fragment is None:
                return jsonify({'success': False, 'message': 'No existe el proyecto', "error": 404})
            else:
                if request.method == 'POST':
                    file = request.files['file']
                    path = request.form.get('path') + secure_filename(file.filename)
                    blob = add_file(path, file, file.content_type)
                    # print(path)
                    # print(blob)
                    if blob == None:
                        return jsonify({'success': False, 'message': 'Ya existe un archivo con este nombre', "error": 403})

                    return jsonify({"success": True, "message": "Se ha subido el archivo", "path": path, "filename": file.filename})

                if request.method == 'DELETE':
                    path = request.form.get('filename')
                    blob = delete_file(path)
                    if blob is None:
                        return jsonify({'success': False, 'message': 'No existe el archivo', "error": 404})
                    else:
                        return jsonify({'success': True, 'message': 'Se ha borrado el archivo', "path": path})
        else:
            return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

    
    @app.route('/is-owner/fragment/<fragment_id>')
    def isOwnerFragment(fragment_id):
        # GET fragment_id and verify if the user is the owner in mongodb
        user_payload = isLogged('USER_TOKEN')
        if not user_payload['success']:
            return jsonify({'success': False, 'message': 'No tienes permisos'})

        user_info = user_payload.get('info')
        fragment = find_fragment({'_id': ObjectId(fragment_id)})
        if fragment and fragment.get('users_id') == ObjectId(user_info.get('user_id')):
            return jsonify({'success': True, 'message': 'Es tu proyecto'})
        else:
            return jsonify({'success': False, 'message': 'No es tu proyecto'})

    @app.route('/delete-fragment', methods=['DELETE'])
    def _delete_fragment():
        user_payload = isLogged('USER_TOKEN')
        user_info = user_payload.get('info')
        if user_info.get('user_id'):
            fragment_id = ObjectId(request.form.get('id'))
            _find_fragment = find_fragment({'_id': fragment_id})

            if _find_fragment['users_id'] == ObjectId(user_info.get('user_id')):
                fragment = delete_fragment({ 'users_id': ObjectId(user_info.get('user_id')), '_id': fragment_id})
                update_user({'_id': ObjectId(user_info.get('user_id'))}, {'inc': {'fragments_count': -1}})
            else:
                return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

            if fragment is None:
                return jsonify({'success': False, 'message': 'No existe el fragment', "error": 404})

            delete_fragment_storage(fragment['path'])

            # delete image in bucket
            image_ext = fragment['image'].split('/')[-1].split('.')[-1]

            data_cursor = get_fragments({ 'users_id': ObjectId(user_info.get('user_id'))})
            data_list = []
            for doc in data_cursor:
                current_fragment_id = doc['_id'].__str__()
                user_id = doc['users_id'].__str__()
                data_list.append({
                    '_id': current_fragment_id,
                    'user_id': user_id,
                    'fragment_name': doc['fragment_name'],
                    'author': doc['author'],
                    'description': doc['description'],
                    'image': doc['image'],
                    'path': doc['path'],
                })
            # data = dumps(data_list,default=json_util.default, ensure_ascii=False).encode('utf-8')
            keys = {'_id', 'image', 'users_id'}
            return jsonify({'success': True, 'data': data_list, 'delete_info': {x: fragment[x] for x in fragment if x not in keys  } }), 200
        else:
            return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

