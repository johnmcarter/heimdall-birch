# heimdall-birch

This repo contains a sensor to track system calls executed on Linux distributions. The original (unmaintained) source code can be found at git@github.com:johnmcarter/heimdall-birch.git. This repo was forked so it could be maintained and used for further research. All credit for the original source code goes to its authors.

## Installation 
To install heimdall on a Raspberry Pi, run these commands (with root privileges):
```
apt-get install cmake
```
```
cd /home/pi/heimdall
```
```
cmake -DCMAKE_BUILD_TYPE=Release .
```
```
make -C syscall-sensor/
```
```
make -C syscall-sensor install
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