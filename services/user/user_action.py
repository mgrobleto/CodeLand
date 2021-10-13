from libs import Mongodb
from bson.objectid import ObjectId
from libs.cloud_storage import Cloud_Storage


def add_user(data):
    mongo = Mongodb().client
    # check if data['_id'] is ObjectId
    if not ObjectId.is_valid(data['_id']):
        data['_id'] = ObjectId(data['_id'])

    user = mongo.db.users.insert(data)
    return user

def add_user_image(url, image_data, mimetype):
    bucket = Cloud_Storage().bucket
    blob = bucket.blob(url);
    blob.upload_from_string(image_data, content_type=mimetype)
    blob.make_public()
    return blob.public_url

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
        {
            '$lookup': {
                "from": 'fragments',
                "localField": '_id',
                "foreignField": 'users_id',
                "as": 'fragments'
            }
        },
        { "$match": { "_id": ObjectId(user_id) } }
    ])
    list_user = list(user_cursor)[0]

    return list_user

def find_user(query):
    mongo = Mongodb().client

    user = mongo.db.users.find_one(query)
    return user

def find_users(query):
    mongo = Mongodb().client

    user = mongo.db.users.find(query)
    return user

def update_user_image(name, new_name, image, mimetype):
    bucket = Cloud_Storage().bucket
    blob = bucket.blob(name)

    bucket.rename_blob(blob, 'user_images/' + new_name)
    blob.metadata = {'Content-Type': mimetype, 'max-age': '0', 'Cache-Control': 'public'}
    blob.upload_from_string(image, content_type=mimetype)
    
    return blob.public_url


def update_user(filter, query):
    mongo = Mongodb().client

    user = mongo.db.users.find_one_and_update(filter, {
        '$set': query
    })
    return user
