from bson.objectid import ObjectId
from flask import send_file

from services.fragments import find_ejemplos
from services.project import find_static_project

from services.project import find_project, find_static_project, download_project, download_static_project
from services.fragments import download_examples

def downloads(app):
    @app.route('/download-project/<project_id>', methods=['GET'])
    def download_project_(project_id):
        project = find_project({ '_id': ObjectId(project_id)})
        project_name = project['project_name']

        memory_file = download_project(project['path'], 3)
        return send_file(memory_file, download_name=f'{project_name}.zip')

    # Ruta para descargar los codigos predeterminados en modo texto
    @app.route('/download-static_project/<project_id>', methods=['GET'])
    def download_static_projec_(project_id):
        project = find_static_project({ '_id': ObjectId(project_id)})
        # print(project)
        project_title = project['program_title']
        memory_file = download_static_project(project['path'], 3)

        return send_file(memory_file, attachment_filename=f'{project_title}.zip', as_attachment=True)

    @app.route('/download-example/<example_id>')
    def download_example(example_id):
        example = find_ejemplos({'_id': ObjectId(example_id)})
        example_title = example['example_name']
        memory_file = download_examples(example['path'], 1)
        return send_file(memory_file, attachment_filename=f'{example_title}.zip', as_attachment=True)
