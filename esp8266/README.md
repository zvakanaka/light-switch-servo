<!-- This is how I created the [virtual enviroment](https://packaging.python.org/guides/installing-using-pip-and-virtual-environments/#creating-a-virtual-environment): -->
<!-- `$ python3 -m venv env` -->
<!-- `$ pip freeze > requirements.txt` -->

## Flash Micropython
`$ git clone https://github.com/zvakanaka/light-switch-servo`  
`$ cd light-switch-servo/esp8266`  
`$ pip install -r requirements.txt`  

## Get the SG90 Servo Working
https://micropython-on-esp8266-workshop.readthedocs.io/en/latest/basics.html#servomechanisms

## Set up the Network (automatically saves)
```python
import network
sta = network.WLAN(network.STA_IF)
sta.active(True)
sta.connect("ap name", "password")
```

## Serve the WebREPL
You can use [this hosted version](https://zvakanaka/github.io/webrepl.html).  
Or serve it [yourself](https://micropython-on-esp8266-workshop.readthedocs.io/en/latest/basics.html#webrepl).

Upload your main.py server to it.