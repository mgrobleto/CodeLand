from libs import Mongodb
from bson.objectid import ObjectId

def find_document(query):
    mongo = Mongodb().client

    user = mongo.db.documentation.find_one(query)
    return user
