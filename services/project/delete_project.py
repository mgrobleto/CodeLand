from libs.cloud_storage import Cloud_Storage

def delete_project_storage(path):
    bucket = Cloud_Storage().bucket
    blobs = bucket.list_blobs(prefix=path)
    for blob in blobs:
        blob.delete()