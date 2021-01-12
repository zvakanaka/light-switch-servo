<!-- This is how I created the [virtual enviroment](https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/#creating-a-virtual-environment): -->
<!-- `$ python3 -m venv env` -->
<!-- `$ pip freeze > requirements.txt` -->
# ESP8266 Light Switch Servo
## Flash MicroPython
`$ git clone https://github.com/zvakanaka/light-switch-servo`  
`$ cd light-switch-servo/esp8266`  
`$ pip install -r requirements.txt`  
Download the appropriate firmware from [here](https://micropython.org/download/esp8266/).  
`$ esptool.py --port /dev/ttyUSB0 --baud 115200 write_flash --flash_size=detect 0 esp8266-20200911-v1.13.bin`

## Connect to Serial Console over USB
`$ picocom /dev/ttyUSB0 -b115200`

## Get the SG90 Servo Working
https://micropython-on-esp8266-workshop.readthedocs.io/en/latest/basics.html#servomechanisms

## Set up Network (automatically saves)
```python
import network
sta = network.WLAN(network.STA_IF)
sta.active(True)
sta.connect("name", "password")
```

## Serve the WebREPL
You can use [this hosted version](http://micropython.org/webrepl/).  
Or serve it [yourself](https://micropython-on-esp8266-workshop.readthedocs.io/en/latest/basics.html#webrepl).

Upload `main.py` so it will run when booted.

[Ampy](https://learn.adafruit.com/micropython-basics-load-files-and-run-code/install-ampy) can be used instead of the WebREPL to upload code over serial connection.
