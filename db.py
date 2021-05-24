from models.user import Users
from mongoengine import connect
from mongoengine import *
from dotenv import dotenv_values

def database():
    ENV_AUTH = dotenv_values(".env")
    USER = ENV_AUTH["USER_DB"]
    PASSWORD = ENV_AUTH["PASSWORD_DB_KEY"]

    connect(host=f"mongodb+srv://{USER}:{PASSWORD}@cluster0.73uuw.mongodb.net/cs50xni?retryWrites=true&w=majority")

database()
# data = Users(name="test", email="test@gmail.com", password="221412")
# data.save()
data=Users.objects(name="test").update_one(name="no test")