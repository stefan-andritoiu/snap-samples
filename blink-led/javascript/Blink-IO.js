/*
 * Author: Dan Yocom <dan.yocom@intel.com>
 * Copyright (c) 2014 Intel Corporation.
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

"use strict";

var program = require('./usr/lib/nodejs/commander');
program
.version('1.0')
.option('-p, --pin_number <n>', 'Insert pin number')
.parse(process.argv);

const mraa = require('./usr/lib/node_modules/mraa/mraa.node'); //require mraa relative to the path where Blink-IO.js will be executed
console.log('MRAA Version: ' + mraa.getVersion()); //write the mraa version to the console



var iopin;
switch (mraa.getPlatformType()) {
      case mraa.INTEL_JOULE_EXPANSION:
        iopin = 103;
        console.log("Detected JOULE Board, flashing %d pin \n", iopin);
        break;
      case mraa.INTEL_DE3815 :       //DE3815 + Arduino 1to1
        iopin = 13+512;
        var res = mraa.addSubplatform(mraa.GENERIC_FIRMATA, "/dev/ttyACM0");
        if (res != mraa.SUCCESS){
        console.log("ERROR: Base platform DE3815 on port /dev/ttyACM0 for reason %d \n", res);
            }
        console.log("Detected DE3815 Board, flashing %d pin \n", iopin);
        break;
      case mraa.INTEL_MINNOWBOARD_MAX:
        iopin = 21;
        console.log("Detected MINNOWBOARD MAX Board, flashing %d pin \n", iopin);
        //There is no onboard pin on MINNOBOARD max, so it is recommended to plug an led into pin 21
        break;
      default:
        if (program.pin_number)
            if (parseInt(program.pin_number))
                iopin = parseInt(program.pin_number);
            else 
                {
                console.log("Error, inserted arguments is not of type int");
                process.exit(1);
                }
        else
            { 
            console.log("Board not detected, please insert the pin that you want to flash");
            process.exit(1);
            }        
        console.log("Board not detected, flashing %d pin \n", iopin);
        break;
    }



let myLed = new mraa.Gpio(iopin);
myLed.dir(mraa.DIR_OUT); //set the gpio direction to output
let ledState = true; //Boolean to hold the state of Led

function periodicActivity() {
    myLed.write(ledState ? 1 : 0); //if ledState is true then write a '1' (high) otherwise write a '0' (low)
    ledState = !ledState; //invert the ledState
}

setInterval(periodicActivity, 1000); //call the periodicActivity function every second
