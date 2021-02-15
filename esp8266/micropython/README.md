<!-- This is how I created the [virtual enviroment](https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/#creating-a-virtual-environment): -->
<!-- `$ python3 -m venv env` -->
<!-- `$ pip freeze > requirements.txt` -->

## Flash Micropython
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
You can use [this hosted version](https://zvakanaka.github.io/light-switch-servo/webrepl.html).  
Or serve it [yourself](https://micropython-on-esp8266-workshop.readthedocs.io/en/latest/basics.html#webrepl).

Upload your main.py server to it.