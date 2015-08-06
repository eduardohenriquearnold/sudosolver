import os
import subprocess
import random
import string
import base64
from flask import Flask, request, render_template

##################
#Helper Functions
##################

def rnd_str(size=6, chars=string.ascii_uppercase + string.digits):
        '''Random string generator'''
        return ''.join(random.choice(chars) for _ in range(size))
        
def formatSudokuOutput(lines):
        '''Format Sudosolver output to be displayed in HTML'''
        lines = lines.split('\n')
        
        if len(lines) < 9:
                return None      
                  
        lines = lines[lines.index('9')+1:]
        lines = [line for line in lines if line != '']
        grid = [x for line in lines for x in line.split(' ') if x!='']
        grid = [x if x!='0' else '' for x in grid]
        return grid

#########
#Web App
#########

app = Flask(__name__, static_folder='web', template_folder='web', static_url_path='/static')

@app.route('/')
def index():
        return render_template("index.html")

@app.route('/solve', methods=['GET', 'POST'])
def solve():
        if request.method == 'GET':
                return render_template("solve.html")
        else:
                f = request.files.get('file', None)
                pic = request.form.get('picture', None)
                txt = request.form.get('sudotext', None)   
                
                err = None
                
                #Image file                
                if f:
                        #Save file
                        f = request.files['file']
                        fname, ext = os.path.splitext(f.filename)
                        ext = ext.lower()
                        
                        if ext in ['.jpg', '.jpeg', '.png']:
                                path = 'temp/'+rnd_str()+ext
                                f.save(path)
                        else:
                                err = 'Invalid image extension.'                                
                                
                #Online picture
                if pic:
                        #Save file as png
                        path = 'temp/'+rnd_str()+'.png'
                        fl = open(path, 'wb')
                        pic = pic[pic.find('base64,')+7:]
                        fl.write(base64.b64decode(pic))
                        fl.close()
                                        
                #Image processing
                if f or pic:                
                        #Process image
                        lines = subprocess.check_output(['./sudosolver.out', '-i', path])
                        os.remove(path)
                        grid = formatSudokuOutput(lines)
                        if grid is None:
                                err = lines
                                
                #Manual text input
                if txt:
                        #Write file
                        path = 'temp/'+rnd_str()+'.txt'
                        f = open(path, 'w')
                        f.write('9\n')
                        f.write(txt)
                        f.close()
                        
                        #Process file
                        lines = subprocess.check_output(['./sudosolver.out', '-s', path])
                        os.remove(path)
                        grid = formatSudokuOutput(lines)
                        if grid is None:
                                err = lines                        
                
                return render_template("solve.html", grid=grid, err=err)
        
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
        app.run(host='0.0.0.0',threaded=True, debug=True)
