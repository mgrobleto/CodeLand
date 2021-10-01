from libs import Mongodb
from bson.objectid import ObjectId

def add_user(data):
    mongo = Mongodb().client
    # check if data['_id'] is ObjectId
    if not ObjectId.is_valid(data['_id']):
        data['_id'] = ObjectId(data['_id'])

    user = mongo.db.users.insert(data)
    return user
