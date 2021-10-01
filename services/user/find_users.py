from libs import Mongodb

def find_users(query):
    mongo = Mongodb().client

    user = mongo.db.users.find(query)
    return user