from flask import Flask, render_template
from flask_debugtoolbar import DebugToolbarExtension
from flask_session import Session
from flask_mongoengine import MongoEngine
from dotenv import dotenv_values
from flask_mongoengine import BaseQuerySet
import datetime

ENV_AUTH = dotenv_values(".env")
USER_DB = ENV_AUTH["USER_DB"]
PASSWORD_DB= ENV_AUTH["PASSWORD_DB_KEY"]

app = Flask(__name__)
# init database
# app.config['MONGODB_SETTINGS'] = {
#     "db": "cs50xni",
#     "username": ,
#     "password": ENV_AUTH["PASSWORD_DB_KEY"],
#     "host": "mongodb+srv://"
# }
print("Users: " + PASSWORD_DB)
app.config['MONGODB_HOST'] = f"mongodb+srv://CS50:{PASSWORD_DB}@cluster0.73uuw.mongodb.net/cs50xni?retryWrites=true&w=majority"
app.config['DEBUG_TB_PANELS'] = ['flask_mongoengine.panels.MongoDebugPanel']
app.config['SESSION_PERMANENT'] = False
app.config['SESSION_KEY_PREFIX'] = ENV_AUTH['SESSION_KEY']
app.config['SECRET_KEY'] = ENV_AUTH['SESSION_KEY']

db = MongoEngine(app)
toolbar = DebugToolbarExtension(app)


class Users(db.Document):
    name=db.StringField(required=True)
    email=db.StringField(required=True)
    password=db.StringField(required=True)
    createdAt=db.DateTimeField()
    updatedAt=db.DateTimeField(default=datetime.datetime.now())
    meta= {'collection': 'users', 'strict': False, 'queryset_class': BaseQuerySet}

    def save(self, *args, **kwargs):
        if not self.createdAt:
            self.createdAt = datetime.datetime.now()
        self.updatedAt = datetime.datetime.now()
        return super(Users, self).save(*args, **kwargs)

@app.route('/', methods= ['GET'])
def home():
    return render_template('index.html')

@app.route('/login', methods= ['GET', 'POST'])
def login():
    user = Users.objects.get_or_404(name="Miguel")
    return render_template('login/index.html', user=user)

if __name__ == '__main__':
    app.run(debug=True)
