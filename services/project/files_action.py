from libs.cloud_storage import Cloud_Storage
# Manejo de markdown para colorear el code
from markdown import markdown
import markdown.extensions.fenced_code
import markdown.extensions.codehilite
from pygments.formatters import HtmlFormatter

def allowed_file(filename):
    ALLOWED_EXTENSIONS = {'txt', 'c', 'js', 'py', 'html', 'h', 'png', 'jpg', 'jpeg', 'gif'}
    return '.' in filename and \
           filename.rsplit('.', 1)[-1].lower() in ALLOWED_EXTENSIONS

def delete_file(path):
    bucket = Cloud_Storage().bucket

    blob = bucket.blob(path)
    if blob.exists():
        return blob.delete()

    return None


def add_file(path, file, content_type):
    bucket = Cloud_Storage().bucket

    blob = bucket.blob(path)
    if blob.exists() and file and allowed_file(file.filename):
        return None
    blob.upload_from_file(file, content_type=content_type)

    return blob


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

