from libs.cloud_storage import Cloud_Storage

def add_user_image(url, image_data, mimetype):
    bucket = Cloud_Storage().bucket
    blob = bucket.blob(url);
    blob.upload_from_string(image_data, content_type=mimetype)
    blob.make_public()
    return blob.public_url

