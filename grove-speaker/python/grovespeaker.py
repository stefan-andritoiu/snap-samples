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
from upm import pyupm_grovespeaker as upmGrovespeaker


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("--pin_number", help="add user specific pin number for instantiating Grove Speaker",
                        type=int)
    args = parser.parse_args()
    platform_name = mraa.getPlatformName()
    iopin = 0
    if platform_name == "Intel DE3815":
        iopin = 14 + 512
        error_platform = mraa.addSubplatform(mraa.GENERIC_FIRMATA, "/dev/ttyACM0")
        if error_platform != mraa.SUCCESS:
            print ("ERROR: Base platform INTEL_DE3815 on port /dev/ttyACM0 for reason %s" % error_platform)
        print ("Detected DE3815 Board, instantiating Grove Speaker %s pin" % iopin)
    elif platform_name == "INTEL JOULE EXPANSION":
        iopin = 20
        print ("Detected Joule Board, instantiating Grove Speaker %s pin" % iopin)
    elif platform_name == "MinnowBoard MAX":
        iopin = 21
        print ("Detected MinnowBoard MAX Board, instantiating Grove Speaker %s pin" % iopin)
    elif args.pin_number:
        iopin = args.pin_number
    else:
        print ("Current board not detected, please provide an int arg for the pin you want to instantiate Grove Speaker")
        exit()
    # Instantiate a Grove Speaker on digital pin 20 from Intel Joule
    mySpeaker = upmGrovespeaker.GroveSpeaker(iopin)

    # Play all 7 of the lowest notes
    mySpeaker.playAll()

    # Play a medium C-sharp
    mySpeaker.playSound('c', True, "med")

if __name__ == '__main__':
    main()
