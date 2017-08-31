# jhd1313m1-lcd  

This example is intended to display a message on the Grove RGB LCD connected to different hardware platforms.

# Basic Wiring

As an example, we will use Intel® Joule Expansion Board as host platform for the jhd1313m1-lcd. Please follow this link for detailed physical connection of the Grove-LCD on the Joule Board:
https://github.com/intel-iot-devkit/code-samples/tree/master/exploring-cpp/lesson_4_i2c/cpp

# Build project
After succesfully installing snapcraft as a snap package, run the following command in the desired language folder:
```sh
$ sudo snap run snapcraft
```

# Install project

This will generate a *.snap file, the next step is to install this .snap on the Intel Joule Board, we will use the cpp project as an example:
  - using scp, copy the .snap file onto the board:
```sh
$ scp jhd1313m1-upm-cpp-example_1.0_amd64.snap <userName>@<ipAddress>:<targetPath>
```
  - Connect through ssh to the board and navigate to the folder where the .snap file was copied and install it:
```sh
$ ssh <userName>@<ipAddress>
$ cd <targetPath>
$ snap install --devmode jhd1313m1-upm-cpp-example_1.0_amd64.snap 
```

# Run Project

After install, for cpp example, run:

```sh
$ sudo snap run jhd1313m1-upm-cpp-example_1.0_amd64.run
```

   
# Warnings   
  
   It was observed that in order for mraa/upm to have access on Ubuntu to GPIO's the binary/python/java should run with sudo.
   
   
   For official documentation over snaps/snapcraft please follow this link:
   https://snapcraft.io/docs/


### Tested
|	Operating System	|	Carrier Board	|	mraa Version	|	upm Version	    |
|:---------------------:|:-----------------:|:-----------------:|:-----------------:|
|	Ubuntu Core			|  Intel Joule 570x	|	mraa 1.7.0		|	upm 1.3.0		|   
|	Ubuntu Desktop		|  MinnowBoard Max 	|	mraa 1.7.0		|	upm 1.3.0		|  
|	Ubuntu Desktop		|  Intel Nuc DE3815 + Arduino 101	|	mraa 1.7.0		|	upm 1.3.0		| 
