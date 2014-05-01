//#define __STDC_FORMAT_MACROS
#include <cstdlib>
#include <iostream>
#include "./RF24/RF24.h"
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <inttypes.h>
#include <math.h>
#include <syslog.h>
#include <time.h>

using namespace std;
const uint64_t pipes[2] ={ 0xABCDABCD71LL, 0x544d52687CLL };
// NOPE: spi device, spi speed, ce gpio pin
// Radio pin, CE pin, speed
RF24 radio(RPI_V2_GPIO_P1_22, BCM2835_SPI_CS0, BCM2835_SPI_SPEED_8MHZ);
int fd;
struct input_event ev;
bool daemon_on = true;
void radio_setup(void)
{
    // init radio for reading
    radio.begin();
    //radio.enableDynamicPayloads();
    radio.setPayloadSize(1);
    radio.setAutoAck(1);
    radio.setRetries(0,15);
    radio.setDataRate(RF24_1MBPS);
    //radio.setPALevel(RF24_PA_MAX);
    //radio.setChannel(76);
    //radio.setCRCLength(RF24_CRC_16);
    radio.openReadingPipe(1,pipes[0]);
    radio.powerUp();
    radio.startListening();
    radio.printDetails();
    //radio.openReadingPipe(1,pipes[0]);
    //radio.openWritingPipe(pipes[1]);
}

signed long write_to_radio(uint64_t write_address, int value)
{
    radio.openWritingPipe(write_address);
    // Return 0 on no response, return time on success
    char gotByte[8];
    unsigned long start = millis();
    //radio.stopListening();
    // bool written = radio.write(&value,1);
    //syslog(LOG_INFO,"Wrote value: %i\r\n",value);
    if ( radio.write(&value,1) ) {

        if ( !radio.available() ) {
            syslog(LOG_INFO,"Got blank response, time %lu", millis() - start);
        } else {
            radio.read(&gotByte,1);
            syslog(LOG_INFO,"Got response %d, time %lu", gotByte, millis() - start);
        }
        return (millis() - start);
    }
    else {
        return 0;
    }
    radio.startListening();
}

int main(int argc, char** argv)
{
    /*if(argc < 2) {
        printf("usage: %s \n", argv[0]);
        return 1;
    }*/
    openlog("remote", LOG_PID|LOG_CONS, LOG_USER);
    radio_setup();
    pid_t pid, sid;
    // uint64_t newvar = pipes[0] + 16;
    fd = open("/dev/input/event0", O_RDONLY);
    printf("Reading on %#llx, writing to %#llx\n", pipes[0], pipes[1]);
    syslog(LOG_INFO, "Read on: %#llx write on: %#llx\n", pipes[0], pipes[1]);
    if (daemon_on) {
        /* Fork off the parent process */
        pid = fork();
        if (pid < 0) {
            exit(EXIT_FAILURE);
        }
        /* If we got a good PID, then
           we can exit the parent process. */
        if (pid > 0) {
            exit(EXIT_SUCCESS);
        }

        /* Change the file mode mask */
        umask(0);

        /* Open any logs here */

        /* Create a new SID for the child process */
        sid = setsid();
        if (sid < 0) {
            /* Log any failure here */
            exit(EXIT_FAILURE);
        }

        /* Change the current working directory */
        if ((chdir("/")) < 0) {
            /* Log any failure here */
            exit(EXIT_FAILURE);
        }


        /* Close out the standard file descriptors */
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
    }
    while(1) {
        // loop();
        read(fd, &ev, sizeof(struct input_event));
        if(ev.type == 1) {
            if (ev.value == 0) {
                int i = ev.code;
                // Select case on send value, one print statement at end
                int writeval = 0;
                if (i == 11) {
                    writeval = 0;
                } else if (i <= 10 && i >= 2) {
                    writeval = int((pow(2, i-2) - 1));
                } else {
                    writeval = 0;
                }
                syslog(LOG_INFO, "Sending %i\n", i);
                signed long ret_time = write_to_radio(pipes[1], writeval);
                if (ret_time==0) {
                    syslog(LOG_INFO, "Sending of %i failed\n", writeval);
                    //printf("Sending of %i failed\n", writeval);
                } else {
                    syslog(LOG_INFO, "Sent %i, got ACK, round-trip-delay: %lu ms\n", writeval, ret_time);
                    //printf("Sent %i, got ACK, round-trip-delay: %lu ms\n", writeval, ret_time);
                }
                ret_time = 0;
            }
        }
    }
    closelog();
    exit(EXIT_SUCCESS);
}

