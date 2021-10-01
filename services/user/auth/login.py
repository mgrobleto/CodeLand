import jwt
from os import environ
from flask import request
import datetime

def login_token(username, email, user_id):
    payload = {
        'username': username,
        'email': email,
        'user_id': user_id,
        'authorization': 'user',
        'exp': datetime.datetime.utcnow() + datetime.timedelta(hours=1),
        'nbf': datetime.datetime.utcnow()
    }

    token = jwt.encode(payload, environ['KEY_JWT'], algorithm='HS256')
    return token

def isLogged(cookie_name):
    if(not cookie_name in request.cookies):
        return {'success': False, 'message': 'El token esta vácio'}
    auth_token = request.cookies.get(cookie_name)

    if auth_token:
        try:
            payload = jwt.decode(auth_token, environ['KEY_JWT'], algorithms=['HS256'])
        except jwt.ExpiredSignatureError:
            return {'success': False, 'message': 'Token has expired, please log in again'}
        except jwt.InvalidTokenError:
            return {'success': False, 'message': 'Invalid token, please log in again'}
        return {'success': True, 'info': payload}
    else:
        return {'success': False, 'message': 'No ha iniciado sessión'}
