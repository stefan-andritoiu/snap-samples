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

#include <unistd.h>
#include <iostream>
#include <signal.h>
#include "grovespeaker.hpp"

using namespace std;

static int iopin;

bool set_board_pin() {
  mraa_platform_t platform = mraa_get_platform_type();
  switch (platform) {
    case MRAA_INTEL_JOULE_EXPANSION: 
      {
      iopin = 20;
      printf("Detected JOULE Board, instantiating Grove Speaker on %d pin \n",  iopin);
      return true;
      }
    case MRAA_INTEL_DE3815:       //DE3815 + Arduino 1to1
      {
      iopin = 14+512; //Pin A0 with groveshield
      mraa_result_t res = mraa_add_subplatform(MRAA_GENERIC_FIRMATA, "/dev/ttyACM0");
      if (res != MRAA_SUCCESS){
      printf("ERROR: Base platform %d on port /dev/ttyACM0 for reason %d \n", platform, res);
          }   
      printf("Detected DE3815 Board, instantiating Grove Speaker on %d pin \n",  iopin);
      return true;
      }
    case MRAA_INTEL_MINNOWBOARD_MAX:
      {
      iopin = 21;
      printf("Detected MINNOWBOARD MAX Board, instantiating Grove Speaker on %d pin \n",  iopin);
      return true;
      }
    default:
      // suggest the user to type a port from the keyboard
      return false;
  }
}


int main(int argc, char** argv)
{
  
  bool board_found;
  board_found = set_board_pin();
  if (!board_found)
      if (argc < 2) {
           printf("Current board not detected, please provide an int arg for the pin you want to instantiate Grove Speaker\n");
           return 0;
          } 
      else {
      iopin = strtol(argv[1], NULL, 10);
      }
//! [Interesting]
  // Instantiate a Grove Speaker sensor based on detected platform
  upm::GroveSpeaker* speaker = new upm::GroveSpeaker(iopin);

  // Play all 7 of the lowest notes
  speaker->playAll();

  // Play a medium C-sharp
  speaker->playSound('c', true, "med");

//! [Interesting]

  cout << "Exiting" << endl;

  delete speaker;
  return 0;
}
