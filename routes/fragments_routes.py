from flask import render_template

def fragments(app):
    @app.route('/add-fragment')
    def fragment_page():
        return render_template('user/add-fragment.html')
