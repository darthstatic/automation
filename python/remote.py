import sys

pipe = open('/dev/input/event0', 'r')

msg = []
final = []
x = 0
while 1:
	for char in pipe.read(1):
		msg += [ord(char)]
		if len(msg) == 16:
			if msg[12] == 1:
				print msg[10] + msg[11] * 256
			'''del msg[0:8]
			print msg
			if msg[4] == 1:
				print msg
			else:
				del msg
			
			if msg[8] == 4:
				print 'event start'
			elif msg[8] == 1:
				print 'button', msg[10], 'down'
			else:
				print 'button', msg[10], 'up'
			'''
			msg = []
			
