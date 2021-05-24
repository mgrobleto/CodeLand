from db import database
from models.user import Users
from flask import Flask, render_template

app = Flask(__name__)
# init database
database()

@app.route('/', methods= ['GET'])
def home():
    return render_template('index.html')

@app.route('/login', methods= ['GET', 'POST'])
def login():
    user = Users.objects.get_or_404(name="Miguel")
    return render_template('login/index.html', user=user)

app.run(debug=True)
