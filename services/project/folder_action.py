from libs.cloud_storage import Cloud_Storage

def add_folder(path):
    bucket = Cloud_Storage().bucket

    blob = bucket.blob(path)
    
    if blob.exists():
        return False

    blob.upload_from_string('', content_type='application/x-www-form-urlencoded;charset=UTF-8')

    return blob


def list_dir(route):
    bucket = Cloud_Storage().bucket
    data = []
    info = {
        'files': [],
        'path': None,
        'isListed': 0
    }
    list_ = bucket.list_blobs(prefix=route)
    # https://stackoverflow.com/questions/63743826/google-datastore-iterator-already-started-how-to-work-with-these-iterators
    class Padding: # Reelleno para que itere todos los elementos +1
        name = '/'
        files: None
        path=""

    data_arr = [Padding]

    for blob in list_:
        data_arr.insert(-1, blob)

    for dirs in data_arr:
        routes = dirs.name.split('/')
        filename = routes.pop(-1) # Si no termina con / quiere decir que no es una carpeta
        path_dir = '/'.join(map(str, routes)) + '/'
        existFolder = False

        for search in data:
            if path_dir == search['path']:
                search['files'].append(filename)
                existFolder = True
        if(existFolder):
            continue

        if(filename == '' or info['path'] != path_dir):
            if info['path'] != path_dir and info['path'] != None:
                data.append(info.copy())
                info['files'] = []

            info['path'] = path_dir
            # print(routes)
        if(filename):
            (info['files']).append(filename)

    return data
