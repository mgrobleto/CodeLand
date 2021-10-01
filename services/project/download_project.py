# data transfer
from io import BytesIO
from zipfile import ZipFile
from libs.cloud_storage import Cloud_Storage

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
