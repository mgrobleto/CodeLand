from libs import Mongodb
from bson.objectid import ObjectId

def get_user_and_project(user_id):
    mongo = Mongodb().client

    if(not ObjectId.is_valid(user_id)):
        user_id = ObjectId(user_id)

    user_cursor = mongo.db.users.aggregate([
        {
            '$lookup': {
                "from": 'projects',
                "localField": '_id',
                "foreignField": 'users_id',
                "as": 'projects'
            }
        },
        { "$match": { "_id": ObjectId(user_id) } }
    ])
    list_user = list(user_cursor)[0]
    print(list_user['username'])

    return list_user
