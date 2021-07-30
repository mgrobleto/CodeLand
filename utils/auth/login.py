import jwt
from os import environ
from flask import request
import datetime

# econded = jwt.encode({ "some": "payload" },'secret', algorithm='HS256')
# print(econded)

# decode = jwt.decode(econded, 'secret', algorithms=['HS256'])

# print(decode)

# create a function that will be called when the user is logged and validated with the JWT token

# def login_required(f):
#     @wraps(f)
#     def decorator(*args, **kwargs):
#         auth_token = request.headers.get('Authorization')
#         if auth_token:
#             try:
#                 payload = jwt.decode(auth_token, environ['KEY_JWT'], algorithms=['HS256'])
#             except jwt.ExpiredSignatureError:
#                 return jsonify({'message': 'Token has expired, please log in again'}), 401
#             except jwt.InvalidTokenError:
#                 return jsonify({'message': 'Invalid token, please log in again'}), 401
#             return f(*args, **kwargs)
#         else:
#             return jsonify({'message': 'You are not logged in'}), 401

#     return decorator
def login_token(username, email, user_id):
    payload = {
        'username': username,
        'email': email,
        'user_id': user_id,
        'authorization': 'user',
        'exp': datetime.datetime.utcnow() + datetime.timedelta(minutes=15),
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
