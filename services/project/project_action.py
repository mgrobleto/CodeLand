from libs import Mongodb
from libs.cloud_storage import Cloud_Storage
from io import BytesIO
from zipfile import ZipFile

def add_project(query):
    mongo = Mongodb().client

    projects = mongo.db.projects.insert(query)
    
    return projects

def get_static_projects(query):
    mongo = Mongodb().client

    static_projects = mongo.db.static_projects.find(query)
    
    return static_projects

def get_projects(query):
    mongo = Mongodb().client

    projects = mongo.db.projects.find(query)
    
    return projects


def find_static_project(query):
    mongo = Mongodb().client

    user = mongo.db.static_projects.find_one(query)
    
    return user


def find_project(query):
    mongo = Mongodb().client

    user = mongo.db.projects.find_one(query)
    
    return user

def update_project(filter, query):
    mongo = Mongodb().client
    keys = list(query.keys())
    query2 = {}

    for key in keys:
        if key == 'inc' and query2.get('$inc') == None:
            query2['$inc'] = query[key]
        if key == 'set' and query2.get('$set') == None:
            query2['$set'] = query[key]
    projects = mongo.db.projects.update_one(filter, query2)

    return projects


def update_many_project(filter, data):
    mongo = Mongodb().client
    user = mongo.db.projects.update_many(filter, {
        '$set': data
    })
    
    return user


def delete_project(query):
    mongo = Mongodb().client

    user = mongo.db.projects.find_one_and_delete(query)
    
    return user


def download_project(path, depth):
    bucket = Cloud_Storage().bucket

    memory_file = BytesIO()
    blobs = bucket.list_blobs(prefix=path)

    with ZipFile(memory_file, 'w') as zf:
        for blob in blobs:
            binary = blob.download_as_string()
            name = blob.name.split('/', depth)[depth]
            zf.writestr(name, binary)
    memory_file.seek(0)
    return memory_file


def download_static_project(path, depth):
    bucket = Cloud_Storage().bucket

    memory_file = BytesIO()
    blobs = bucket.list_blobs(prefix=path)

    with ZipFile(memory_file, 'w') as zf:
        for blob in blobs:
            binary = blob.download_as_string()
            name = blob.name.split('/', depth)[depth]
            zf.writestr(name, binary)
    memory_file.seek(0)
    return memory_file

