/*
 * Author: Brendan Le Foll <brendan.le.foll@intel.com>
 * Author: Thomas Ingleby <thomas.c.ingleby@intel.com>
 * Copyright (c) 2014 Intel Corporation.
 * Author: Petre Eftime <petre.p.eftime@intel.com>
 * Copyright (c) 2015 Intel Corporation.
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


import mraa.Dir;
import mraa.Gpio;
import mraa.Result;
import mraa.mraa;
import mraa.Platform;

public class BlinkIO {
    static {
        try {
            System.loadLibrary("mraajava");
        } catch (UnsatisfiedLinkError e) {
            System.err.println(
                    "Native code library failed to load. See the chapter on Dynamic Linking Problems in the SWIG Java documentation for help.\n" +
                            e);
            System.exit(1);
        }
    }

    public static void main(String argv[]) throws InterruptedException {
        int iopin;
        Platform platform = mraa.getPlatformType();
        if (platform == Platform.INTEL_JOULE_EXPANSION) {  
                     iopin = 103;
                     System.out.println("Detected JOULE Board, flashing " + iopin + " pin \n ");
                    }
        else if (platform == Platform.INTEL_DE3815){              
                     iopin = 13+512;
                     Result sublplatformResult =  mraa.addSubplatform(Platform.GENERIC_FIRMATA, "/dev/ttyACM0");
                     if (sublplatformResult != Result.SUCCESS)
                        {
                        System.out.println("ERROR: Base platform INTEL_DE3815 on port /dev/ttyACM0 for reason" + sublplatformResult);                        
                        }
                     System.out.println("Detected DE3815 Board, flashing " + iopin + " pin \n ");
                    }
            else if (platform == Platform.INTEL_MINNOWBOARD_MAX){             
                     iopin = 21;
                     System.out.println("Detected MINNOWBOARD MAX Board, flashing " + iopin + " pin \n ");
                    }
                 else if (argv.length == 0) {
                        iopin = 0;
                        System.out.println("Current board not detected, please provide an int arg for the pin you want to flash\n");
                        System.exit(1);
                    } 
                      else {
                      iopin = Integer.valueOf(argv[0]);
                      }

        //! [Interesting]
        Gpio gpio = new Gpio(iopin);
        Result result = gpio.dir(Dir.DIR_OUT);
        if (result != Result.SUCCESS) {
            mraa.printError(result);
            System.exit(1);
        }

        while (true) {
            gpio.write(1);
            Thread.sleep(1000);
            gpio.write(0);
            Thread.sleep(1000);
        }
        //! [Interesting]
    }
}
