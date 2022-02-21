from flask import render_template, request, jsonify
from services.storage import list_dir, get_file_data

from services.project import find_static_project, find_project

def statics(app):
    # Ruta para ver los proyectos en modo grafico
    @app.route('/static_projects/graphic_mode/<project_name>/', methods=['GET', 'POST'])
    def show_project_graphic(project_name):
        db_project = find_static_project({ 'program_title': project_name })
        project_path = db_project['path']

        if db_project is None:
            return render_template('404.html'), 404

        if request.method == 'POST':
            file = (request.get_json())['filename']
            path_file = (request.get_json())['path']
            file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
            return jsonify(get_file_data(path_file, file, file_ext))

        # Muestra los directorios del proyecto correspondiente para ver los codigos
        directory = list_dir(route=project_path)
        download_URI = f'/download-static_project/{db_project["_id"]}'

        return render_template('show_static_project/index.html', project_info=db_project, directory=directory, name=project_name, download_URI=download_URI, type="graphic mode")

    # Ruta para ver los proyectos predeterminados en modo texto
    @app.route('/static_projects/text_mode/<project_name>/', methods=['GET', 'POST'])
    def show_static_project(project_name):

        # Trae el proyecto correspondiente al nombre de la db
        db_project = find_static_project({ 'program_title': project_name })

        if db_project is None:
            return render_template('404.html'), 404

        project_path = db_project['path']

        if request.method == 'POST':
            file = (request.get_json())['filename']
            path_file = (request.get_json())['path']
            file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c
            return jsonify(get_file_data(path_file, file, file_ext))

        # Muestra los directorios del proyecto correspondiente para ver los codigos
        directory = list_dir(route=project_path)
        download_URI = f'/download-static_project/{db_project["_id"]}'
        
        return render_template('show_static_project/index.html', project_info=db_project, directory=directory, name=project_name, download_URI=download_URI, type="text mode")
    
