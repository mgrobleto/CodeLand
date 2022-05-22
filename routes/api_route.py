from services.project import get_projects
from services.fragments import get_fragments
from flask import jsonify, request
from bson.objectid import ObjectId

def api(app):
    @app.route('/api/user/get_project')
    def get_user_project():
        user_image = request.cookies.get('user_image')

        db_projects = get_projects({
            'users_id': ObjectId(request.cookies.get('user_id')),
        })
        data_list = []
        for doc in db_projects:
                data_list.append({
                    '_id': doc['_id'].__str__(),
                    'project_name': doc['project_name'],
                    'mode': doc['mode'],
                    'image': doc['image'],
                    'author': doc['author'],
                    'user_image': user_image,
                    'url': '/project/' + doc['author'] + '/' + doc['_id'].__str__() + '/'
                })

        return jsonify(data_list)
    @app.route('/api/user/get_fragment')
    def get_user_fragment():
        user_image = request.cookies.get('user_image')

        db_fragments = get_fragments({
            'users_id': ObjectId(request.cookies.get('user_id')),
        })
        data_list = []
        for doc in db_fragments:
                data_list.append({
                    '_id': doc['_id'].__str__(),
                    'fragment_name': doc['fragment_name'],
                    'image': doc['image'],
                    'author': doc['author'],
                    'user_image': user_image,
                    'url': '/fragment/' + doc['author'] + '/' + doc['_id'].__str__() + '/'
                })

        return jsonify(data_list)