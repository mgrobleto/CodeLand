# Actualización del tiempo
import datetime

# Cada vez que se crea algo, se añade el tiempo en que se creo
def timestamp():
    return {"created_at": datetime.datetime.now(datetime.timezone.utc), "updated_at": datetime.datetime.now(datetime.timezone.utc)}
