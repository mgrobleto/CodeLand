import base64
from flask import Flask, render_template, request, redirect, session, flash, jsonify
from werkzeug.security import generate_password_hash, check_password_hash
from flask_session import Session
from flask_pymongo import PyMongo
from bson.objectid import ObjectId
from dotenv import dotenv_values
from tempfile import mkdtemp
import datetime
from base64 import encodebytes

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
            
        if find_user != None:
            flash(f"{username} already exist")
            return redirect('/register')
            
        if not username or not password or not email:
            flash("username or password is empty")
            return redirect('/register')
        
        if request.files['image'].filename != '':
            mimetype = request.files['image'].mimetype
            image = request.files['image'].read()
            image = encodebytes(image)
        else:
            image = open('./static/images/user_default_logo.png', 'rb').read()
            mimetype = 'image/png'
            image = encodebytes(image)

        user = mongo.db.users.insert( # inserta un usuario
            {"username": username, "password": password, "email": email, "created_at": datetime.datetime.now(datetime.timezone.utc), "updated_at": datetime.datetime.now(datetime.timezone.utc), "perfil": image, "contentType": mimetype})

        session['user_id'] = user

        return redirect('/')

    return render_template('auth/register/index.html')

@app.route('/upload', methods=['POST'])
def upload():
    if request.method == 'POST':
        image = request.files['image'].read()
        byte = encodebytes(image)
        mongo.db.test.insert(
            { "image": byte }
        )
        return jsonify(image=image)

@app.route('/profile')
def profile():
    if session.get('user_id') == None:
        flash("You are not logged in. Please log in to see the profile.")
        return redirect('/login')

    user_id = ObjectId(session.get('user_id'))
    user = mongo.db.users.find_one({"_id": user_id})
    return render_template('user/profile/index.html', data=None, user=user)

@app.route('/add-project')
def addProject():
    return render_template('user/addCode.html')

@app.route('/logout')
def logout():
    session.clear()
    flash("Session closed")
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
