import subprocess
from flask import Flask, request, render_template

app = Flask(__name__, static_folder='web', template_folder='web', static_url_path='/static')

@app.route('/')
def index():
        return render_template("index.html")

@app.route('/solve')
def solve():
        if request.method == 'GET':
                return render_template("solve.html")
        
@app.route('/generate', methods=['GET','POST'])
def generate():
        if request.method == 'GET':
                return render_template("generate.html")
        else:
                emptyCellCount = irequest.form[u'empty-cell-count']
                
                
        
@app.route('/about')
def about():
        return render_template("about.html")

if __name__ == '__main__':
        app.run(debug=True)
