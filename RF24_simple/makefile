all:
	g++ -g -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -L./RF24/  -lrf24-bcm switch.cpp -o remote
wire:
	g++ -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -L./RF24/librf24-rpi/librf24/  -lrf24 wireless.cpp -o wireless
lcd:
    g++ -g -Wall -Ofast -mfpu=vfp -mfloat-abi=hard -march=armv6zk -mtune=arm1176jzf-s -L./rpi-lcd/ -lrpi-lcd lcd.cpp ./rpi-lcd/gpio.c ./rpi-lcd/lcd.c ./rpi-lcd/lcd_lowlevel.c -o lcd
