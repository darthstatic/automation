#include <cstdlib>
#include <iostream>
#include "./RF24/librf24-rpi/librf24/RF24.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>

using namespace std;
const uint64_t pipes[2] =  { 0xABCDABCD71LL, 0x544d52687CLL };
char *device = NULL;
// spi device, spi speed, ce gpio pin
// RF24 radio("/dev/spidev0.0",8000000,25);
struct input_event ev[64];
int fd, rd, value, size=sizeof(struct input_event);;
char name[256] = "Unknown";
void setup(void)
{
    // init radio for reading
    /*radio.begin();
    radio.enableDynamicPayloads();
    radio.setAutoAck(1);
    radio.setRetries(15,15);
    radio.setDataRate(RF24_1MBPS);
    radio.setPALevel(RF24_PA_MAX);
    radio.setChannel(76);
    radio.setCRCLength(RF24_CRC_16);
    radio.openReadingPipe(1,pipes[0]);
    radio.openWritingPipe(pipes[1]);*/

}
void handler (int sig) {
    printf("nexiting...(%d)n", sig);
    exit (0);
}
void perror_exit (char *error) {
    perror (error);
    handler(9);
}
void loop(void)
{
    /*char gotByte[8];
    unsigned long time = __millis();
    time = __millis();
    for(int i=0;i<=255;i=i+10) {
      printf("This is integer %i with size %i\r\n",i, sizeof(i));
      if ( radio.write(&i,2) ) {
        if(!radio.available()) {
          printf("Got blank response. delay: %lu ms\n\r",__millis()-time);
        }
        else{
          while(radio.available()){
            radio.read(&gotByte,2);
            printf("Got response %s, round-trip delay: %lu ms\n\r",gotByte,__millis()-time);
          }
        }
      }
      else {
        printf("Sending failed.\r\n");
      }
      sleep(1);
    }*/
}

int main(int argc, char** argv)
{
    printf("This should print");
    // setup();
    if (argv[1] == NULL){
        printf("Please specify (on the command line) the path to the dev event interface devicen");
        exit (0);
    }
    if ((getuid ()) != 0)
        printf ("You are not root! This may not work...n");

    if (argc > 1)
        device = argv[1];

    if ((fd = open(device, O_RDONLY)) == -1)
        printf("%s is not a valid device.n", device);
    //Print Device Name
    ioctl(fd, EVIOCGNAME (sizeof (name)), name);
    printf("Reading From : %s (%s)n", device, name);

    while(1)
        // loop();
        if ((rd = read(fd,ev,size*64)) < size)
            perror_exit("read()");
        value = ev[0].value;
        if (value != ' ' && ev[1].value == 1 && ev[1].type == 1) {
            printf("Code[%d]n", (ev[1].code));
        }
    return 0;
}

