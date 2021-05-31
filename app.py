from io import BytesIO
from logging import info
from os import path, makedirs, listdir, walk
from shutil import rmtree
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
            if request.files['image'].mimetype != 'image/png' or 'image/jpeg' or 'image/jpg':
                flash('error mimetype')
                return redirect('/register')
            mimetype = request.files['image'].mimetype
            image = request.files['image'].read()
            image = encodebytes(image)
        else:
            image = open('./static/images/user_default_logo.png', 'rb').read()
            mimetype = 'image/png'
            image = encodebytes(image)

        user = mongo.db.users.insert( # inserta un usuario
            {"username": username, "password": password, "email": email, **timestamp(), "perfil": image, "contentType": mimetype})
        session['user_id'] = user

        return redirect('/profile')

    return render_template('auth/register/index.html')

@app.route('/profile')
def profile():
    if session.get('user_id') == None:
        flash("You are not logged in. Please log in to see the profile.")
        return redirect('/login')

    user_id = ObjectId(session.get('user_id'))
    user = get_user_and_project(user_id)

    return render_template('user/profile/index.html', user=user)

@app.route('/add-project', methods=['GET', 'POST'])
def addProject():
    if request.method == 'POST':
        if session.get('user_id') != None:
            user = mongo.db.users.find_one({ '_id':  ObjectId(session.get('user_id'))})
            if 'files' not in request.files:
                flash('No file')
                return redirect('/add-project')

            files = request.files.getlist('files')
            title = request.form.get('title')
            description = request.form.get('description')
            image = request.files['image'].read()
            file_names = []
            directory = path.join('.', 'project', user['username'], title)
            
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

            mongo.db.projects.insert({ "title": title, 'author': user['username'], "description": description, "users_id": user['_id'], "path": directory, **timestamp(), "image": encodebytes(image)})
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

@app.route('/project/<username>/<project_name>/', methods=['GET', 'POST'])
def show_project(username, project_name):
    project_path = path.join('.', 'project', username, project_name)
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

@app.route('/logout')
def logout():
    session.clear()
    flash("Session closed")
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
