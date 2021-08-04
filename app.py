# utils
import json
from utils.auth.login import login_token, isLogged
from utils.schema.login import loginSchema
from utils.schema.register import registerSchema

# data transfer
from io import BytesIO
from zipfile import ZipFile

# Manejo de archivos
from tempfile import mkdtemp
from os import path, environ

# manipular información 
from base64 import encodebytes, b64decode
from bson.objectid import ObjectId
from bson import json_util
from json import dumps

# Configuración del servidor
from flask import Flask, render_template, request, Response, redirect, session, flash, jsonify, send_file, make_response, after_this_request
from werkzeug.security import generate_password_hash, check_password_hash
from flask_session import Session
from werkzeug.utils import secure_filename

# Librerias de google cloud
from google.cloud import storage
from google.oauth2 import service_account
# from google.api_core import page_iterator
# from google.cloud.storage.bucket import Bucket

# Librerias de Mongodb
from flask_pymongo import PyMongo

# Libreria de tokens
import jwt

# Actualización del tiempo
import datetime

# Manejo de markdown para colorear el code
from markdown import markdown
import markdown.extensions.fenced_code
import markdown.extensions.codehilite
from pygments.formatters import HtmlFormatter

if(path.exists('./.env')):
    # Variables de entorno en modo desarrollo 
    from dotenv import load_dotenv
    load_dotenv()


USER_DB = environ["USER_DB"]
PASSWORD_DB = environ["PASSWORD_DB_KEY"]

# Firebase credentials
private_key = environ['private_key'].replace('\\n', '\n').replace('\\\\n', '\\n')
credentials = {
    'type': environ['type'],
    'project_id': environ['project_id'],
    'private_key_id': environ['private_key_id'],
    'private_key': private_key,
    'client_email': environ['client_email'],
    'client_id': environ['client_id'],
    'auth_uri': environ['auth_uri'],
    'token_uri': environ['token_uri'],
    'auth_provider_x509_cert_url': environ['auth_provider_x509_cert_url'],
    'client_x509_cert_url': environ['client_x509_cert_url']
}
 
config = {
    'apiKey': environ['apiKey'],
    'authDomain': environ['authDomain'],
    'databaseURL': environ['databaseURL'],
    'storageBucket': environ['storageBucket'],
    'serviceAccount': credentials
}
STORAGE_BUCKET = config['storageBucket']

app = Flask(__name__)

app.secret_key = environ['SESSION_KEY']
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config['SESSION_PERMANENT'] = True  # La cookie no se guarda para siempre
app.config['SESSION_TYPE'] = 'filesystem'
app.config['SESSION_COOKIE_SECURE'] = True
app.config['MONGO_URI'] = f'mongodb+srv://{USER_DB}:{PASSWORD_DB}@cluster0.73uuw.mongodb.net/cs50xni?retryWrites=true&w=majority'
Session(app)
mongo = PyMongo(app)
# Initialize Firestore DB
credentials_gc = service_account.Credentials.from_service_account_info(credentials)
client = storage.Client(credentials=credentials_gc)
bucket = client.get_bucket(STORAGE_BUCKET)

ALLOWED_EXTENSIONS = {'txt', 'c', 'js', 'py', 'html', 'h', 'png', 'jpg', 'jpeg', 'gif'}
IMAGE_MIMETYPE = {'image/png', 'image/jpeg', 'image/jpg'}
INVALID_FILENAME = {':', '*', '/', '"', '?', '>', '|', '<'}

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[-1].lower() in ALLOWED_EXTENSIONS

# Cada vez que se crea algo, se añade el tiempo en que se creo
def timestamp():
    return {"created_at": datetime.datetime.now(datetime.timezone.utc), "updated_at": datetime.datetime.now(datetime.timezone.utc)}

def get_user_and_project(user_id):
    user_cursor = mongo.db.users.aggregate([
        {
            '$lookup': {
                "from": 'projects',
                "localField": '_id',
                "foreignField": 'users_id',
                "as": 'projects'
            }
        },
        { "$match": { "_id": ObjectId(user_id) } }
    ])

    return list(user_cursor)[0]

# Es una herramienta sorpresa que nos ayudara más tarde
# def _item_to_value(iterator, item):
#     return item

# def list_directories(bucket_name, prefix):
#     if prefix and not prefix.endswith('/'):
#         prefix += '/'

#     extra_params = {
#         "projection": "noAcl",
#         "prefix": prefix,
#         "delimiter": '/'
#     }

#     path = "/b/" + bucket_name + "/o"

#     iterator = page_iterator.HTTPIterator(
#         client=client,
#         api_request=client._connection.api_request,
#         path=path,
#         items_key='prefixes',
#         item_to_value=_item_to_value,
#         extra_params=extra_params,
#     )
#     return [x for x in iterator]
# directories = list_directories(STORAGE_BUCKET, route)

# Lista los directorios de las rutas especificadas
def list_dir(route):
    data = []
    info = {
        'files': [],
        'path': None,
        'isListed': 0
    }
    list_ = bucket.list_blobs(prefix=route)
    # https://stackoverflow.com/questions/63743826/google-datastore-iterator-already-started-how-to-work-with-these-iterators
    class Padding: # Reelleno para que itere todos los elementos +1
        name = '/'
        files: None
        path=""

    data_arr = [Padding]

    for blob in list_:
        data_arr.insert(-1, blob)
    for dirs in data_arr:
        routes = dirs.name.split('/')
        filename = routes.pop(-1) # Si no termina con / quiere decir que no es una carpeta
        path_dir = '/'.join(map(str, routes)) + '/'
        existFolder = False

        for search in data:
            if path_dir == search['path']:
                search['files'].append(filename)
                existFolder = True
        if(existFolder):
            continue

        if(filename == '' or info['path'] != path_dir):
            if info['path'] != path_dir and info['path'] != None and len(info['files']) > 0:
                data.append(info.copy())
                info['files'] = []

            info['path'] = path_dir
        if(filename):
            (info['files']).append(filename)

    return data

def get_file_data(path_file, file, file_ext):
    if file_ext != 'png' and file_ext !='jpg' and file_ext != 'jpeg':
        code = bucket.blob(f'{path_file}{file}').download_as_string().decode('utf-8')
        code_md = f'```{file_ext}\n{code}\n```'

        md_template_string = markdown.markdown(
        code_md, extensions=["fenced_code", "codehilite"]
        )
        formatter = HtmlFormatter(style="monokai", full=True, cssclass="codehilite")

        css_string = formatter.get_style_defs()

        return {
            "code": {    
                "html": f'{md_template_string}',
                "css": f'{css_string}',
            },
            'file_ext': file_ext,
            'type': 'code'
        }
    else:
        code = bucket.blob(f'{path_file}{file}').download_as_string()
        image = encodebytes(code)
        info = {
            'file_ext': file_ext,
            'type': 'image'
        }
        return {
            'code': None,
            'image': dumps(image, default=json_util.default),
            'info': info,
        }


# Si el nombre tiene un carácter extraño
def change_folder_name(string):
    for invalid_name in INVALID_FILENAME:
        if string.find(invalid_name) > -1:
            string = string.replace(invalid_name, '_')
    return string

def path_join(*argv):
    return ('/'.join(map(str, argv))) + '/'

def create_zip(path, depth):
    memory_file = BytesIO()
    blobs = bucket.list_blobs(prefix=path)

    with ZipFile(memory_file, 'w') as zf:
        for blob in blobs:
            binary = blob.download_as_string()
            name = blob.name.split('/', depth)[depth]
            zf.writestr(name, binary)
    memory_file.seek(0)
    return memory_file

def delete_project_storage(path):
    blobs = bucket.list_blobs(prefix=path)
    for blob in blobs:
        blob.delete()


@app.before_request
def before_request():
    app.permanent_session_lifetime = datetime.timedelta(hours=12);
    if(not '/static/' in request.path):
        @after_this_request
        def request_after(resp):
            token = request.cookies.get('USER_TOKEN')
            if not token is None:
                try:
                    get_info = jwt.decode(token, environ['KEY_JWT'], algorithms=['HS256'])
                except jwt.ExpiredSignatureError:
                    resp.set_cookie('USER_TOKEN', expires=0)
                    resp.set_cookie('username', expires=0)
                    resp.set_cookie('email', expires=0)
                    resp.set_cookie('user_id', expires=0)
                    resp.set_cookie('user_image', expires=0)
                    return resp
                except jwt.InvalidTokenError:
                    resp.set_cookie('USER_TOKEN', expires=0)
                    resp.set_cookie('username', expires=0)
                    resp.set_cookie('email', expires=0)
                    resp.set_cookie('user_id', expires=0)
                    resp.set_cookie('user_image', expires=0)
                    return resp
            return resp


@app.route('/')
def home():
    user = {}
    validation = isLogged('USER_TOKEN')
    if validation.get('success'):
        user_info = validation.get('info')
        user_id = ObjectId(user_info.get('user_id'))
        user = mongo.db.users.find_one({"_id": user_id})

    return render_template('index.html', user=user)


@app.route('/login', methods=['GET', 'POST'])
def login():
    admin_token = isLogged('ADMIN_TOKEN')
    if admin_token['success']:
        return redirect('/admin/profile')
    
    user_token = isLogged('USER_TOKEN')

    if user_token['success']:
        return redirect('/profile')    
    
    if request.method == 'POST':
        email = request.form.get('email')
        password = request.form.get('password')
            
        validation = loginSchema(email, password)

        if not validation['success']:
            return jsonify(validation)
        user = mongo.db.users.find_one({
            'email': email
        })

        if not user:
            return jsonify({'success': False,'error': 'El usuario no existe'})
        if not check_password_hash(user["password"], password):
            return jsonify({'success': False,'error': 'Correo o contraseña incorrecta'})

        resp = make_response(jsonify({"success": True, 'token': 'valid'}))
        resp.set_cookie('USER_TOKEN', login_token(user['username'], email, user['_id'].__str__()))
        resp.set_cookie('username', user['username'])
        resp.set_cookie('email', email)
        resp.set_cookie('user_id', user['_id'].__str__())
        resp.set_cookie('user_image', user['cover'])

        return resp


    return render_template('auth/login/index.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    admin_token = isLogged('ADMIN_TOKEN')
    if admin_token['success']:
        return redirect('/admin/profile')
    
    user_token = isLogged('USER_TOKEN')
    if user_token['success']:
        return redirect('/profile')
            
    if(request.method == 'POST'):
        email = request.form.get("email")
        username = request.form.get("username")
        password = generate_password_hash(request.form.get(
            "password"), method="sha256", salt_length=10 # se encripta con sha256 10 veces
        )

        validation = registerSchema(email, username, password)

        if not validation['success']:
            return jsonify(validation)

        find_user = mongo.db.users.find_one({
            '$or': [
                { "email": email },
                { "username": username }
            ]
        }) # busca un usuario donde uno de esos dos campos tenga ese valor
        if find_user != None:
            return jsonify({"success": True, 'message': f'{username} ya existe'})

        file = request.files['image']
        if file.filename != '':
            if file.mimetype in IMAGE_MIMETYPE:
                mimetype = file.mimetype
                extension_image = file.filename.split('.')[-1]
                image_data = file.read()
            else:
                flash('error mimetype')
                return redirect('/register')

        else:
            image = open('./static/images/user_default_logo.png', 'rb').read()
            mimetype = 'image/png'
            extension_image = 'png'
            image_data = image

        user_id = ObjectId()
        image_url = 'user_image/' + user_id.__str__() + f'.{extension_image}'

        blob = bucket.blob(image_url)
        blob.upload_from_string(image_data, content_type=mimetype)
        blob.make_public()

        user = mongo.db.users.insert( # inserta un usuario
            {"_id": user_id, "username": username, "password": password, "email": email, "cover": blob.public_url, **timestamp()})

        resp = make_response(jsonify({"success": True, 'message': 'Usuario creado con éxito'}))

        resp.set_cookie('USER_TOKEN', login_token(username, email, user.__str__()))
        resp.set_cookie('username', username)
        resp.set_cookie('email', email)
        resp.set_cookie('user_id', user.__str__())
        resp.set_cookie('user_image', blob.public_url)

        return resp

    return render_template('auth/register/index.html')

@app.route('/profile')
def profile():
    session_exist = isLogged('USER_TOKEN')
    if session_exist['success']:
        user_id = (session_exist['info'])['user_id']
        find_user = mongo.db.users.find({'_id':ObjectId(user_id)}) 

        if find_user:
            user = get_user_and_project(user_id)
        else:
            return redirect('/logout')
        return render_template('user/profile/index.html', user=user)
    else:
        flash("You are not logged in. Please log in to see the profile.")
        return redirect('/login')


@app.route('/update-account/<user_id>', methods=['PUT'])
def update_profile(user_id):
    user_payload = isLogged('USER_TOKEN')
    user_info = user_payload.get('info')

    if(user_info['user_id'] == user_id):
        username = request.form.get('username')
        email = request.form.get('email')
        password = request.form.get('password')
        password_confirm = request.form.get('password_confirm')

        findUsers_cursor = mongo.db.users.find({
            '$or': [
                { "email": email },
                { "username": username }
        ]})
        findUser = list(findUsers_cursor)

        if len(findUser) > 1:
            return 'el usuario ya existe'

        if not check_password_hash((findUser[-1])['password'], password_confirm):
            return redirect('/profile')
        #se validan las entradas
        newInfo = {}
        if len(username) > 0:
            newInfo['username'] = username
        if len(email) > 3:
            newInfo['email'] = email

        if len(password) > 4:
            newInfo['password'] = generate_password_hash(password, method="sha256", salt_length=10)
        newInfo['updated_at'] = datetime.datetime.now()

        file = request.files['perfil']
        if file.filename != '':
            if file.mimetype in IMAGE_MIMETYPE:
                mimetype = file.mimetype
                ext = file.filename.split('.')[-1]
                image = file.read()
                blob = bucket.blob(f'user_image/{user_id}.{ext}')
                blob.upload_from_string(image, content_type=mimetype)
                blob.make_public()
                newInfo['cover'] = blob.public_url
            else:
                flash('error mimetype')
                return redirect('/register')

        deleteBeforeImage = bucket.blob(request.cookies.get('user_image').split('/', 4)[-1])
        deleteBeforeImage.delete()
        
        mongo.db.projects.update_many({'users_id': ObjectId(user_info['user_id'])}, { '$set': { 'author': newInfo['username'] }})
        user = mongo.db.users.find_one_and_update( { '_id': ObjectId(user_id) }, {
            '$set': newInfo
        })

        data = dumps(user,default=json_util.default)
        resp = make_response(data)
        resp.set_cookie('USER_TOKEN', login_token(newInfo['username'], user['email'], user['_id'].__str__()))
        resp.set_cookie('username', newInfo['username'])
        resp.set_cookie('email', user['email'])
        resp.set_cookie('user_id', user.__str__())
        resp.set_cookie('user_image', blob.public_url)
        return resp
    else:
        flash('No puedes cambiar la info de otro usuario >:v')

    return {}

@app.route('/add-project', methods=['GET', 'POST'])
def addProject():
    user_payload = isLogged('USER_TOKEN')
    user_info = user_payload.get('info')

    if not user_payload['success']:
        return redirect('/login')

    if request.method == 'POST':
        if user_payload['success'] and user_info['user_id']:
            print(request.files)
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

            image_url = 'project_image/' + project_id.__str__() + '.' + image.name.split('.')[-1]

            upload_image = bucket.blob(image_url)
            upload_image.upload_from_string(image.read(), content_type=image.content_type)
            upload_image.make_public()

            mongo.db.projects.insert({"_id": project_id, "project_name": project_name, 'author': user_info.get('username'), "description": description, 'modo': modo, "users_id": ObjectId(user_info.get('user_id')), "path": directory, **timestamp(), "image": upload_image.public_url, "files": file_names, "github": github_url})
            
            return jsonify({'success': True, 'message': 'Proyecto creado'})
        else:
            return jsonify({'success': False, 'message': 'No tienes permisos'})

    return render_template('user/addCode.html')


@app.route('/make-public/<project_id>')
def make_public(project_id):
    user = isLogged('USER_TOKEN')
    if user['success']:
        user_info = user['info']
        is_owner = user_info['user_id'] == mongo.db.projects.find_one({'_id': ObjectId(project_id)})['users_id']
        if is_owner:
            project = mongo.db.projects.find_one_and_update({'_id': ObjectId(project_id)}, {'$set': {'public': True}})

            return redirect('/profile')
        else:
            return 'no tienes permisos'
    else:
        flash('You are not logged in')
        return redirect('/login')


@app.route('/download-project/<project_id>', methods=['GET'])
def download_project(project_id):
    project = mongo.db.projects.find_one({ '_id': ObjectId(project_id)})
    project_name = project['project_name']

    memory_file = create_zip(project['path'], 3)
    return send_file(memory_file, download_name=f'{project_name}.zip')

# Ruta para descargar los codigos predeterminados en modo texto
@app.route('/download-static_project/<project_id>', methods=['GET'])
def download_static_project(project_id):
    project = mongo.db.static_projects.find_one({ '_id': ObjectId(project_id)})
    # print(project)
    project_title = project['program_title']
    memory_file = create_zip(project['path'], 3)

    return send_file(memory_file, attachment_filename=f'{project_title}.zip', as_attachment=True)

@app.route('/download-example/<example_id>')
def download_examples(example_id):
    example = mongo.db.ejemplos.find_one({ '_id': ObjectId(example_id)})
    example_title = example['example_name']
    memory_file = create_zip(example['path'], 1)
    return send_file(memory_file, attachment_filename=f'{example_title}.zip', as_attachment=True)


@app.route('/delete-project', methods=['DELETE'])
def delete_project():
    user_payload = isLogged('USER_TOKEN')
    user_info = user_payload.get('info')
    if user_info.get('user_id'):
        project_id = ObjectId(request.form.get('id'))
        find_project = mongo.db.projects.find_one({'_id': project_id})

        if find_project['users_id'] == ObjectId(user_info.get('user_id')):
            project = mongo.db.projects.find_one_and_delete({ 'users_id': ObjectId(user_info.get('user_id')), '_id': project_id}, {'_id': False, 'image': False, 'users_id': False})
        else:
            return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

        if project is None:
            return jsonify({'success': False, 'message': 'No existe el proyecto', "error": 404})

        delete_project_storage(project['path'])
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
                'modo': doc['modo'],
                'public': doc['public'],
                'image': doc['image'],
                'files': doc['files'],
                'github': doc['github']
            })
        # data = dumps(data_list,default=json_util.default, ensure_ascii=False).encode('utf-8')

        return jsonify({ 'data': data_list, 'delete_info': project }), 200
    else:
        return jsonify({'success': False, 'message': 'No tienes permisos', "error": 403})

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

    return render_template('show_project/index.html', project_info=db_project, directory=directory, name=project_name, download_URI=download_URI)
# Ruta para ver los proyectos en modo grafico
@app.route('/static_projects/graphic_mode/<project_name>/', methods=['GET', 'POST'])
def show_project_graphic(project_name):
    db_project = mongo.db.static_projects.find_one({ 'program_title': project_name })
    project_path = db_project['path']

    if db_project is None:
        return render_template('404.html'), 404

    if request.method == 'POST':
        file = (request.get_json())['filename']
        path_file = (request.get_json())['path']
        file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
        return jsonify(get_file_data(path_file, file, file_ext))

    # Muestra los directorios del proyecto correspondiente para ver los codigos
    directory = list_dir(route=project_path)
    download_URI = f'/download-static_project/{db_project["_id"]}'

    return render_template('show_static_project/index.html', project_info=db_project, directory=directory, name=project_name, download_URI=download_URI, type="graphic mode")

@app.route('/static_projects/<project_name>/', methods=['GET', 'POST'])


# Ruta para ver los proyectos predeterminados en modo texto
@app.route('/static_projects/text_mode/<project_name>/', methods=['GET', 'POST'])
def show_static_project(project_name):

    # Trae el proyecto correspondiente al nombre de la db
    db_project = mongo.db.static_projects.find_one({ 'program_title': project_name })

    if db_project is None:
        return render_template('404.html'), 404

    project_path = db_project['path']

    if request.method == 'POST':
        file = (request.get_json())['filename']
        path_file = (request.get_json())['path']
        file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
        return jsonify(get_file_data(path_file, file, file_ext))

    # Muestra los directorios del proyecto correspondiente para ver los codigos
    directory = list_dir(route=project_path)
    download_URI = f'/download-static_project/{db_project["_id"]}'
    
    return render_template('show_static_project/index.html', project_info=db_project, directory=directory, name=project_name, download_URI=download_URI, type="text mode")
  
#para la parte de documentacion
@app.route('/examples/basicos')
def documentacion():  
    db_documentation = mongo.db.documentation.find({'type':'document'})
    return render_template("pdf/documentacion.html",db_documentation=db_documentation)
# Ruta para ver ejemplos
@app.route('/example/<ejemplo_name>/', methods=['GET', 'POST'])
def show_ejemplo(ejemplo_name):

    # Trae el ejemplo correspondiente al nombre de la db
    db_example = mongo.db.ejemplos.find_one({ 'example_name': ejemplo_name })

    if db_example is None:
        return render_template('404.html'), 404

    example_path = db_example['path']

    if request.method == 'POST':

        file = (request.get_json())['filename']
        path_file = (request.get_json())['path']
        file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c

        return jsonify(get_file_data(path_file, file, file_ext))

    # Muestra los directorios del proyecto correspondiente para ver los codigos
    directory = list_dir(route=example_path)
    download_URI = f'/download-example/{db_example["_id"]}'

    return render_template('show_ejemplo/index.html', example_info=db_example, directory=directory, name=ejemplo_name, download_URI=download_URI, type="text mode")


@app.route('/tools')
def installers():
    return render_template("installers/tools.html")


@app.route('/about-us')
def about():
    return render_template("about us/about.html")


@app.route('/examples/intro')
def text_mode():

    db_project = mongo.db.static_projects.find({'mode': 'text_mode'})
    db_project_user = mongo.db.projects.find({"modo": "text_mode"})

    if db_project is None:
        return render_template('404.html'), 404

    return render_template("text_mode/text.html", db_project=db_project, db_project_user=db_project_user)

#Cuando se consulte en el modo grafico
@app.route('/examples/node')
def graphic_mode():
    db_project = mongo.db.static_projects.find({'mode': 'graphic_mode'})
    db_project_user = mongo.db.projects.find({"modo": "graphic_mode"})

    return render_template("graphic_mode/graphic.html", db_project=db_project, db_project_user=db_project_user)

@app.route('/logout')
def logout():
    resp = make_response(redirect('/login'))
    resp.set_cookie('USER_TOKEN', expires=0)
    resp.set_cookie('username', expires=0)
    resp.set_cookie('email', expires=0)
    resp.set_cookie('user_id', expires=0)
    flash(f'Session closed') 
    return resp

@app.route('/admin', methods=['GET'])
def admin_panel():
    cookie = session.get('admin_id')
    if cookie is None:
        flash('Inicia sesión para entrar al panel')
        return redirect('/admin/login')
    else:
        admin_user = mongo.db.admins.find_one({ '_id': cookie })
        get_users = list(mongo.db.users.find({}))
        if admin_user is None:
            flash('No se encontro el administrador')
            return redirect('/admin/login')
        return render_template('admin/panel.html', users= get_users)

@app.route('/admin/login', methods=['GET', 'POST'])
def login_admin():
    if session.get('user_id'):
        session.clear()
    if session.get('admin_id'):
        return redirect('/admin')
    if request.method == 'POST':
        get_admin = mongo.db.admins.find_one(
            {"email": request.form.get("email")})
        if not get_admin:
            return redirect('/admin/login')
        # contraseña_super_compleja
        # admin@codeland.com
        if check_password_hash(get_admin["password"], request.form.get('password')) == False:
            return redirect('/admin/login')

        session['admin_id'] = get_admin['_id']
        session['adminname'] = get_admin['admin_name']
        return redirect('/admin')
    return render_template('admin/login.html')

@app.route('/admin/update_user/<user_id>', methods=['PUT'])
def update_user(user_id):
    if session.get('admin_id') and session.get('user_id') is None:
        username = request.form.get('username')
        email = request.form.get('email')
        password = request.form.get('password')

        print(username, email, password)
        findUsers_cursor = mongo.db.users.find({
            '$or': [
                { "email": email },
                { "username": username }
        ]})
        findUser = list(findUsers_cursor)

        if len(findUser) > 1:
            return 'el usuario ya existe'

        newInfo = {}
        if len(username) > 0:
            newInfo['username'] = username
        if len(email) > 3:
            newInfo['email'] = email

        if len(password) > 4:
            newInfo['password'] = generate_password_hash(password, method="sha256", salt_length=10)
        newInfo['updated_at'] = datetime.datetime.now()

        file = request.files['perfil']
        if file.filename != '':
            if file.mimetype in IMAGE_MIMETYPE:
                mimetype = file.mimetype
                image = encodebytes(file.read())
                newInfo['perfil'] = image
                newInfo['contentType'] = mimetype
            else:
                flash('error mimetype')
                return redirect('/register')

        user = mongo.db.users.find_one_and_update( { '_id': ObjectId(user_id) }, {
            '$set': newInfo
        })

        data = dumps(user,default=json_util.default)
        
        return data
    else:
        flash('Acceso denegado :/')
        return redirect('/admin/login')

@app.route('/admin/delete_user/<user_id>', methods=['DELETE'])
def delete_user(user_id):
    if session.get('admin_id') and session.get('user_id') is None:
        user = mongo.db.users.find_one_and_delete({ '_id': ObjectId(user_id) })
        return {
            "user": dumps(user,default=json_util.default)
        }
    else:
        flash('Acceso denegado >:v')
        return redirect('/admin/login')


@app.route('/google5e97d84d9d35c069.html')
def googleSearchConsole():
    return render_template("google5e97d84d9d35c069.html")


@app.route('/dirs', methods=['GET'])
def getDirs():
    datas = []
    code = list_dir()
    datas.append(code)
    codigo = dumps(code, default=json_util.default, ensure_ascii=False).encode('utf-8')
    
    return Response(codigo, content_type='application/json; charset=utf-8')


@app.route('/zip', methods=['GET'])
def zipDownload():
    memory_file = BytesIO()
    blobs = bucket.list_blobs(prefix='static_projects/')

    with ZipFile(memory_file, 'w') as zf:
        for blob in blobs:
            binary = blob.download_as_string()
            zf.writestr(blob.name, binary)
    memory_file.seek(0)
    return send_file(memory_file, download_name='zip.zip')

@app.route('/download-gc', methods=['GET', 'POST'])
def download_google():
    if request.method == 'POST':
        files = request.files.getlist('files')
        for file in files:
            filename = file.filename
            data = (file.stream.read()).decode('utf-8')
            blob = bucket.blob('documentacion/' + filename)
            blob.upload_from_string(data, content_type = file.content_type)
        # file = bucket.blob('josue.png')
        # file.make_public()
        # file.download_to_filename('filename.png')
    return 'ta bien'

# @app.route('/prueba', methods=['GET'])
# def prueba():
    # storage_user = default_app.storage.bucket(name='gs://codeland-dcd2d.appspot.com')
    # storage_user = default_app.storage()
    # storage_random = storage_fb.child("documentacion/cuento.c").get_url(None)

    # gcs_file = bucket.get_blob('josue.png')
    # blob = bucket.blob('static_projects/')
    # blob.upload_from_string('', content_type='application/x-www-form-urlencoded;charset=UTF-8')
    # folders = bucket.list_blobs(None, prefix='static_project/')

    # folder = bucket.blob('/static_project/graphic_mode/')
    # folder_2 = bucket.blob('static_projects/')
    # print(folders.path)
    # print(folders.max_results)
    # for folder_ref in folders:
    #     print(folder_ref)
    # Util
    # https://stackoverflow.com/questions/59829188/how-rename-folder-in-firebase-storage-android-studio
    # https://stackoverflow.com/questions/41075100/move-rename-folder-in-google-cloud-storage-using-nodejs-gcloud-api?noredirect=1&lq=1
    # https://stackoverflow.com/questions/38601548/how-to-move-files-with-firebase-storage
    # bucket.copy_blob(folder, bucket, '/copia/')

    # return send_file(BytesIO(gcs_file.download_as_string()), mimetype='image/jpg')
@app.route("/publicProject/<projectID>")
def publicProjects(projectID): 
    update = mongo.db.projects.update_one({"_id":ObjectId(projectID)},{"$set":{
        "public": True
    }})
    return jsonify({"success":True})


@app.errorhandler(404)
def page_not_found(_):
    # note that we set the 404 status explicitly
    return render_template('404.html'), 404

if __name__ == '__main__':
    if environ['FLASK_ENV'] == 'development':
        app.run(debug=True)
    else:
        app.run(debug=False)


# https://stackoverflow.com/questions/37074977/how-to-get-list-of-folders-in-a-given-bucket-using-google-cloud-api :0
# https://stackoverflow.com/questions/583791/is-it-possible-to-generate-and-return-a-zip-file-with-app-engine creara el zip
# https://stackoverflow.com/questions/41865214/how-to-serve-an-image-from-google-cloud-storage-using-python-flask
# https://stackoverflow.com/questions/38658417/create-blob-from-url-in-gae-using-python
# https://cloud.google.com/appengine/docs/flexible/python/using-cloud-storage
# https://cloud.google.com/storage/docs/json_api/v1/objects/copy