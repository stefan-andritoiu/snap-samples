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
.option('-p, --pin_number <n>', 'Insert pin number')
.parse(process.argv);

const mraa = require('./usr/lib/node_modules/mraa/mraa.node');
var lineFinderSensor = require('./usr/lib/node_modules/jsupm_grovelinefinder/jsupm_grovelinefinder.node');

var iopin;
switch (mraa.getPlatformType()) {
      case mraa.INTEL_JOULE_EXPANSION:
        iopin = 20;
        console.log("Detected JOULE Board, instantiating Grove Line Finder on %d pin \n", iopin);
        break;
      case mraa.INTEL_DE3815 :       //DE3815 + Arduino 1to1
        iopin = 14 + 512;
        var res = mraa.addSubplatform(mraa.GENERIC_FIRMATA, "/dev/ttyACM0");
        if (res != mraa.SUCCESS){
        console.log("ERROR: Base platform DE3815 on port /dev/ttyACM0 for reason %d \n", res);
            }
        console.log("Detected DE3815 Board, instantiating Grove Line Finder on %d pin \n", iopin);
        break;
      case mraa.INTEL_MINNOWBOARD_MAX:
        iopin = 21;
        console.log("Detected MINNOWBOARD MAX Board, instantiating Grove Line Finder on %d pin \n", iopin);
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
            console.log("Board not detected, please provide an int arg for the screen bus you want to instantiate Grove Line Finder");
            process.exit(1);
            }        
        console.log("Board not detected, instantiating Grove Line Finder on %d pin \n", iopin);
        break;
    }


// Instantiate a Grove line finder sensor on pin based on detected platform
var myLineFinderSensor = new lineFinderSensor.GroveLineFinder(iopin);

// Check every second for the presence of white detection
setInterval(function()
{
	if (myLineFinderSensor.whiteDetected())
		console.log("White detected.");
	else
		console.log("Black detected.");
}, 1000);

// Turn relay off when exiting
process.on('SIGINT', function()
{
	console.log("Exiting...");
	process.exit(0);
});
