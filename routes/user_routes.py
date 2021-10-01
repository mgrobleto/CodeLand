from flask import render_template, request, redirect, flash, make_response, jsonify
from werkzeug.security import generate_password_hash, check_password_hash

# Timepo
import datetime

# types
from bson.objectid import ObjectId

# utils
from services.user.auth import login_token, isLogged

# Services
from services.user import get_user_and_project, find_user, find_users, update_user_image, update_user
from services.project import update_many_project

from utils.cookies import destroyCookie

def user(app):
    IMAGE_MIMETYPE = {'image/png', 'image/jpeg', 'image/jpg'}

    @app.route('/profile')
    def profile():
        session_exist = isLogged('USER_TOKEN')
        if session_exist['success']:
            user_id = (session_exist['info'])['user_id']
            finduser = find_user({'_id': ObjectId(user_id)})

            if finduser:
                user = get_user_and_project(user_id)
            else:
                return redirect('/logout')
            return render_template('user/profile/index.html', user=user)
        else:
            resp = make_response(redirect('/login'))
            flash("You are not logged in. Please log in to see the profile.")
            return destroyCookie(resp)
    
    @app.route('/update-account/<user_id>', methods=['PUT'])
    def update_profile(user_id):
        user_payload = isLogged('USER_TOKEN')
        user_info = user_payload.get('info')

        if(user_info['user_id'] == user_id):
            username = request.form.get('username')
            email = request.form.get('email')
            password = request.form.get('password')
            password_confirm = request.form.get('password_confirm')

            findUsers_cursor = find_users({ "email": email })
            findUser = list(findUsers_cursor)
            # print(findUser)

            if len(findUser) >= 1 and (findUser[0]['_id'] != ObjectId(user_info['user_id'])):
                return jsonify({"success": False, 'message': 'Ya existe un usuario con ese nombre o email'})

            user_db = find_user({'_id': ObjectId(user_id)})
            if user_db == None:
                return jsonify({"success": False, 'message': 'Usuario no encontrado'})

            if not check_password_hash(user_db['password'], password_confirm):
                return jsonify({"success": False, 'message': 'Las contraseñas no coinciden'})
            #se validan las entradas
            newInfo = {}
            if len(username) > 0:
                newInfo['username'] = username
            if len(email) > 3:
                newInfo['email'] = email

            if len(password) > 4:
                newInfo['password'] = generate_password_hash(password, method="sha256", salt_length=10)
            newInfo['updated_at'] = datetime.datetime.now()

            file = request.files['perfil']
            newImage = ''
            if file.filename != '':
                if file.mimetype in IMAGE_MIMETYPE:
                    mimetype = file.mimetype
                    ext = file.filename.split('.')[-1]
                    image = file.read()

                    image_url = update_user_image(request.cookies.get('user_image').split('/', 4)[-1], f'user_image/{user_id}.{ext}', image, mimetype)
                    # edit metadata blob
                    
                    # blob.make_public()
                    newInfo['cover'] = image_url
                    newImage = image_url
                    # print('Hi')
                else:
                    return jsonify({"success": False, 'message': 'error mimetype'})

            
            update_many_project({'users_id': ObjectId(user_info['user_id'])}, { 'author': newInfo['username'] })
            user = update_user({ '_id': ObjectId(user_id) }, newInfo)

            data = jsonify({
                'user': user.get('username'),
                'image': user.get('cover'),
                'email': user.get('email'),
                'success': True,
            })
            resp = make_response(data)
            resp.set_cookie('USER_TOKEN', login_token(newInfo['username'], user['email'], user['_id'].__str__()), httponly=True)
            resp.set_cookie('user_id', user['_id'].__str__(), httponly=True)
            resp.set_cookie('username', newInfo['username'])
            resp.set_cookie('email', newInfo['email'], httponly=True)
            if newImage:
                resp.set_cookie('user_image', image_url, httponly=True)
            return resp
        else:
            return jsonify({'success': False, 'message': 'Usuario no autorizado'})
