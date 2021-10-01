# utils
import json
from services.user.auth import isLogged
import mimetypes

# Manejo de archivos
from tempfile import mkdtemp
from os import path, environ

# manipular información 
from bson.objectid import ObjectId

# Configuración del servidor
from flask import Flask, render_template, request, after_this_request

# Cloud Storage
from libs import Cloud_Storage

# Librerias de Mongodb
from libs import Mongodb

# Actualización del tiempo
import datetime

# Rutas de la página
from routes import auths, downloads, examples, project, user, statics

# cookies
from utils.cookies import compareValues

if(path.exists('./.env')):
    # Variables de entorno en modo desarrollo 
    from dotenv import load_dotenv
    load_dotenv()


USER_DB = environ["USER_DB"]
PASSWORD_DB = environ["PASSWORD_DB_KEY"]


mimetypes.add_type('application/javascript', '.js')
app = Flask(__name__)

app.secret_key = environ['SESSION_KEY']
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config['SESSION_PERMANENT'] = True  # La cookie no se guarda para siempre
app.config['SESSION_TYPE'] = 'filesystem'
app.config['SESSION_COOKIE_SECURE'] = True
app.config['MONGO_URI'] = f'mongodb+srv://{USER_DB}:{PASSWORD_DB}@cluster0.73uuw.mongodb.net/cs50xni?retryWrites=true&w=majority'

mongodb = Mongodb()
mongodb.connect(app)
mongo = mongodb.client
Cloud_Storage()

IMAGE_MIMETYPE = {'image/png', 'image/jpeg', 'image/jpg'}
INVALID_FILENAME = {':', '*', '/', '"', '?', '>', '|', '<'}

# Es una herramienta sorpresa que nos ayudara más tarde
# def _item_to_value(iterator, item):
#     return item

# def list_directories(bucket_name, prefix):
#     if prefix and not prefix.endswith('/'):
#         prefix += '/'

#     extra_params = {
#         "projection": "noAcl",
#         "prefix": prefix,
#         "delimiter": '/'
#     }

#     path = "/b/" + bucket_name + "/o"

#     iterator = page_iterator.HTTPIterator(
#         client=client,
#         api_request=client._connection.api_request,
#         path=path,
#         items_key='prefixes',
#         item_to_value=_item_to_value,
#         extra_params=extra_params,
#     )
#     return [x for x in iterator]
# directories = list_directories(STORAGE_BUCKET, route)

# Si el nombre tiene un carácter extraño
def change_folder_name(string):
    for invalid_name in INVALID_FILENAME:
        if string.find(invalid_name) > -1:
            string = string.replace(invalid_name, '_')
    return string

@app.before_request
def before_request():
    app.permanent_session_lifetime = datetime.timedelta(hours=12);
    if(not '/static/' in request.path):
        @after_this_request
        def request_after(resp):
            token = request.cookies.get('USER_TOKEN')
            get_info = isLogged(token)
            if get_info.get('success'):
                # print(get_info)
                data = get_info.get('info')

                if(get_info.get('success')):
                    return compareValues(resp, data)

            return resp


@app.route('/')
def home():
    user = {}
    validation = isLogged('USER_TOKEN')
    if validation.get('success'):
        user_info = validation.get('info')
        user_id = ObjectId(user_info.get('user_id'))
        user = mongo.db.users.find_one({"_id": user_id})

    return render_template('index.html', user=user)

auths(app)
downloads(app)
examples(app)
user(app)
project(app)
statics(app)

@app.route('/tools')
def installers():
    return render_template("installers/tools.html")


@app.route('/about-us')
def about():
    return render_template("about us/about.html")


@app.route('/google5e97d84d9d35c069.html')
def googleSearchConsole():
    return render_template("google5e97d84d9d35c069.html")


# @app.route('/dirs', methods=['GET'])
# def getDirs():
#     datas = []
#     code = list_dir()
#     datas.append(code)
#     codigo = dumps(code, default=json_util.default, ensure_ascii=False).encode('utf-8')
    
#     return Response(codigo, content_type='application/json; charset=utf-8')


# @app.route('/zip', methods=['GET'])
# def zipDownload():
#     memory_file = BytesIO()
#     blobs = bucket.list_blobs(prefix='static_projects/')

#     with ZipFile(memory_file, 'w') as zf:
#         for blob in blobs:
#             binary = blob.download_as_string()
#             zf.writestr(blob.name, binary)
#     memory_file.seek(0)
#     return send_file(memory_file, download_name='zip.zip')

# @app.route('/download-gc', methods=['GET', 'POST'])
# def download_google():
#     if request.method == 'POST':
#         files = request.files.getlist('files')
#         for file in files:
#             filename = file.filename
#             data = (file.stream.read()).decode('utf-8')
#             blob = bucket.blob('documentacion/' + filename)
#             blob.upload_from_string(data, content_type = file.content_type)
        # file = bucket.blob('josue.png')
        # file.make_public()
        # file.download_to_filename('filename.png')
    # return 'ta bien'

# @app.route('/prueba', methods=['GET'])
# def prueba():
    # storage_user = default_app.storage.bucket(name='gs://codeland-dcd2d.appspot.com')
    # storage_user = default_app.storage()
    # storage_random = storage_fb.child("documentacion/cuento.c").get_url(None)

    # gcs_file = bucket.get_blob('josue.png')
    # blob = bucket.blob('static_projects/')
    # blob.upload_from_string('', content_type='application/x-www-form-urlencoded;charset=UTF-8')
    # folders = bucket.list_blobs(None, prefix='static_project/')

    # folder = bucket.blob('/static_project/graphic_mode/')
    # folder_2 = bucket.blob('static_projects/')
    # print(folders.path)
    # print(folders.max_results)
    # for folder_ref in folders:
    #     print(folder_ref)
    # Util
    # https://stackoverflow.com/questions/59829188/how-rename-folder-in-firebase-storage-android-studio
    # https://stackoverflow.com/questions/41075100/move-rename-folder-in-google-cloud-storage-using-nodejs-gcloud-api?noredirect=1&lq=1
    # https://stackoverflow.com/questions/38601548/how-to-move-files-with-firebase-storage
    # bucket.copy_blob(folder, bucket, '/copia/')

    # return send_file(BytesIO(gcs_file.download_as_string()), mimetype='image/jpg')
# @app.route("/publicProject/<projectID>")
# def publicProjects(projectID): 
#     update = mongo.db.projects.update_one({"_id":ObjectId(projectID)},{"$set":{
#         "public": True
#     }})
#     return jsonify({"success":True})


@app.errorhandler(404)
def page_not_found(_):
    # note that we set the 404 status explicitly
    return render_template('404.html'), 404

if __name__ == '__main__':
    if environ['FLASK_ENV'] == 'development':

        app.run(debug=True)
    else:
        app.run(debug=False)


# https://stackoverflow.com/questions/37074977/how-to-get-list-of-folders-in-a-given-bucket-using-google-cloud-api :0
# https://stackoverflow.com/questions/583791/is-it-possible-to-generate-and-return-a-zip-file-with-app-engine creara el zip
# https://stackoverflow.com/questions/41865214/how-to-serve-an-image-from-google-cloud-storage-using-python-flask
# https://stackoverflow.com/questions/38658417/create-blob-from-url-in-gae-using-python
# https://cloud.google.com/appengine/docs/flexible/python/using-cloud-storage
# https://cloud.google.com/storage/docs/json_api/v1/objects/copy