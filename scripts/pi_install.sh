#!/bin/bash

# Author: John Carter
# Created: 2021/12/15 18:47:43
# Last modified: 2021/12/15 18:50:08
# Install heimdall on a Raspberry Pi


RED=$'\e[1;31m'
GRN=$'\e[1;32m'
END=$'\e[0m'

exit_process() {
    echo "[${RED}EXIT${END}] Script terminated"
    exit 1
}

trap exit_process INT TERM

if (( EUID != 0 )); then
   echo "[${RED}ERROR${END}] This script must be run as root" 
   exit 1
fi

echo "[${GRN}INFO${END}] Installing cmake"
apt-get install cmake

echo "[${GRN}INFO${END}] Entering directory '/home/pi/heimdall'"
cd /home/pi/heimdall

echo "[${GRN}INFO${END}] Installing syscall-sensor"
cmake -DCMAKE_BUILD_TYPE=Release .
make -C syscall-sensor/
make -C syscall-sensor install
/usr/sbin