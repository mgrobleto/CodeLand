from libs import Mongodb
from bson.objectid import ObjectId

def find_ejemplos(ejemplo_id):
    mongo = Mongodb().client

    if(not ObjectId.is_valid(ejemplo_id)):
        ejemplo_id = ObjectId(ejemplo_id)
        
    user = mongo.db.ejemplos.find_one({'_id': ObjectId(ejemplo_id)})
    
    return user
