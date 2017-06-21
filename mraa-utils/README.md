# mraa-utils 

This example is intended to have mraa uitlities available inside a snap packages and test on the Intel® Joule Expansion Board

# Build project
After succesfully installing snapcraft as a snap package, run the following command in the desired language folder:
```sh
$ sudo snap run snapcraft
```

# Install project

This will generate a *.snap file, the next step is to install this .snap on the Intel Joule Board, we will use the cpp project as an example:
  - using scp, copy the .snap file onto the board:
```sh
$ scp mraa-utils_1.0_amd64.snap <userName>@<ipAddress>:<JoulePath>
```
  - Connect through ssh to the board and navigate to the folder where the .snap file was copied and install it:
```sh
$ ssh <userName>@<ipAddress>
$ cd <JoulePath>
$ snap install --devmode mraa-utils_1.0_amd64.snap
```

# Run Project

To list the available gpio ports on Intel joule, run:

```sh
sudo snap run mraa-utils.mraa-gpio list
```

To use mraa-i2c utility, simply run:

```sh
sudo snap run mraa-utils.mraa-i2c <options>
```
   
# Warnings   
  
   It was observed that, for mraa/upm to have access to board GPIO's the utility binary should run with sudo.
   
   
   For official documentation over snaps/snapcraft please follow this link:
   https://snapcraft.io/docs/


### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|	upm Version	    |
|:---------------------:|:-----------------:|:-----------------:|:-----------------:|
|	Ubuntu Core			|  Intel Joule 570x	|	mraa 1.7.0		|	upm 1.3.0		|   