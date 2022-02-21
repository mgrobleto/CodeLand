from os import path, environ

# Librerias de google cloud
from google.cloud import storage
from google.oauth2 import service_account
# from google.api_core import page_iterator
# from google.cloud.storage.bucket import Bucket


# Firebase credentials
private_key = environ['private_key'].replace('\\n', '\n').replace('\\\\n', '\\n')
credentials = {
    'type': environ['type'],
    'project_id': environ['project_id'],
    'private_key_id': environ['private_key_id'],
    'private_key': private_key,
    'client_email': environ['client_email'],
    'client_id': environ['client_id'],
    'auth_uri': environ['auth_uri'],
    'token_uri': environ['token_uri'],
    'auth_provider_x509_cert_url': environ['auth_provider_x509_cert_url'],
    'client_x509_cert_url': environ['client_x509_cert_url']
}
 
config = {
    'apiKey': environ['apiKey'],
    'authDomain': environ['authDomain'],
    'databaseURL': environ['databaseURL'],
    'storageBucket': environ['storageBucket'],
    'serviceAccount': credentials
}
STORAGE_BUCKET = config['storageBucket']

    
class Cloud_Storage:
    __instance = None
    def __new__(cls):
        if Cloud_Storage.__instance is None:
            Cloud_Storage.__instance = object.__new__(cls)
        return Cloud_Storage.__instance
    
    def __init__(self):
        self.connect()
    
    def connect(self):
        # Initialize Cloud Storage
        credentials_gc = service_account.Credentials.from_service_account_info(credentials)
        client = storage.Client(credentials=credentials_gc)
        bucket = client.get_bucket(STORAGE_BUCKET)
        self.bucket = bucket

