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
#include <string>

#include "jhd1313m1.hpp"
#include "upm_utilities.h"

int shouldRun = true;

void sig_handler(int signo)
{
    if (signo == SIGINT)
        shouldRun = false;
}

int
main(int argc, char **argv)
{
    signal(SIGINT, sig_handler);
    int screenBus;
    mraa_platform_t platform = mraa_get_platform_type();
    switch (platform) {
        case MRAA_INTEL_JOULE_EXPANSION: 
            {
            screenBus = 0;
            printf("Detected JOULE Board, instantiating jhd1313m on %d bus \n",  screenBus);
            break;
            }
        case MRAA_INTEL_DE3815:       //DE3815 + Arduino 1to1
            {
            screenBus = 512; //Pin I2c with groveshield
            mraa_result_t res = mraa_add_subplatform(MRAA_GENERIC_FIRMATA, "/dev/ttyACM0");
            if (res != MRAA_SUCCESS){
            printf("ERROR: Base platform %d on port /dev/ttyACM0 for reason %d \n", platform, res);
                }   
            printf("Detected DE3815 Board, instantiating jhd1313m on %d bus \n",  screenBus);
            break;
            }
        case MRAA_INTEL_MINNOWBOARD_MAX:
            {
            screenBus = 0;
            printf("Detected MINNOWBOARD MAX Board, instantiating jhd1313m on %d bus \n",  screenBus);
            //There is no onboard pin on MINNOBOARD max, so it is recommended to plug an led into pin 21
            break;
            }
        default:
            if (argc < 2) {
            printf("Current board not detected, please provide an int arg for the bus you want to instantiate jhd1313m \n");
            return 0;
           } 
            else {
            screenBus = strtol(argv[1], NULL, 10);
        }
    }
    //! [Interesting]
    // 0x62 RGB_ADDRESS, 0x3E LCD_ADDRESS
    upm::Jhd1313m1 lcd(screenBus, 0x3E, 0x62);

    int ndx = 0;
    uint8_t rgb[7][3] = {
        {0xd1, 0x00, 0x00},
        {0xff, 0x66, 0x22},
        {0xff, 0xda, 0x21},
        {0x33, 0xdd, 0x00},
        {0x11, 0x33, 0xcc},
        {0x22, 0x00, 0x66},
        {0x33, 0x00, 0x44}};
    while (shouldRun)
    {
        // Alternate rows on the LCD
        lcd.setCursor(ndx%2,0);
        // Change the color
        uint8_t r = rgb[ndx%7][0];
        uint8_t g = rgb[ndx%7][1];
        uint8_t b = rgb[ndx%7][2];
        lcd.setColor(r, g, b);
        lcd.write("Hello World " + std::to_string(ndx));
        // Echo via printf
        printf("Hello World %d rgb: 0x%02x%02x%02x\n", ndx++, r, g, b);
        upm_delay(1);
    }

    //! [Interesting]
    return 0;
}
