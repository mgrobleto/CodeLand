from flask import Flask, render_template, request, redirect, session, flash
import flask
from werkzeug.security import generate_password_hash, check_password_hash
from flask_session import Session
from flask_pymongo import PyMongo
from bson.objectid import ObjectId
from dotenv import dotenv_values
from tempfile import mkdtemp
import datetime

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

    return render_template('login/index.html')

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

        user = mongo.db.users.insert( # inserta un usuario
            {"username": username, "password": password, "email": email, "created_at": datetime.datetime.now(datetime.timezone.utc), "updated_at": datetime.datetime.now(datetime.timezone.utc)})
        session['user_id'] = user

        return redirect('/')

    return render_template('register/index.html')

@app.route('/logout')
def logout():
    session.clear()
    flash("Session closed")
    return redirect('/')

if __name__ == '__main__':
    app.run(debug=True)
