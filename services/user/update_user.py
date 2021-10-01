from libs import Mongodb

def update_user(filter, query):
    mongo = Mongodb().client

    user = mongo.db.users.find_one_and_update(filter, {
        '$set': query
    })
    return user