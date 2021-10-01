# Manejo de markdown para colorear el code
from markdown import markdown
import markdown.extensions.fenced_code
import markdown.extensions.codehilite
from pygments.formatters import HtmlFormatter

from libs.cloud_storage import Cloud_Storage

def get_file_data(path_file, file, file_ext):
    bucket = Cloud_Storage().bucket

    if file_ext != 'png' and file_ext !='jpg' and file_ext != 'jpeg':
        code = bucket.blob(f'{path_file}{file}').download_as_string().decode('utf-8')
        code_md = f'```{file_ext}\n{code}\n```'

        md_template_string = markdown.markdown(
        code_md, extensions=["fenced_code", "codehilite"]
        )
        formatter = HtmlFormatter(style="monokai", full=True, cssclass="codehilite")

        css_string = formatter.get_style_defs()

        return {
            "code": {    
                "html": f'{md_template_string}',
                "css": f'{css_string}',
            },
            'file_ext': file_ext,
            'type': 'code'
        }
    else:
        code = bucket.blob(f'{path_file}{file}')
        image = code.public_url
        info = {
            'file_ext': file_ext,
            'type': 'image'
        }
        return {
            'code': None,
            'image': image,
            'info': info,
        }

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
