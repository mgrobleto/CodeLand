from libs import Mongodb
# from bson.objectid import ObjectId

def find_user(query):
    mongo = Mongodb().client

    user = mongo.db.users.find_one(query)
    return user
