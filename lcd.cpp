#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <getopt.h>
#include <time.h>
#include <unistd.h>
#include "rpi_lcd/lcd.c"

/*#include "rpi-lcd/button.h"
#include "rpi-lcd/lcd.h"
#include "rpi-lcd/lcd_cgram.h"
#include "rpi-lcd/gpio.h"*/
#define ADDR 0x20
int colors[7] = {RED,GREEN,BLUE,YELLOW,TEAL,VIOLET,OFF};
int i = 0;
int main()
{
    lcdSetup(ADDR,1);
    lcdBacklight(ON);
    lcdClear();
    lcdMessage("Hello, world!");
    //LCD_init(0);
    while(1) {
    lcdBacklight(colors[i]);
    i++;
    if (i == 7) {
        i = 0;
    }
    sleep(1);
/*
        if(lcdButtonPressed(SELECT)) {
            lcdBacklight(OFF);
            lcdClear();
            lcdMessage("Select");
            lcdBacklight(RED);
        }
        if(lcdButtonPressed(RIGHT)) {
            lcdBacklight(OFF);
            lcdClear();
            lcdMessage("Right");
            lcdBacklight(BLUE);
        }*/
    }
}

