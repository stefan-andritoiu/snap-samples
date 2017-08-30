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

var program = require('./usr/lib/nodejs/commander');
program
.version('1.0')
.option('-p, --screen_bus <n>', 'Insert screen bus number')
.parse(process.argv);

const mraa = require('./usr/lib/node_modules/mraa/mraa.node');
// Load lcd module on I2C
var LCD = require('./usr/lib/node_modules/jsupm_jhd1313m1/jsupm_jhd1313m1.node');

var screenBus;
switch (mraa.getPlatformType()) {
      case mraa.INTEL_JOULE_EXPANSION:
        screenBus = 0;
        console.log("Detected JOULE Board, instantiating jhd1313m1 on %d screen bus \n", screenBus);
        break;
      case mraa.INTEL_DE3815 :       //DE3815 + Arduino 1to1
        screenBus = 512;
        var res = mraa.addSubplatform(mraa.GENERIC_FIRMATA, "/dev/ttyACM0");
        if (res != mraa.SUCCESS){
        console.log("ERROR: Base platform DE3815 on port /dev/ttyACM0 for reason %d \n", res);
            }
        console.log("Detected DE3815 Board, instantiating jhd1313m1 on %d screen bus \n", screenBus);
        break;
      case mraa.INTEL_MINNOWBOARD_MAX:
        screenBus = 0;
        console.log("Detected MINNOWBOARD MAX Board, instantiating jhd1313m1 on %d screen bus \n", screenBus);
        break;
      default:
        if (program.screen_bus)
            if (parseInt(program.screen_bus))
                screenBus = parseInt(program.screen_bus);
            else 
                {
                console.log("Error, inserted arguments is not of type int");
                process.exit(1);
                }
        else
            { 
            console.log("Board not detected, please provide an int arg for the screen bus you want to instantiate jhd1313m1");
            process.exit(1);
            }        
        console.log("Board not detected, instantiating jhd1313m1 on %d screen bus \n", screenBus);
        break;
    }

// Initialize Jhd1313m1 at 0x62 (RGB_ADDRESS) and 0x3E (LCD_ADDRESS) 
var myLcd = new LCD.Jhd1313m1 (screenBus, 0x3E, 0x62);

myLcd.setCursor(0,0);
// RGB Blue
//myLcd.setColor(53, 39, 249);
// RGB Red
myLcd.setColor(255, 0, 0);
myLcd.write('Hello World');  
myLcd.setCursor(1,2);
myLcd.write('Hello World');
