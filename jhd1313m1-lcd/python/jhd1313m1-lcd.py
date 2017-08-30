#!/usr/bin/env python
# Author: Flavian Manea <flavian.manea@rinftech.com>
# Copyright (c) 2017 Intel Corporation.
#
# Permission is hereby granted, free of charge, to any person obtaining
# a copy of this software and associated documentation files (the
# "Software"), to deal in the Software without restriction, including
# without limitation the rights to use, copy, modify, merge, publish,
# distribute, sublicense, and/or sell copies of the Software, and to
# permit persons to whom the Software is furnished to do so, subject to
# the following conditions:
#
# The above copyright notice and this permission notice shall be
# included in all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
# EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
# MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
# NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
# LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION
# OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
# WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

from __future__ import print_function
import argparse
import mraa
from upm import pyupm_jhd1313m1 as lcd


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--screen_bus", help="add user specific screen bus  for instantiating jhd1313m1",
                        type=int)
    args = parser.parse_args()
    platform_name = mraa.getPlatformName()
    screenBus = 0
    if platform_name == "Intel DE3815":
        screenBus = 0 + 512
        error_platform = mraa.addSubplatform(mraa.GENERIC_FIRMATA, "/dev/ttyACM0")
        if error_platform != mraa.SUCCESS:
            print ("ERROR: Base platform INTEL_DE3815 on port /dev/ttyACM0 for reason %s" % error_platform)
        print ("Detected DE3815 Board, instantiating jhd1313m1 %s screen bus" % screenBus)
    elif platform_name == "INTEL JOULE EXPANSION":
        screenBus = 0
        print ("Detected Joule Board, instantiating jhd1313m1 %s screen bus" % screenBus)
    elif platform_name == "MinnowBoard MAX":
        screenBus = 0
        print ("Detected MinnowBoard MAX Board, instantiating jhd1313m1 %s screen bus" % screenBus)
    elif args.screen_bus:
        screenBus = args.screen_bus
    else:
        print ("Current board not detected, please provide an int arg for the screen bus you want to instantiate jhd1313m1")
        exit()
    # Initialize Jhd1313m1 at 0x3E (LCD_ADDRESS) and 0x62 (RGB_ADDRESS) and screenBus based on detected platform 
    myLcd = lcd.Jhd1313m1(screenBus, 0x3E, 0x62)

    myLcd.setCursor(0,0)

    # RGB Red
    myLcd.setColor(255, 0, 0)

    myLcd.write('Hello World')
    myLcd.setCursor(1,2)
    myLcd.write('Hello World')

if __name__ == '__main__':
    main()
