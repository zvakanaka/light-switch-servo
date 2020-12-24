import change_direction
import RPi.GPIO as GPIO
import sys
import time

arg1 = str(sys.argv[1])

def get_degree(state):
    if state == 'on':
        return '6.5'
    elif state == 'off':
        return '2.4'

degree = get_degree(arg1)

change_direction.change_direction(degree)
time.sleep(0.25)
change_direction.change_direction('4.5')
GPIO.cleanup()

