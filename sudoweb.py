import subprocess
from flask import Flask, request, render_template

app = Flask(__name__, static_folder='web', template_folder='web', static_url_path='/static')

def formatSudokuOutput(lines):
        '''Format Sudosolver output to be displayed in HTML'''
        lines = lines.split('\n')
        lines.pop(0)
        lines = [line for line in lines if line != '']
        grid = [x for line in lines for x in line.split(' ') if x!='']
        grid = [x if x!='0' else '' for x in grid]
        return grid

@app.route('/')
def index():
        return render_template("index.html")

@app.route('/solve', methods=['GET', 'POST'])
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
                lines = subprocess.check_output(['./sudosolver.out', '-g', '9', str(cellCount)])
                grid = formatSudokuOutput(lines)
                
                #Return template
                return render_template("generate.html", grid=grid)
                
        
@app.route('/about')
def about():
        return render_template("about.html")

if __name__ == '__main__':
        app.run(threaded=True, debug=True)
