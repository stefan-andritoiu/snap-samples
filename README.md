# snap-samples

Snapcraft samples using the Intel IoT Developer Kit, Intel Developer boards or Intel IoT Gateway, sensors, and APIs.

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
   
  - On the target Developer boards it is suggested to have installed Ubuntu Desktop or Ubuntu Core, in the future development of snapd, it will support other operating systems, but for now we suggest using Ubuntu.

Preffered development host OS:
  - Ubuntu
  - Linux Mint

Since snapcraft was developed mainly for Ubuntu, other debian distros might need different environment setup to support snapd/snapcraft. Please follow official documentation on this subject: 
https://snapcraft.io/docs/build-snaps/trusty
