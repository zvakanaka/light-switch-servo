# Light Switch Servo
# Command Line
Turn on:  
`$ python3 flip.py on`  
Turn off:  
`$ python3 flip.py off`
# Server
`$ env FLASK_APP=server.py flask run --host=0.0.0.0 --port=5000`  
Endpoints:  
http://raspberrypi:5000/on  
http://raspberrypi:5000/off  
Start server at boot:
`$ crontab -e`  
Crontab contents:  
```sh
DIR=/home/pi/light-switch-servo
@reboot echo $(date) >> $DIR/log.txt; cd $DIR && env FLASK_APP=$DIR/server.py flask run --host=0.0.0.0 --port=5000 >> $DIR/log.txt 2>> $DIR/log.txt
```
# Wii Remote
`A` is on and `B` is off:  
`$ python3 wiicontrol.py`

# Sources
https://flask.palletsprojects.com  
https://github.com/abstrakraft/cwiid  
https://github.com/the-raspberry-pi-guy/Wiimote  
https://www.thingiverse.com/thing:1156995
