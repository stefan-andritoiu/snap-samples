# ubuntu-core-samples

Samples and projects for platforms running Ubuntu Core on Intel® Joule Expansion Board

Basic environment settings and tools needed for every example:

  - Add official mraa and upm PPA on development machine:
```sh
$ sudo add-apt-repository ppa:mraa/mraa
$ sudo apt-get update
```
  - Install snapd on development machine, install aditional snapcraft tool inside snapd:

```sh
$ sudo apt-get install snapd
$ snap install snapcraft --beta --classic
```

  - Follow this [link] for installing Ubuntu Core on Intel Joule, additional help can be found [here].

   [link]: <https://developer.ubuntu.com/core/get-started/intel-joule>
   [here]: <https://tutorials.ubuntu.com/tutorial/setup-ubuntu-core-intel-joule#0>
   
Preffered OS:
	- Ubuntu
	- Linux Mint

Since snapcraft was developed mainly for Ubuntu, other debian distros might need different environment setup to support snapd/snapcraft. Please follow official documentation on this subject: 
https://snapcraft.io/docs/build-snaps/trusty
