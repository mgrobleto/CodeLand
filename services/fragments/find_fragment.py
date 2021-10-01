from libs import Mongodb
from bson.objectid import ObjectId

def find_fragment(fragment_id):
    mongo = Mongodb().client

    if(not ObjectId.is_valid(fragment_id)):
        fragment_id = ObjectId(fragment_id)

    user = mongo.db.fragments.find_one({'_id': ObjectId(fragment_id)})
    
    return user
