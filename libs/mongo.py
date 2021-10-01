from flask_pymongo import PyMongo

# singleton class
    
class Mongo:
    __instance = None
    def __new__(cls):
        if Mongo.__instance is None:
            Mongo.__instance = object.__new__(cls)
        return Mongo.__instance
    
    def connect(self, app):
        print("Connecting to MongoDB")
        self.client = PyMongo(app)

# compare
