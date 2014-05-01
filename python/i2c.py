import smbus
import time
import sys
import math
bus = smbus.SMBus(1)
pipe = open('/dev/input/event0', 'r')
address = 0x04
toExit = False
x = 0
msg = []
while not toExit:
	for char in pipe.read(1):
		msg+= [ord(char)]
		if len(msg) == 16:
			if msg[12] == 1 and msg[11] == 0:
				if 2 <= msg[10] <= 9:
					bus.write_byte(address, int(math.pow(2,msg[10]-2)))
					print int(math.pow(2,msg[10]-2))
				elif msg[10] == 10:
					bus.write_byte(address, 255)
					print "255"
				elif msg[10] == 11:
					bus.write_byte(address, 0)
					print "0"
			msg = []
