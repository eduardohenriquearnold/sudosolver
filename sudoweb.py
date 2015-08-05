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
                #Generate Sudoku
                emptyCellCount = int(request.form[u'empty-cell-count'])
                cellCount = 81-emptyCellCount
                gen = subprocess.check_output(['./sudosolver.out', '-g', '9', str(cellCount)])
                
                #Format output
                lns = gen.split('\n')
                lns.pop(0)
                grid = [row for row in lns if row != '']
                grid = [x for row in grid for x in row.split(' ') if x!='']
                grid = [x if x!='0' else '' for x in grid]
                
                #Return template
                return render_template("generate.html", grid=grid)
                
        
@app.route('/about')
def about():
        return render_template("about.html")

if __name__ == '__main__':
        app.run(debug=True)
