#!/bin/bash
g++ -g -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -L./rpi-lcd/ -lrpi-lcd $1.cpp -o $1 
#./rpi-lcd/gpio.c ./rpi-lcd/lcd.c ./rpi-lcd/lcd_lowlevel.c
