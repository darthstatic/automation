import RPi.GPIO as GPIO
import time
import os
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
p = GPIO.PWM(18, 5000)
p.start(99)
time.sleep(1)
p.stop()
GPIO.cleanup()
