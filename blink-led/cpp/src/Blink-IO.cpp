/*
* Author: Flavian Manea <flavian.manea@rinftech.com>
* Copyright (c) 2017 Intel Corporation.
*
* Permission is hereby granted, free of charge, to any person obtaining
* a copy of this software and associated documentation files (the
* "Software"), to deal in the Software without restriction, including
* without limitation the rights to use, copy, modify, merge, publish,
* distribute, sublicense, and/or sell copies of the Software, and to
* permit persons to whom the Software is furnished to do so, subject to
* the following conditions:
*
* The above copyright notice and this permission notice shall be
* included in all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
* MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
* NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
* LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
* OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
* WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/

#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mraa.hpp"

static int iopin;
int running = 0;



bool set_board_pin() {
    mraa_platform_t platform = mraa_get_platform_type();
    switch (platform) {
      case MRAA_INTEL_JOULE_EXPANSION: 
        {
        iopin = 103;
        printf("Detected JOULE Board, flashing %d pin \n", iopin);
        return true;
        }
      case MRAA_INTEL_DE3815:       //DE3815 + Arduino 1to1
        {
        iopin = 13+512;
        mraa_result_t res = mraa_add_subplatform(MRAA_GENERIC_FIRMATA, "/dev/ttyACM0");
        if (res != MRAA_SUCCESS){
        printf("ERROR: Base platform %d on port /dev/ttyACM0 for reason %d \n", platform, res);
            }   
        printf("Detected DE3815 Board, flashing %d pin \n", iopin);
        return true;
        }
      case MRAA_INTEL_MINNOWBOARD_MAX:
        {
        iopin = 21;
        printf("Detected MINNOWBOARD MAX Board, flashing %d pin \n", iopin);
        //There is no onboard pin on MINNOBOARD max, so it is recommended to plug an led into pin 21
        return true;
        }
      default:
        // suggest the user to type a port from the keyboard
        return false;
    }
}
void
sig_handler(int signo)
{
    if (signo == SIGINT) {
        printf("closing IO%d nicely\n", iopin);
        running = -1;
    }
}
int
main(int argc, char** argv)
{
    bool board_found;
    board_found = set_board_pin();
    if (!board_found)
        if (argc < 2) {
             printf("Current board not detected, please provide an int arg for the pin you want to flash\n");
             return 0;
            } 
        else {
        iopin = strtol(argv[1], NULL, 10);
        }

    signal(SIGINT, sig_handler);
        
    //! [Interesting]
    mraa::Gpio* gpio = new mraa::Gpio(iopin);
    if (gpio == NULL) {
        return mraa::ERROR_UNSPECIFIED;
    }
    mraa::Result response = gpio->dir(mraa::DIR_OUT);
    if (response != mraa::SUCCESS) {
        mraa::printError(response);
        return 1;
    }

    while (running == 0) {
        response = gpio->write(1);
        sleep(1);
        response = gpio->write(0);
        sleep(1);
    }
    delete gpio;
    return response;
    //! [Interesting]
}
