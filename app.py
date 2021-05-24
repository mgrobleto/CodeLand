from flask import Flask, render_template

app = Flask(__name__)

@app.route('/', methods= ['GET'])
def home():
    return render_template('index.html')

@app.route('/login', methods= ['GET', 'POST'])
def login():
    return render_template('login/index.html')

app.run(debug=True)
