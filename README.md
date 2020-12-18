# Light Switch Servo
# Command Line
Turn on:  
`$ python3 flip.py on`  
Turn off:  
`$ python3 flip.py off`
# Server
`$ env FLASK_APP=server.py flask run --host=0.0.0.0 --port=5000`  
http://raspberrypi:5000/on  
http://raspberrypi:5000/off
# Wii Remote
`A` is on and `B` is off:  
`$ python3 wiicontrol.py`

# Sources
https://flask.palletsprojects.com  
https://github.com/abstrakraft/cwiid  
https://github.com/the-raspberry-pi-guy/Wiimote  
https://www.thingiverse.com/thing:1156995
