from os import path, getcwd, makedirs, listdir
from flask import Flask, render_template, request, redirect, session, flash, jsonify
from werkzeug.security import generate_password_hash, check_password_hash
from flask_session import Session
from flask_pymongo import PyMongo
from bson.objectid import ObjectId
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

ALLOWED_EXTENSIONS = {'txt', 'c', '.js', '.py', '.html', 'pdf', 'png', 'jpg', 'jpeg', 'gif'}
def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[1].lower() in ALLOWED_EXTENSIONS

# Cada vez que se crea algo, se añade el tiempo en que se creo
def timestamp():
    return {"created_at": datetime.datetime.now(datetime.timezone.utc), "updated_at": datetime.datetime.now(datetime.timezone.utc)}


@app.route('/')
def home():
    user = {}
    if session.get('user_id'):
        user_id = ObjectId(session.get('user_id'))
        user = mongo.db.users.find_one({"_id": user_id})

    return render_template('index.html', user=user)


@app.route('/login', methods=['GET', 'POST'])
def login():
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
        print(email)
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

@app.route('/upload', methods=['POST'])
def upload():
    if request.method == 'POST':
        image = request.files['image'].read()
        print(type(image))
        byte = encodebytes(image)
        mongo.db.test.insert(
            { "image": image }
        )
        return jsonify({ "image": byte})

@app.route('/profile')
def profile():
    if session.get('user_id') == None:
        flash("You are not logged in. Please log in to see the profile.")
        return redirect('/login')

    user_id = ObjectId(session.get('user_id'))
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
    user = list(user_cursor)[0]

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
            directory = path.join(getcwd(), 'project', user['username'], title)
            
            if path.exists(directory) is False:
                print('directorio creado')
                makedirs(directory)
            else:
                flash('project already exist')
                return redirect('/add-project')

            print(path.exists(directory))
            for file in files:
                filename = file.filename
                file_names.append(filename)
                file.save(path.join(directory, filename))
            mongo.db.projects.insert({ "title": title, "path": directory, "users_id": ObjectId(session.get('user_id')), "image": encodebytes(image), **timestamp(), "description": description})
            return redirect('/profile')
        else:
            flash('You are not logged in')
            return redirect('/login')
    return render_template('user/addCode.html')

@app.route('/project/<username>/<project_name>/', methods=['GET', 'POST'])
def show_project(username, project_name):
    project_path = path.join(getcwd(), 'project', username, project_name)
    if request.method == 'POST':
        file = (request.get_json())['filename']
        # print(path.join(project_path, file['filename']))
        file_ext = file.split('.')[1]
        code = open(path.join(project_path, file)).read()
        code_md = f'```{file_ext}\n{code}\n```'

        md_template_string = markdown.markdown(
        code_md, extensions=["fenced_code", "codehilite"]
        )
        formatter = HtmlFormatter(style="emacs", full=True, cssclass="codehilite")

        css_string = formatter.get_style_defs()
        md_css_string = "<style>" + css_string + "</style>"
        md_template = md_css_string + md_template_string

        return jsonify({
            "info": f'{md_template}'
        })
        
    directory = listdir(project_path)
    return render_template('show_project/index.html', directory=directory, name=project_name)

@app.route('/logout')
def logout():
    session.clear()
    flash("Session closed")
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
