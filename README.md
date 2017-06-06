# ubuntu-core-samples

Samples and projects for platforms running Ubuntu Core

Basic environment settings and tools needed for every example:

  - Add official mraa and upm PPA on development machine:
```sh
$ sudo add-apt-repository ppa:mraa/mraa
$ sudo apt-get update
```
  - Install snapcraft on development machine:

```sh
$ sudo add-apt-repository ppa:snappy-dev/tools
$ sudo apt-get update
$ sudo apt-get install snapcraft
```

  - Follow this [link] for installing Ubuntu Core on Intel Joule, additional help can be found [here].

   [link]: <https://developer.ubuntu.com/core/get-started/intel-joule>
   [here]: <https://tutorials.ubuntu.com/tutorial/setup-ubuntu-core-intel-joule#0>
   