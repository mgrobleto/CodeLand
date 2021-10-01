from libs import Mongodb
from bson.objectid import ObjectId

def find_project(query):
    mongo = Mongodb().client

    user = mongo.db.projects.find_one(query)
    
    return user
