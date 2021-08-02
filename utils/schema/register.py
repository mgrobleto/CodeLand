def registerSchema(email, username, password):
    if not username or not password or not email:
        return {
            'success': False,
            'message': 'Username, password and email are required.'
        }
    else:
        return {
            'success': True,
            'message': None
        }
