from libs import Mongodb
from bson.objectid import ObjectId

def find_static_project(query):
    mongo = Mongodb().client

    user = mongo.db.static_projects.find_one(query)
    
    return user
