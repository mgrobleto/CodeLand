from utils.schema.register import registerSchema
from utils.schema.login import loginSchema
from flask import request, jsonify, make_response, redirect, render_template, flash
from werkzeug.security import generate_password_hash, check_password_hash
from services.user.auth import login_token, isLogged
from bson.objectid import ObjectId

from services.user import find_user, add_user, add_user_image

# Actualización del tiempo
import datetime

def auths(app):
    # Cada vez que se crea algo, se añade el tiempo en que se creo
    def timestamp():
        return {"created_at": datetime.datetime.now(datetime.timezone.utc), "updated_at": datetime.datetime.now(datetime.timezone.utc)}

    IMAGE_MIMETYPE = {'image/png', 'image/jpeg', 'image/jpg'}
    @app.route('/login', methods=['GET', 'POST'])
    def login():
        admin_token = isLogged('ADMIN_TOKEN')
        if admin_token['success']:
            return redirect('/admin/profile')
        
        user_token = isLogged('USER_TOKEN')

        if user_token['success']:
            return redirect('/profile')    
        
        if request.method == 'POST':
            email = request.form.get('email')
            password = request.form.get('password')
                
            validation = loginSchema(email, password)

            if not validation['success']:
                return jsonify(validation)
            user = find_user({
                'email': email
            })

            if not user:
                return jsonify({'success': False,'error': 'El usuario no existe'})
            if not check_password_hash(user["password"], password):
                return jsonify({'success': False,'error': 'Correo o contraseña incorrecta'})

            resp = make_response(jsonify({"success": True, 'token': 'valid'}))
            resp.set_cookie('USER_TOKEN', login_token(user['username'], email, user['_id'].__str__()), httponly=True)
            resp.set_cookie('username', user['username'])
            resp.set_cookie('email', email, httponly=True)
            resp.set_cookie('user_id', user['_id'].__str__(), httponly=True)
            resp.set_cookie('user_image', user['cover'], httponly=True)

            return resp


        return render_template('auth/login/index.html')
    @app.route('/register', methods=['GET', 'POST'])
    def register():
        admin_token = isLogged('ADMIN_TOKEN')
        if admin_token['success']:
            return redirect('/admin/profile')
        
        user_token = isLogged('USER_TOKEN')
        if user_token['success']:
            return redirect('/profile')
                
        if(request.method == 'POST'):
            email = request.form.get("email")
            username = request.form.get("username")
            password = generate_password_hash(request.form.get(
                "password"), method="sha256", salt_length=10 # se encripta con sha256 10 veces
            )

            print(username)
            validation = registerSchema(email, username, password)

            if not validation['success']:
                return jsonify(validation)

            findUser = find_user({ "email": email }) # busca un usuario donde uno de esos dos campos tenga ese valor
            if findUser != None:
                return jsonify({"success": False, 'message': f'{email} ya existe'})

            file = request.files['image']
            if file.filename != '':
                if file.mimetype in IMAGE_MIMETYPE:
                    mimetype = file.mimetype
                    extension_image = file.filename.split('.')[-1]
                    image_data = file.read()
                else:
                    flash('error mimetype')
                    return redirect('/register')

            else:
                image = open('./static/images/user_default_logo.png', 'rb').read()
                mimetype = 'image/png'
                extension_image = 'png'
                image_data = image

            user_id = ObjectId()
            image_url = 'user_image/' + user_id.__str__() + f'.{extension_image}'

            submit_image = add_user_image(image_url, image_data, mimetype)

            user = add_user( # inserta un usuario
                {"_id": user_id, "username": username, "password": password, "email": email, "cover": submit_image, **timestamp()})

            print('created')
            resp = make_response(jsonify({"success": True, 'message': 'Usuario creado con éxito'}))

            # set httpOnly cookies
            resp.set_cookie('USER_TOKEN', login_token(username, email, user.__str__()), httponly=True)
            resp.set_cookie('username', username)
            resp.set_cookie('email', email, httponly=True)
            resp.set_cookie('user_id', user.__str__(), httponly=True)
            resp.set_cookie('user_image', submit_image, httponly=True)

            return resp

        return render_template('auth/register/index.html')
    
    @app.route('/logout')
    def logout():
        resp = make_response(redirect('/login'))
        resp.set_cookie('USER_TOKEN', expires=0)
        resp.set_cookie('username', expires=0)
        resp.set_cookie('email', expires=0)
        resp.set_cookie('user_id', expires=0)
        resp.set_cookie('user_image', expires=0)
        resp.set_cookie('project_path', expires=0)
        flash(f'Session closed') 
        return resp

