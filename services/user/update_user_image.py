from libs.cloud_storage import Cloud_Storage

def update_user_image(name, new_name, image, mimetype):
    bucket = Cloud_Storage().bucket
    blob = bucket.blob(name)

    bucket.rename_blob(blob, 'user_images/' + new_name)
    blob.metadata = {'Content-Type': mimetype, 'max-age': '0', 'Cache-Control': 'public'}
    blob.upload_from_string(image, content_type=mimetype)
    
    return blob.public_url
