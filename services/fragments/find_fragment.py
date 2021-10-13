from libs import Mongodb
from bson.objectid import ObjectId

def find_fragment(query):
    mongo = Mongodb().client

    user = mongo.db.fragments.find_one({'_id': ObjectId(query)})
    
    return user
