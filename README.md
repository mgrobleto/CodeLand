# CodeLand

Encuentra codigo escrito en un
lenguaje de programacion complejo
como lo es C.Desde lo basico en el,
hasta proyectos mas elaborados
tanto en modo texto como grafico.

Los codigos proporcionados pueden ser
compilados desde la version turbo c 2.0
en adelante.

Podras obtener librerias que son
personalizadas de los desarrolladores
que proporcionan funciones para el C
principal

# Documentación del lenguaje C en español

CodeLand te ofrece
una coleccion de libros
traducidos al idioma
espanol donde
encontraras desde lo
mas basico de la
sintaxis hasta
algoritmos complejos
aplicados en las
primitivas graficas.

# Lenguajes de programación usados

- JavaScript
- Python

## Deploy de la página

La página web esta disponible gracias la plataforma en la nube llamada Heroku y usando gunicorn como WSGI

## Herramientas usadas

<div align="center">
  <img src="/readme_files/software.png" />
</div>

Para poder alacenar los proyectos y algunos archivos estaticos como los pdf usamos Firebase Storage y lo manejamos con librerias de google cloud para poder administrar 
los archivos de una manera más sencilla, y para facilitar el registro de usuarios e información de los proyectos MongoDB fue la herramienta usada para poder hacerlo.

# Analizando código:

En esta parte se explicara el código hecho en python para programar la página. Algunas opciones estan guardadas en variables de entorno por motivos de seguridad.

# Cargando variables de entorno

Necesitamos cargar estas variables solo si el entorno esta en modo desarrollo. Las variables de entorno son varibles que estan en el sistema operativo y 
no se pueden acceder fuera de el, esto es útil para que nadie mire las claves de autenticación.

```python
if(path.exists('./.env')):
    # Variables de entorno en modo desarrollo 
    from dotenv import load_dotenv
    load_dotenv()
```

### Autenticación

En la la parte de autenticación disponemos de la autenticación de Google Cloud, Firebase y MongoDB

### Credenciales para Google Cloud y Firebase

```python
private_key = environ['private_key'].replace('\\n', '\n').replace('\\\\n', '\\n')
credentials = {
    'type': environ['type'],
    'project_id': environ['project_id'],
    'private_key_id': environ['private_key_id'],
    'private_key': private_key,
    'client_email': environ['client_email'],
    'client_id': environ['client_id'],
    'auth_uri': environ['auth_uri'],
    'token_uri': environ['token_uri'],
    'auth_provider_x509_cert_url': environ['auth_provider_x509_cert_url'],
    'client_x509_cert_url': environ['client_x509_cert_url']
}
```
Esta configuración se encuentra en la sección Cuentas de servicios en Configuración del proyecto en el botón generar nueva clave privada. Con esta credencial se dara permisos 
a google cloud storage para manejar los archivos, en el caso de firebase para acceder al storage. Al final esto es un método de seguridad, en el que usamos un diccionario para 
las opciones de la autenticación ya que un json puede ser visible desde el repositorio.

<img src="/readme_files/firebase-credentials.JPG" />

Ahora con las crendenciales usamos ```service_account.Credentials.from_service_account_info(credentials)``` para pasarle las credenciales y retorne el tipo de 
dato que require el storage de google.cloud.

```python
credentials_gc = service_account.Credentials.from_service_account_info(credentials)
client = storage.Client(credentials=credentials_gc)
bucket = client.get_bucket(STORAGE_BUCKET)
```

# Configuración web de Firebase

```python
config = {
    'apiKey': environ['apiKey'],
    'authDomain': environ['authDomain'],
    'databaseURL': environ['databaseURL'],
    'storageBucket': environ['storageBucket'],
    'serviceAccount': credentials
}
STORAGE_BUCKET = config['storageBucket']
```

Ahora pasamos al configuración a Firebase

```python
firebase = Firebase(config)
storage_fb = firebase.storage()
```

Bueno, si todo lo anterior sale bien ya tenemos acceso a google cloud y Firebase y ahora podemos hacer todo lo que estas herramientas no ofrecen. Ahora falta 
MongoDB

# Iniciando la app en MongoDB

Para esto necesitamos dos variables de entorno, una que tiene el nombre de la base de datos y la otra la constraseña

```python
USER_DB = environ["USER_DB"]
PASSWORD_DB = environ["PASSWORD_DB_KEY"]
```

Ahora pasamos a la url de mongoDB esas dos variables para conectarnos directamente a nuestra base de datos :D

```python
app.config['MONGO_URI'] = f'mongodb+srv://{USER_DB}:{PASSWORD_DB}@cluster0.73uuw.mongodb.net/cs50xni?retryWrites=true&w=majority'
Session(app)
mongo = PyMongo(app)
```

## Ya tenemos listas la herramientas que vamos a usar, ahora si, vayamos al código!.

Antes de empezar cabe destacar que el código aún se puede optimizar ;) solo es conocer más el lenguaje.

## Algunas variables globales

```python
ALLOWED_EXTENSIONS = {'txt', 'c', 'js', 'py', 'html', 'h', 'png', 'jpg', 'jpeg', 'gif'}
IMAGE_MIMETYPE = {'image/png', 'image/jpeg', 'image/jpg'}
INVALID_FILENAME = {':', '*', '/', '"', '?', '>', '|', '<'}
```
`ALLOWED_EXTENSIONS` nos ayuda a verificar que los archivos que se subiran sean los correctos, `IMAGE_MIMETYPE` verifica que los mimetype de imagenes sean unicamente 
esos, `INVALID_FILENAME` evita que los archivos tengan nombre que puedan provocar un comportamiento especifico en el sistema por ejemplo: si 
el cliente envia un archivo con ese nombre `../../../../home/username/.bashrc` podria provocar que modifique ese archivo del servidor y eso no esta bien.

## Algunas funciones

Estas funciones no ayudan a resolver algunas validaciones y hacer algunas acciones que se usan en varias partes de código, gracias a ellas evitamos que el código sea 
repetitivo y extenso.

<b>Validando los nombres de archivos</b>

```python
def allowed_file(filename):
    return '.' in filename and \
           filename.rsplit('.', 1)[-1].lower() in ALLOWED_EXTENSIONS
```
Con esta validamos la extensión, el `\` es para indicarle que el código de la siguiente línea forma parte de la línea anterior. Para evitar que tome la extensión incorrecta 
obtenemos el último valor en el arreglo con `-1`, asi al validar `index.routes.js` si fuera `1` tomaria routes y no js y con `-1` tomaria el último. y el 
`in ALLOWED_EXTENSIONS` busca si la extensión obtenida coincide con una de las que esta en el SET (es un arreglo inmutable, quiere decir que no se puede modificar) `in ALLOWED_EXTENSIONS`

<b>Añadiendo el tiempo en que se creo un usuario.</b>

Gracias a esta función podemos decirle al usuario la vez en que se unio a nuestra comunidad.

```python
def timestamp():
    return {"created_at": datetime.datetime.now(datetime.timezone.utc), "updated_at": datetime.datetime.now(datetime.timezone.utc)}
```

<b>Algo más avanzado, retornando la información del usuario y sus proyectos en una sola consulta</b>

En la siguente consulta traemos un diccionario formado por dos datos de diferentes colecciones (tablas en sql) para no hacer dos consultas. Lo que esta haciendo es 
decir: MongoDB buscame un usuario donde el `_id` sea igual al de la variable `user_id`, y ahora con esa información vas a buscar `$lookup` en la colección `projects` usando el valor del 
`_id` del usuario que encontraste y lo vas a comparar con el campo `users_id` de cada documento de la base de datos y los vas a almacenar en un campo `projects`

```python

def get_user_and_project(user_id):
    user_cursor = mongo.db.users.aggregate([
        {
            '$lookup': {
                "from": 'projects',
                "localField": '_id',
                "foreignField": 'users_id',
                "as": 'projects'
            }
        },
        { "$match": { "_id": ObjectId(user_id) } }
    ])
    return list(user_cursor)[0]
```

De manera más visual se puede decir que estamos haciendo una consulta que en vez de traer solo esto del usuarios:

```javascript
{
  "_id": "ObjectId(60baf82dde280748a153f33f)",
  "username": "Enrique Urbina",
  "password": "sha256$J4mU8JkZHq$b8f....",
  "email": "emrique@codeland.com",
  "created_at": 2021-06-05T04:05:55.529+00:00,
  "updated_at": 2021-06-19T11:00:57.745+00:00,
  "perfil": BinaryImage,
  "contentType": "image/png"
}
```

Agrega un campo projects con todos los proyectos de la colección projects donde el `_id` del usuario coincida con el `users_id` de la colleción `projects`, al final 
quedaria algo como esto:


```javascript
{
  "_id": "ObjectId(60baf82dde280748a153f33f)",
  "username": "Enrique Urbina",
  "password": "sha256$J4mU8JkZHq$b8f....",
  "email": "emrique@codeland.com",
  "created_at": 2021-06-05T04:05:55.529+00:00,
  "updated_at": 2021-06-19T11:00:57.745+00:00,
  "perfil": BinaryImage,
  "contentType": "image/png",
  "projects": [
    {
      "_id": "ObjectId(60b0082dde280748a153f33f)",
      "project_name": "Hola Mundo",
      "author": "Enrique Urbina",
      "description": "fdsfdsfddsfds",
      "modo": "text_mode",
      "_id": "ObjectId(60baf82dde280748a153f33f)",
      "path": "/project/60baf82dde280748a153f33f/text_mode/Hola Mundo",
      "created_at": 2021-06-18T20:38:12.594+00:00,
      "updated_at": 2021-06-18T20:38:12.594+00:00,
      "image": BinaryImage
    },
        {
      "_id": "ObjectId(60b0082dde280748a153f33f)",
      "project_name": "PruebaxD",
      "author": "Enrique Urbina",
      "description": "Hola :D",
      "modo": "graphic_mode",
      "_id": "ObjectId(60baf82dde280748a153f33f)",
      "path": "/project/60baf82dde280748a153f33f/text_mode/Hola Mundo",
      "created_at": 2021-06-18T20:38:12.594+00:00,
      "updated_at": 2021-06-18T20:38:12.594+00:00,
      "image": BinaryImage
    }
  ]
}
```

### Ahora algo mucho más complejo, listando directorios de google cloud.

Los directorios listados se usan cuando miras el código de un proyecto o ejemplos dentro de la página, debido a que internamente en google cloud no existe 
el concepto de carpetas sino un concepto un poco complejo, hay que buscar al forma de obtener cada archivo y simular como si vinieran de una carpeta. En google cloud 
los archivos tiene un nombre dependiendo de donde se ubiquen, por ejemplo pueden llamarse: `examples/functions/ordenar.c` entonces usando los `/` del nombre se 
puede simular que es una carpeta y asi listarlos para mostrarlos en el frontend.

Vamos a analizar este código paso por paso para hacerlo menos complejo.

```python
def list_dir(route):
    data = []
    info = {
        'files': [],
        'path': None
    }
    list_ = bucket.list_blobs(prefix=route)
    
    class Padding: # Reelleno para que itere todos los elementos +1
        name = '/'

    data_arr = [Padding]

    for blob in list_:
        data_arr.insert(-1, blob)
    for dirs in data_arr:
        routes = dirs.name.split('/')
        filename = routes.pop(-1) # Si no termina con / quiere decir que no es una carpeta
        path_dir = '/'.join(map(str, routes)) + '/'

        if(filename == '' or info['path'] != path_dir):
            if info['path'] != path_dir and info['path'] != None and len(info['files']) > 0:
                data.append(info.copy())
                info['files'] = []

            info['path'] = path_dir
        if(filename):
            (info['files']).append(filename)

    return data
```

Para empezar lo que necesitamos es obtener los archivos de un directorio como este:
<img src="/readme_files/directorios.png" />
<br/>
Y que regresemos un arreglo de estructura como este:
 
 ```javascript
 [
  {
    files: ['function.c', 'return.c'],
    path: "Example/function/"
  },
  {
    files: ['sort.c', 'reverse.c'],
    path: "Example/arrays/"
  },
   {
    files: ['typedef.c', 'types.c'],
    path: "Example/struct/"
  },
 ]
 ```
 
Luego usando un ciclo for podemos ir mostrando los directorios en el frontend.

para empezar usamos la función `bucket.list_blob(prefix=route)` para listar todos los archivos que incluyan el `prefix` en su nombre, por ejemplo si el prefix es `example/` 
entonces va a retorna algo parecido a una arreglo con todos los archivos que inicien con `example/`, sin embargo también queremos ordenarlos para poder simular subdirectorios, 
para esto vamos a itererar todos los archivos que vienen del `bucket.blob` con una iteración extra por que si no al final quedaria faltando un archivo, ya que en el for se guarda un archivo en el arreglo hasta la siguiente iteración.

```python
    class Padding:
        name = '/'

    data_arr = [Padding]

    for blob in list_:
        data_arr.insert(-1, blob)
```

Con este relleno ya iterara todos los arreglos +1 extra.

En cada iteración primero obtenemos la ruta y el nombre del archivo:

<img src="/readme_files/ejemplo_archivos.png" />

Luego validamos que el nombre no este vacio ya que puede que haigan "directorios" vacios llamados: "Example/const/" y si es así entonces filename seria un string vacio 
por que al dividir con split quedaria: `["Example", "const", ""]` y al obtener el último estaria vacio. También si el path anterior es distinto al anterior quiere decir 
que el proximo archivo es de otra directorio y entonces valida que aparte de que si es distinto no sea None, None es el valor por defecto en el diccionario, y luego que exista 
más de un archivo para tomarlo en cuenta.

Pero si el directorio no cambia entonces valida que el nombre no este vacio, y si no lo esta agrega en el arreglo files del diccionario el nombre del archivo.

Si te das cuenta, el `if(filename == '' or info['path'] != path_dir)` guarda la información de un directorio hasta la siguiente iteración por que depende del nombre del 
proximo archivo para guardalo, ya que si el proximo tiene un directorio distinto debera guarda el directorio anterior.

 ```python
 if(filename == '' or info['path'] != path_dir):
    if info['path'] != path_dir and info['path'] != None and len(info['files']) > 0:
        data.append(info.copy())
        info['files'] = []
        
    info['path'] = path_dir
  if(filename):
      (info['files']).append(filename)
 ```
 
 el `info.copy()` es para pasar una copia del diccionario y no la posición de memoria del diccionario, si pasaramos la posición de memoria se sobreescribiria y en el arreglo 
 habrian muchos diccionarios con la información del último archivo.
 
 ## Obteniendo los código con colores
 
 Esta función es para mostrar el código en el frontend de colores o una imagen. En este caso se valida si es imagen o no, en el caso de que fuera código 
 lo obtiene usando `download_as_string()` y decodificanla con `decode('utf-8')` para caracteres especiales y no obtener un texto extraño. en `code_md` pasamos 
 una sintaxis en markdown similar a la de este archivo para colorear el código usando 3 comillas invertidas y el nombre del lenguaje.
 
 Para la image solo usamos `encodebytes para enviar la información en base64 al frontend`
 
 ```python
 def get_file_data(path_file, file, file_ext):
    if file_ext != 'png' and file_ext !='jpg' and file_ext != 'jpeg':
        code = bucket.blob(f'{path_file}{file}').download_as_string().decode('utf-8')
        code_md = f'```{file_ext}\n{code}\n```'

        md_template_string = markdown.markdown(
        code_md, extensions=["fenced_code", "codehilite"]
        )
        formatter = HtmlFormatter(style="monokai", full=True, cssclass="codehilite")

        css_string = formatter.get_style_defs()
        md_css_string = "<style>" + css_string + "</style>"

        md_template = md_css_string + md_template_string

        return {
            "info": f'{md_template}',
            'file_ext': file_ext,
            'type': 'code'
        }
    else:
        code = bucket.blob(f'{path_file}{file}').download_as_string()
        image = encodebytes(code)
        json_image = dumps(image,default=json_util.default)

        return {
            'info': json_image,
            'type': 'binary'
        }
 ```
 
 ## path.join personalizado
 
 Con "*argv" obtenemos un arreglo con el valor de cada paramentro y lo unimos en un string, se usa para los nombre de los archivos cuando un usuario crea un archivo, si lo 
 quiere guarda en la carpeta `bin` va a concatenar la ruta hasta `bin` por ejemplo: `project/user_id/mode/project_name/bin/filaname` y asi lo guarda en esa ubicación
 
 ```python
def path_join(*argv):
    return ('/'.join(map(str, argv))) + '/'
 ```
 
 ## Creando un zip de los proyectos y static_project
 
 Recorre cada archivo y en base al nombre se guarda en el zip, obtiene el arreglo de archivos que coincidan con prefix y escribe en el zip cada archivo, pero 
 para que no cree carpetas desde el directorio raíz ya que, si recuerdas blob.name trae el nombre del archivo algo así: `project/user_id/mode/project_name/dirs/file.c` 
 necesitamos cortar el nombre y quede `project_name/dirs/file.c` para que la carpeta dentro del zip empieze desde allí. Entonces le indicamos la profundidad del 
 directorio con `depth`, si es 3 entonces `project/user_id/mode/project_name/dirs/file.c` quedaria como `['project', 'user_id', 'mode', 'project_name/dirs/file.c']`, entonces 
 obtenemos el último arreglo para obtener el directorio correcto. `depth` lo que hace es limitar la cantidad de coincidencias que busca en el string.
 
 ```python
 def create_zip(path, depth):
    memory_file = BytesIO()
    blobs = bucket.list_blobs(prefix=path)

    with ZipFile(memory_file, 'w') as zf:
        for blob in blobs:
            binary = blob.download_as_string()
            name = blob.name.split('/', depth)[depth]
            zf.writestr(name, binary)
    memory_file.seek(0)
    return memory_file
```

## Borrando los proyectos

Solo elimina los archivos que coincidan con `prefix`

```python
def delete_project_storage(path):
    blobs = bucket.list_blobs(prefix=path)
    for blob in blobs:
        blob.delete()
```

# Fin

# Protipo en Figma

[Mirar el diseño en figma del proyecto](https://www.figma.com/file/7OgHTAOVJir6qJI9Nlf0T4/cs50_design)