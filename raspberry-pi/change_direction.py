import RPi.GPIO as GPIO
import time
import signal

servopin = 40
GPIO.setmode(GPIO.BOARD)
GPIO.setup(servopin, GPIO.OUT, initial=False)
p = GPIO.PWM(servopin,50) 
p.start(0)
time.sleep(0.5)

def change_direction(degree):
    degree = float(degree)
    p.ChangeDutyCycle(degree)
    time.sleep(0.02)
    time.sleep(1)
    p.ChangeDutyCycle(0)

    
