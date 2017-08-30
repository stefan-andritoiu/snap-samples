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
import time
import sys
import signal
import atexit
from upm import pyupm_grovelinefinder as upmGrovelinefinder


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--pin_number", help="add user specific pin number for instantiating Grove Line Finder",
                        type=int)
    args = parser.parse_args()
    platform_name = mraa.getPlatformName()
    iopin = 0
    if platform_name == "Intel DE3815":
        iopin = 14 + 512
        error_platform = mraa.addSubplatform(mraa.GENERIC_FIRMATA, "/dev/ttyACM0")
        if error_platform != mraa.SUCCESS:
            print ("ERROR: Base platform INTEL_DE3815 on port /dev/ttyACM0 for reason %s" % error_platform)
        print ("Detected DE3815 Board, instantiating Grove Line Finder %s pin" % iopin)
    elif platform_name == "INTEL JOULE EXPANSION":
        iopin = 20
        print ("Detected Joule Board, instantiating Grove Line Finder %s pin" % iopin)
    elif platform_name == "MinnowBoard MAX":
        iopin = 21
        print ("Detected MinnowBoard MAX Board, instantiating Grove Line Finder %s pin" % iopin)
    elif args.pin_number:
        iopin = args.pin_number
    else:
        print ("Current board not detected, please provide an int arg for the pin you want to instantiate Grove Line Finder")
        exit()
    # Instantiate a Grove line finder sensor on pin based on platform type
    myLineFinder = upmGrovelinefinder.GroveLineFinder(iopin)

    ## Exit handlers ##
    # This function stops python from printing a stacktrace when you hit control-C
    def SIGINTHandler(signum, frame):
        raise SystemExit

    # This function lets you run code on exit, including functions from myLineFinder
    def exitHandler():
        print("Exiting")
        sys.exit(0)

    # Register exit handlers
    atexit.register(exitHandler)
    signal.signal(signal.SIGINT, SIGINTHandler)

    while(1):
        if (myLineFinder.whiteDetected()):
            print("White detected.")
        else:
            print("Black detected.")
        time.sleep(1)


if __name__ == '__main__':
    main()
