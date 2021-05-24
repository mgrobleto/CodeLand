import datetime
from mongoengine import *

class Users(Document):
    name=StringField(required=True)
    email=StringField(required=True)
    password=StringField(required=True)
    createdAt=DateTimeField()
    updatedAt=DateTimeField(default=datetime.datetime.now())
    __v=IntField(default=0)
    meta= {'collection': 'users', 'strict': False,}

    def save(self, *args, **kwargs):
        if not self.createdAt:
            self.createdAt = datetime.datetime.now()
        self.updatedAt = datetime.datetime.now()
        return super(Users, self).save(*args, **kwargs)
