from libs import Mongodb
from bson.objectid import ObjectId

# data transfer
from io import BytesIO
from zipfile import ZipFile

from libs.cloud_storage import Cloud_Storage

def allowed_file(filename):
    ALLOWED_EXTENSIONS = {'txt', 'c', 'js', 'py', 'html', 'h', 'png', 'jpg', 'jpeg', 'gif'}
    return '.' in filename and \
           filename.rsplit('.', 1)[-1].lower() in ALLOWED_EXTENSIONS


def get_fragments(query):
    mongo = Mongodb().client

    user = mongo.db.fragments.find(query)
    
    return user

def find_fragment(query):
    mongo = Mongodb().client

    user = mongo.db.fragments.find_one(query)
    
    return user


def find_ejemplos(query):
    mongo = Mongodb().client

    user = mongo.db.ejemplos.find_one(query)
    
    return user

def add_fragment(query):
    mongo = Mongodb().client

    fragments = mongo.db.fragments.insert(query)
    
    return fragments

def delete_fragment(query):
    mongo = Mongodb().client

    user = mongo.db.fragments.find_one_and_delete(query)
    
    return user


def download_examples(path, depth):
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
