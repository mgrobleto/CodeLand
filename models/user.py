import datetime
from mongoengine import *
from flask_mongoengine import BaseQuerySet

class Users(db.Document):
    name=StringField(required=True)
    email=StringField(required=True)
    password=StringField(required=True)
    createdAt=DateTimeField()
    updatedAt=DateTimeField(default=datetime.datetime.now())
    __v=IntField(default=0)
    meta= {'collection': 'users', 'strict': False, 'queryset_class': BaseQuerySet}

    def save(self, *args, **kwargs):
        if not self.createdAt:
            self.createdAt = datetime.datetime.now()
        self.updatedAt = datetime.datetime.now()
        return super(Users, self).save(*args, **kwargs)
