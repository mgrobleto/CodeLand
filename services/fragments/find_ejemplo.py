from libs import Mongodb
from bson.objectid import ObjectId

def find_ejemplos(query):
    mongo = Mongodb().client

    user = mongo.db.ejemplos.find_one(query)
    
    return user
