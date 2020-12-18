# env FLASK_APP=server.py flask run --host=0.0.0.0 --port=5001
from flask import Flask
import os

app = Flask(__name__)

def get_style(state):
    color = 'black' if state is 'on' else 'white'
    background = 'white' if state is 'on' else 'black'
    return f"""<meta name="viewport" content="width=device-width, initial-scale=1.0">
<style>
    body {{ margin: 0; color: {color}; background: {background}; }}
    .control {{
      display: flex;
      justify-content: center;
      align-items: center;
      flex-direction: column;
      height: 100vh;
    }}
</style>
"""

def render_page(state):
    title = 'On' if state is 'on' else 'Off'
    opposite = 'off' if state is 'on' else 'on'
    style = get_style(state)
    return f'''
<div class="control">{style}<h1><a href="./{state}" style="text-decoration: none; color: unset;">{title}</a></h1><a href="./{opposite}">Turn {opposite}</a></div>
'''

@app.route('/on')
def flip_on():
    os.system('python flip.py on')
    return render_page('on')

@app.route('/off')
def flip_off():
    os.system('python flip.py off')
    return render_page('off')
