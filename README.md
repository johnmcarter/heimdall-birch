# heimdall-birch

This repo contains a sensor to track system calls executed on Linux distributions. The original (unmaintained) source code can be found at https://github.com/ronin-zero/heimdall.git.git. This repo was forked so it could be maintained and used for further research. All credit for the original source code goes to its authors.

## Installation 
To install heimdall on a Raspberry Pi, run the install script in the ```scripts``` directory (with root privileges):
```
./scripts/pi_install.sh
```

## Usage
To run the syscall sensor, run:
```
syscall-sensor start <options>
```

To stop the syscall sensor, run:
```
syscall-sensor stop
```

## Compatibility
```
Last modified: 15 December 2021
Last tested on: October 2021 release of Raspberry Pi OS
```