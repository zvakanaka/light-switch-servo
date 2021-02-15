# This is a server that runs on MicroPython on the ESP8266
from machine import Pin, PWM
import time
import socket
addr = socket.getaddrinfo('0.0.0.0', 80)[0][-1]
servo = PWM(Pin(14), freq=50, duty=77)

# max is 90 and min is 35
ON = 85
OFF = 45
NEUTRAL = int((ON + OFF) / 2)

def get_html(state):
    color = 'black' if state is 'on' else 'white'
    background = 'white' if state is 'on' else 'black'
    title = 'On' if state is 'on' else 'Off'
    opposite = 'off' if state is 'on' else 'on'
    return """<!DOCTYPE html>
<html>
    <head> <title>Light Switch</title>
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
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
</head>
<body>
<div class="control"><h1><a href="./{state}" style="text-decoration: none; color: unset;">{title}</a></h1><a href="./{opposite}">Turn {opposite}</a></div>
</body>
</html>
""".format(color=color,background=background,state=state,title=title,opposite=opposite)

s = socket.socket()
# this allows reuse of the port if this server crashes
# see https://github.com/micropython/micropython/issues/3739#issuecomment-386191815
s.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
s.bind(addr)
s.listen(1)

print('light switch server listening on', addr)

while True:
    cl, addr = s.accept()
    print('client connected from', addr)
    cl_file = cl.makefile('rwb', 0)
    response = 'unknown error'
    while True:
        line = cl_file.readline()
        if not line or line == b'\r\n':
            break
        elif line.startswith(b'GET /off '):
            print('turning on the light')
            servo.duty(OFF)
            time.sleep(1)
            servo.duty(NEUTRAL)
            response = get_html('off')
        elif line.startswith(b'GET /on '):
            print('turning off the light')
            servo.duty(ON)
            time.sleep(1)
            servo.duty(NEUTRAL)
            response = get_html('on')
    if response is 'unknown error':
      cl.send('HTTP/1.0 500 Internal Server Error\r\nContent-type: text/html\r\n\r\n')
    else:
      cl.send('HTTP/1.0 200 OK\r\nContent-type: text/html\r\n\r\n')
    cl.send(response)
    cl.close()
