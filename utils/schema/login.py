def loginSchema(email, password):
    if(email == None):
        return {'success': False,'error': 'No ingreso el correo'}

    if(password == None):
        return {'success': False,'error': 'La contraseña es requerida'}

    else:
        return {'success': True, 'error': None}

