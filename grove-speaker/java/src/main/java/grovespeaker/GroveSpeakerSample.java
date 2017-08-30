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

import mraa.Result;
import mraa.mraa;
import mraa.Platform;

public class GroveSpeakerSample {

    public static void main(String argv[]) throws InterruptedException {

        int iopin=0;
        Platform platform = mraa.getPlatformType();
        if (platform == Platform.INTEL_JOULE_EXPANSION) {  
                     iopin = 20;
                     System.out.println("Detected JOULE Board, instantiating Grove Speaker on " + iopin + " pin \n ");
                    }
        else if (platform == Platform.INTEL_DE3815){              
                     iopin = 14+512;
                     Result sublplatformResult =  mraa.addSubplatform(Platform.GENERIC_FIRMATA, "/dev/ttyACM0");
                     if (sublplatformResult != Result.SUCCESS)
                        {
                        System.out.println("ERROR: Base platform INTEL_DE3815 on port /dev/ttyACM0 for reason" + sublplatformResult);                        
                        }
                     System.out.println("Detected DE3815 Board, instantiating Grove Speaker on " + iopin + " pin \n ");
                    }
        else if (platform == Platform.INTEL_MINNOWBOARD_MAX){             
                     iopin = 21;
                     System.out.println("Detected MINNOWBOARD MAX Board, instantiating Grove Speaker on " + iopin + " pin \n ");
                    }
        else if (argv.length == 0) {
                     System.out.println("Current board not detected, please provide an int arg for the pin you want instantiate Grove Speaker \n");
                     System.exit(1);
                    } 
            else {   
                     try {    
                        iopin = Integer.valueOf(argv[0]);
                        }
                     catch (NumberFormatException e)  {
                        System.out.println("Inserted pin is not a integer type");  
                        System.exit(1);  
                        }
                     System.out.println("Current board not detected, instantiating Grove Speaker on " + iopin + " pin \n ");
                 }
        
        // ! [Interesting]
        // Instantiate a Grove Speaker on pin based on detected platform
        upm_grovespeaker.GroveSpeaker speaker = new upm_grovespeaker.GroveSpeaker(iopin);

        // Play all 7 of the lowest notes
        speaker.playAll();

        // Play a medium C-sharp
        speaker.playSound('c', true, "med");
        // ! [Interesting]
    }

}
