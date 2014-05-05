import RPi.GPIO as GPIO
import time
import os
GPIO.setmode(GPIO.BCM)
GPIO.setup(18, GPIO.OUT)
GPIO.setup(27, GPIO.IN, pull_up_down = GPIO.PUD_UP)
p = GPIO.PWM(18, 5000)
def Int_shutdown(channel):
	p.start(99)
	time.sleep(1)
	p.stop()
	os.system("sudo shutdown -h now")
GPIO.add_event_detect(27, GPIO.FALLING, callback = Int_shutdown, bouncetime = 2000)
while 1:
	time.sleep(1)
