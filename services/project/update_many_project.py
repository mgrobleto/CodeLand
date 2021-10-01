from libs import Mongodb
from bson.objectid import ObjectId

def update_many_project(filter, data):
    mongo = Mongodb().client
    user = mongo.db.projects.update_many(filter, {
        '$set': data
    })
    
    return user
