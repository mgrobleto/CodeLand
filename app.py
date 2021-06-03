from io import BytesIO
from os import path, makedirs, listdir, walk
from shutil import rmtree
from time import strftime
from zipfile import ZipFile
from flask import Flask, render_template, request, redirect, session, flash, jsonify, send_file
from werkzeug.security import generate_password_hash, check_password_hash
from flask_session import Session
from werkzeug.utils import secure_filename
from flask_pymongo import PyMongo
from bson.objectid import ObjectId
from bson import json_util
from json import dumps
from dotenv import dotenv_values
from tempfile import mkdtemp
import datetime
from base64 import encodebytes
from markdown import markdown
import markdown.extensions.fenced_code
import markdown.extensions.codehilite
from pygments.formatters import HtmlFormatter

ENV_AUTH = dotenv_values(".env")
USER_DB = ENV_AUTH["USER_DB"]
PASSWORD_DB = ENV_AUTH["PASSWORD_DB_KEY"]

app = Flask(__name__)

app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config['SESSION_PERMANENT'] = False  # La cookie no se guarda para siempre
app.secret_key = ENV_AUTH['SESSION_KEY']
app.config['MONGO_URI'] = f'mongodb+srv://CS50:{PASSWORD_DB}@cluster0.73uuw.mongodb.net/cs50xni?retryWrites=true&w=majority'
app.config['SESSION_TYPE'] = 'filesystem'
Session(app)
mongo = PyMongo(app)

ALLOWED_EXTENSIONS = {'txt', 'c', 'js', 'py', 'html', 'h', 'png', 'jpg', 'jpeg', 'gif'}
IMAGE_MIMETYPE = ['image/png', 'image/jpeg', 'image/jpg']

def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

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

@app.route('/')
def home():
    user = {}
    if session.get('user_id'):
        user_id = ObjectId(session.get('user_id'))
        user = mongo.db.users.find_one({"_id": user_id})

    return render_template('index.html', user=user)


@app.route('/login', methods=['GET', 'POST'])
def login():
    if session.get('user_id') != None:
        return redirect('/profile')
    if request.method == 'POST':
        get_user = mongo.db.users.find_one(
            {"email": request.form.get("email")})
        if not get_user:
            return redirect('/login')
        if not check_password_hash(get_user["password"], request.form.get('password')):
            return redirect('/login')

        session['user_id'] = get_user['_id']
        session['username'] = get_user['username']
        return redirect('/')

    return render_template('auth/login/index.html')

@app.route('/register', methods=['GET', 'POST'])
def register():
    if session.get('user_id') != None:
        return redirect('/profile')
    if(request.method == 'POST'):
        email = request.form.get("email")
        username = request.form.get("username")
        password = generate_password_hash(request.form.get(
            "password"), method="sha256", salt_length=10 # se encripta con sha256 10 veces
        )

        find_user = mongo.db.users.find_one({
            '$or': [
                { "email": email },
                { "username": username }
            ]
        }) # busca un usuario donde uno de esos dos campos tenga ese valor
        if find_user != None:
            flash(f"{username} already exist")
            return redirect('/register')
            
        if not username or not password or not email:
            flash("username or password is empty")
            return redirect('/register')
        
        if request.files['image'].filename != '':
            if any(request.files['image'].mimetype == mimetype for mimetype in IMAGE_MIMETYPE):
                mimetype = request.files['image'].mimetype
                image = request.files['image'].read()
                image = encodebytes(image)
            else:
                flash('error mimetype')
                return redirect('/register')

        else:
            image = open('./static/images/user_default_logo.png', 'rb').read()
            mimetype = 'image/png'
            image = encodebytes(image)

        user = mongo.db.users.insert( # inserta un usuario
            {"username": username, "password": password, "email": email, **timestamp(), "perfil": image, "contentType": mimetype})
        session['user_id'] = user
        session['username'] = username

        return redirect('/profile')

    return render_template('auth/register/index.html')

@app.route('/profile')
def profile():
    if session.get('user_id') == None:
        flash("You are not logged in. Please log in to see the profile.")
        return redirect('/login')

    user_id = session.get('user_id')
    user = get_user_and_project(user_id)

    print(user['created_at'].strftime('%d %b %Y'))
    return render_template('user/profile/index.html', user=user)

@app.route('/update-account/<user_id>', methods=['PUT'])
def update_profile(user_id):
    if(session.get('user_id') == ObjectId(user_id)):
        username = request.form.get('username')
        email = request.form.get('email')

        findUsers_cursor = mongo.db.users.find({
            '$or': [
                { "email": email },
                { "username": username }
            ]})
        findUser = list(findUsers_cursor)
        for field in findUser:
            print(field['username'])
        print(len(findUser))
        if len(findUser) > 1:
            print('El usuario ya existe')
            return 'el usuario ya existe'
        
        user = mongo.db.users.find_one_and_update( { '_id': ObjectId(user_id) }, {
            '$set': {
            'username': username,
            'email': email,
            'password': generate_password_hash(request.form.get('password'), method="sha256", salt_length=10),
            'updated_at': datetime.datetime.now()
        }
        })
        data = dumps(user,default=json_util.default)
        return data
    else:
        flash('No puedes cambiar la info de otro usuario >:v')

    return {}

@app.route('/add-project', methods=['GET', 'POST'])
def addProject():
    if request.method == 'POST':
        if session.get('user_id') != None:
            user = mongo.db.users.find_one({ '_id':  ObjectId(session.get('user_id'))})
            if 'files' not in request.files:
                flash('No file')
                return redirect('/add-project')

            modo = request.form.get('modo')
            if not (modo != 'text_mode' or modo != 'graphic_mode'):
                flash('Ahh sos retroll')
                return redirect('/add-project')
            files = request.files.getlist('files')
            title = request.form.get('title')
            description = request.form.get('description')
            image = request.files['image'].read()
            file_names = []
            directory = path.join('.', 'project', user['username'], modo, title)
            
            if path.exists(directory) is False:
                makedirs(directory)
            else:
                flash('project already exist')
                return redirect('/add-project')

            for file in files:
                if file and allowed_file(file.filename):
                    filename = secure_filename(file.filename)
                    file_names.append(filename)
                    file.save(path.join(directory, filename))

            mongo.db.projects.insert({ "title": title, 'author': user['username'], "description": description, 'modo': modo, "users_id": user['_id'], "path": directory, **timestamp(), "image": encodebytes(image)})
            return redirect('/profile')
        else:
            flash('You are not logged in')
            return redirect('/login')
    return render_template('user/addCode.html')

@app.route('/download-project/<project_id>', methods=['GET'])
def download_project(project_id):
    project = mongo.db.projects.find_one({ '_id': ObjectId(project_id)})
    project_title = project['title']
    memory_file = BytesIO()
    with ZipFile(memory_file, 'w') as zf:
        for root, dirs, files in walk(project['path']):
            for file in files:
                zf.write(path.join(root, file),
                        path.relpath(path.join(root, file), 
                                        path.join(project['path'], '..')))
    # send_file
    memory_file.seek(0)

    return send_file(memory_file, attachment_filename=f'{project_title}.zip', as_attachment=True)


# Ruta para descargar los codigos predeterminados en modo texto
@app.route('/download-static_project/<project_id>', methods=['GET'])
def download_static_project(project_id):

    project = mongo.db.static_projects.find_one({ '_id': ObjectId(project_id)})
    project_title = project['program_title']
    memory_file = BytesIO()
    
    with ZipFile(memory_file, 'w') as zf:
        for root, dirs, files in walk(project['path']):
            for file in files:
                zf.write(path.join(root, file),
                        path.relpath(path.join(root, file), 
                                        path.join(project['path'], '..')))
    # send_file
    memory_file.seek(0)

    return send_file(memory_file, attachment_filename=f'{project_title}.zip', as_attachment=True)

@app.route('/delete-project', methods=['DELETE'])
def delete_project():
    if session.get('user_id'):
        project_id = ObjectId(request.form.get('id'))
        project = mongo.db.projects.find_one_and_delete({ 'users_id': ObjectId(session.get('user_id')), '_id': project_id}, {'_id': False, 'image': False, 'users_id': False})
        if project is None:
            flash('El proyecto no existe')
            return redirect('/profile')
        rmtree(project['path'])
        data_cursor = mongo.db.projects.find({ 'users_id': ObjectId(session.get('user_id'))})
        data_list = [doc for doc in data_cursor]
        data = dumps(data_list,default=json_util.default)
        return { 'data': data, 'delete_info': project }
    else:
        flash('You are not logged in')
        return redirect('login')

# Ruta para ver los proyectos en modo texto
@app.route('/project/<username>/<project_name>/', methods=['GET', 'POST'])
def show_project(username, project_name):
    project_path = path.join('.', 'project', username, 'text_mode', project_name)
    if request.method == 'POST':
        file = (request.get_json())['filename']
        file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
        if file_ext != 'png' and file_ext !='jpg' and file_ext != 'jpeg':
            code = open(path.join(project_path, file), 'r', encoding='utf-8').read()
            code_md = f'```{file_ext}\n{code}\n```'

            md_template_string = markdown.markdown(
            code_md, extensions=["fenced_code", "codehilite"]
            )
            formatter = HtmlFormatter(style="monokai", full=True, cssclass="codehilite")

            css_string = formatter.get_style_defs()
            md_css_string = "<style>" + css_string + "</style>"
            
            md_template = md_css_string + md_template_string

            return jsonify({
                "info": f'{md_template}',
                'file_ext': file_ext,
                'type': 'code'
            })
        else:
            code = open(path.join(project_path, file), 'rb').read()
            image = encodebytes(code)
            json_image = dumps(image,default=json_util.default)
            
            return jsonify({
                'info': json_image,
                'type': 'binary'
            })
        
    directory = listdir(project_path)
    return render_template('show_project/index.html', directory=directory, name=project_name, username=username)
# Ruta para ver los proyectos en modo grafico
@app.route('/project/<username>/graphic_mode/<project_name>/', methods=['GET', 'POST'])
def show_project_graphic(username, project_name):
    project_path = path.join('.', 'project', username, 'graphic_mode', project_name, 'BIN')
    if request.method == 'POST':
        file = (request.get_json())['filename']
        file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
        if file_ext != 'png' and file_ext !='jpg' and file_ext != 'jpeg':
            code = open(path.join(project_path, file), 'r', encoding='utf-8').read()
            code_md = f'```{file_ext}\n{code}\n```'

            md_template_string = markdown.markdown(
            code_md, extensions=["fenced_code", "codehilite"]
            )
            formatter = HtmlFormatter(style="monokai", full=True, cssclass="codehilite")

            css_string = formatter.get_style_defs()
            md_css_string = "<style>" + css_string + "</style>"
            
            md_template = md_css_string + md_template_string

            return jsonify({
                "info": f'{md_template}',
                'file_ext': file_ext,
                'type': 'code'
            })
        else:
            code = open(path.join(project_path, file), 'rb').read()
            image = encodebytes(code)
            json_image = dumps(image,default=json_util.default)
            
            return jsonify({
                'info': json_image,
                'type': 'binary'
            })
        
    directory = listdir(project_path)
    return render_template('show_project/index.html', directory=directory, name=project_name, username=username)


# Ruta para ver los proyectos predeterminados en modo texto
@app.route('/static_projects/text_mode/<project_name>/', methods=['GET', 'POST'])
def show_static_project(project_name):

    # Trae el proyecto correspondiente al nombre de la db
    db_project = mongo.db.static_projects.find_one({ 'program_title': project_name })

    #project_path = path.join('.', 'static_projects', 'text_mode' , project_name)
    print(db_project)
    if db_project is None:
        return render_template('404.html'), 404

    project_path = db_project['path']

    if request.method == 'POST':
        file = (request.get_json())['filename']
        path_file = (request.get_json())['path']
        file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
        if file_ext != 'png' and file_ext !='jpg' and file_ext != 'jpeg':
            code = open(path.join(path_file, file), 'r', encoding='utf-8').read()
            code_md = f'```{file_ext}\n{code}\n```'

            md_template_string = markdown.markdown(
            code_md, extensions=["fenced_code", "codehilite"]
            )
            formatter = HtmlFormatter(style="monokai", full=True, cssclass="codehilite")

            css_string = formatter.get_style_defs()
            md_css_string = "<style>" + css_string + "</style>"
            
            md_template = md_css_string + md_template_string

            return jsonify({
                "info": f'{md_template}',
                'file_ext': file_ext,
                'type': 'code'
            })

        else:
            code = open(path.join(path_file, file), 'rb').read()
            image = encodebytes(code)
            json_image = dumps(image,default=json_util.default)
            
            return jsonify({
                'info': json_image,
                'type': 'binary'
            })
    
    # Muestra los directorios del proyecto correspondiente para ver los codigos
    directory = {}

    for root, _, files in walk(project_path):
        for file in files:
            directory[root] = files
            
    return render_template('show_static_project/index.html', directory=directory, name=project_name, id=db_project['_id'])
    

# Ruta para ver ejemplos
@app.route('/ejemplos/<ejemplo_name>/', methods=['GET', 'POST'])
def show_ejemplo(ejemplo_name):
    ejemplo_path = path.join('.', 'ejemplos', ejemplo_name)
    if request.method == 'POST':
        file = (request.get_json())['filename']
        file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
        if file_ext != 'png' and file_ext !='jpg' and file_ext != 'jpeg':
            code = open(path.join(ejemplo_path, file), 'r', encoding='utf-8').read()
            code_md = f'```{file_ext}\n{code}\n```'

            md_template_string = markdown.markdown(
            code_md, extensions=["fenced_code", "codehilite"]
            )
            formatter = HtmlFormatter(style="monokai", full=True, cssclass="codehilite")

            css_string = formatter.get_style_defs()
            md_css_string = "<style>" + css_string + "</style>"
            
            md_template = md_css_string + md_template_string

            return jsonify({
                "info": f'{md_template}',
                'file_ext': file_ext,
                'type': 'code'
            })
        else:
            code = open(path.join(ejemplo_path, file), 'rb').read()
            image = encodebytes(code)
            json_image = dumps(image,default=json_util.default)
            
            return jsonify({
                'info': json_image,
                'type': 'binary'
            })
        
    directory = listdir(ejemplo_path)
    return render_template('show_ejemplo/index.html', directory=directory, name=ejemplo_name)

@app.route('/about-us')
def about():
    return render_template("about us/about.html")

@app.route('/examples/intro')
def text_mode():
    """user = {}
    if session.get('user_id'):
        user_id = ObjectId(session.get('user_id'))
        user = get_user_and_project(user_id)"""

    db_project = mongo.db.static_projects.find({'mode': 'text_mode'})

    if db_project is None:
        return render_template('404.html'), 404

    return render_template("text_mode/text.html", db_project=db_project)

#Cuando se consulte en el modo grafico
@app.route('/examples/node')
def graphic_mode():
    user = {}
    if session.get('user_id'):
        user_id = ObjectId(session.get('user_id'))
        user = get_user_and_project(user_id)

    return render_template("graphic_mode/graphic.html", user=user)

@app.route('/logout')
def logout():
    session.clear()
    flash("Session closed")
    return redirect('/')

@app.errorhandler(404)
def page_not_found(e):
    # note that we set the 404 status explicitly
    return render_template('404.html'), 404

if __name__ == '__main__':
    app.run(debug=True)
