from flask import render_template, request, jsonify
from services.project import list_dir, get_file_data

from services.documentation import find_document
from services.fragments import find_ejemplos
from services.project import find_static_project, find_project


def examples(app):
    #para la parte de documentacion
    @app.route('/examples/basicos')
    def documentacion():
        db_documentation = find_document('document')
        return render_template("pdf/documentacion.html",db_documentation=db_documentation)

    # Ruta para ver ejemplos
    @app.route('/example/<ejemplo_name>/', methods=['GET', 'POST'])
    def show_ejemplo(ejemplo_name):

        # Trae el ejemplo correspondiente al nombre de la db
        db_example = find_ejemplos({ 'example_name': ejemplo_name })

        if db_example is None:
            return render_template('404.html'), 404

        example_path = db_example['path']

        if request.method == 'POST':

            file = (request.get_json())['filename']
            path_file = (request.get_json())['path']
            file_ext = file.split('.')[-1] # Siempre va a elegir la ultima extensión, por si el nombre es name.something.c

            return jsonify(get_file_data(path_file, file, file_ext))

        # Muestra los directorios del proyecto correspondiente para ver los codigos
        directory = list_dir(route=example_path)
        download_URI = f'/download-example/{db_example["_id"]}'

        return render_template('show_ejemplo/index.html', example_info=db_example, directory=directory, name=ejemplo_name, download_URI=download_URI, type="text mode")

    
    @app.route('/examples/intro')
    def text_mode():

        db_project = find_static_project({'mode': 'text_mode'})
        db_project_user = find_project({"mode": "text_mode"})

        if db_project is None:
            return render_template('404.html'), 404

        return render_template("text_mode/text.html", db_project=db_project, db_project_user=db_project_user)

    #Cuando se consulte en el modo grafico
    @app.route('/examples/node')
    def graphic_mode():
        db_project = find_static_project({'mode': 'graphic_mode'})
        db_project_user = find_project({"mode": "graphic_mode"})

        return render_template("graphic_mode/graphic.html", db_project=db_project, db_project_user=db_project_user)

