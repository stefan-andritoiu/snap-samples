# grove-linefinder  

This example is intended to make use of the Grove Line Finder sensor and Intel® Joule Expansion Board.

# Basic Wiring

1. Connect a jumper wire between;
	* Pin 42 (pin 2 on the Joule's JI3)
	* The 5V pin on your Grove shield
2. Connect a jumper wire between;
	* Pin 41 (pin 1 on the Joule's JI3)
	* Any of the GND pins on your Grove shield
3. Connect a jumper wire between;
	* Pin 20 (on the Joule's JI2)
	* The SIG pin on your Grove shield


![Grove-linefinder diagram](grove-linefinder-diagram.jpg?raw=true "Grove-linefinder diagram")


![Grove-linefinder example](grove-linefinder-real-example.jpg?raw=true "Grove-linefinder example")



# Build project
After succesfully installing snapcraft as a snap package, run the following command in the desired language folder:
```sh
$ sudo snap run snapcraft
```

# Install project

This will generate a *.snap file, the next step is to install this .snap on the Intel Joule Board, we will use the cpp project as an example:
  - using scp, copy the .snap file onto the board:
```sh
$ scp grove-linefinder-cpp-joule-example_1.0_amd64.snap <userName>@<ipAddress>:<JoulePath>
```
  - Connect through ssh to the board and navigate to the folder where the .snap file was copied and install it:
```sh
$ ssh <userName>@<ipAddress>
$ cd <JoulePath>
$ snap install --devmode grove-linefinder-cpp-joule-example_1.0_amd64.snap 
```

# Run Project

After install, for cpp example, run:

```sh
$ sudo snap run grove-linefinder-cpp-joule-example_1.0_amd64.run
```

   
# Warnings   
  
   It was observed that, for mraa/upm to have access to GPIO's the binary/python/java should run with sudo.
   
   
   For official documentation over snaps/snapcraft please follow this link:
   https://snapcraft.io/docs/


### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|	upm Version	    |
|:---------------------:|:-----------------:|:-----------------:|:-----------------:|
|	Ubuntu Core			|  Intel Joule 570x	|	mraa 1.7.0		|	upm 1.3.0		|
