from flask import request

def destroyCookie(resp):
    resp.set_cookie('USER_TOKEN', expires=0)
    resp.set_cookie('username', expires=0)
    resp.set_cookie('email', expires=0)
    resp.set_cookie('user_id', expires=0)
    resp.set_cookie('user_image', expires=0)
    return resp

def compareValues(resp, data):
    if(not (findCookie('username') == data.get('username'))):
        return destroyCookie(resp)

    if(not (findCookie('user_id') == data.get('user_id'))):
        return destroyCookie(resp)
    
    if(not (findCookie('email') == data.get('email'))):
        return destroyCookie(resp)

def findCookie(name):
    return request.cookies.get(name)
    

def checkCookies():
    username = findCookie('username')
    user_id = findCookie('user_id')
    email = findCookie('email')
    user_image = findCookie('user_image')
    return {
        'username': username,
        'user_id': user_id,
        'email': email,
        'user_image': user_image
    }