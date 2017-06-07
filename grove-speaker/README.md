# grove-speaker  

This example is intended to make use of grove Speaker v1.0b sensor, in order to emit some custom musical notes in conjuction with Intel Joule Board.

# Basic Wiring



# Build project
After succesfully installed snapcraft, navigate to the desired language folder, and write in terminal:
```sh
$ snapcraft
```

# Install project

This will generate a *.snap file, the next step is to install this .snap on the Intel Joule Board, we will use the cpp project as an example:
  - using scp, we will copy the .snap file onto the board:
```sh
$ scp grove-speaker-cpp-joule-example_1.0_amd64.snap <userName>@<ipAddress>:<JoulePath>
```
  - Connect through ssh to the board and navigate to the folder where the .snap file was copied and install it:
```sh
$ ssh <userName>@<ipAddress>
$ cd <JoulePath>
$ snap install --devmode grove-speaker-cpp-joule-example_1.0_amd64.snap 
```

# Run Project

After install, for cpp example, run:

```sh
$ sudo snap run grove-speaker-cpp-joule-example_1.0_amd64.run
```

   
# Warnings   
  
   It was observed that, for mraa/upm to have access to GPIO's the binary/python/java should run with sudo.
   
   
   For official documentation over snaps/snapcraft please follow this link:
   https://snapcraft.io/docs/


### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|	upm Version	    |
|:---------------------:|:-----------------:|:-----------------:|:-----------------:|
|	Ubuntu Core			|  Intel Joule 570x	|	mraa 1.7.0		|	upm 1.3.0		|
