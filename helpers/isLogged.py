def isLogged(f):
    @wraps(f)
    def isLogged_decorate(*args, **kargs):
        print()
        return f(*args, **kargs)
    return isLogged_decorate