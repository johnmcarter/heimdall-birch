#!/bin/bash

# Author: John Carter
# Created: 2021/12/15 18:47:43
# Last modified: 2022/01/18 11:18:23
# Install heimdall-birch on a Linux machine


RED=$'\e[1;31m'
GRN=$'\e[1;32m'
END=$'\e[0m'

help() {
   echo "[${RED}ERROR${END}] USAGE: $0 <username>"
   exit 1
}

exit_process() {
    echo "[${RED}EXIT${END}] Script terminated"
    exit 1
}

trap exit_process INT TERM

if (( EUID != 0 )); then
   echo "[${RED}ERROR${END}] This script must be run as root" 
   exit 1
fi

if [[ $# -ne 1 ]]; then
    help
fi

echo "[${GRN}INFO${END}] Installing cmake"
apt-get install cmake

echo "[${GRN}INFO${END}] Entering directory '/home/$1/heimdall-birch'"
cd /home/$1/heimdall-birch
pwd

echo "[${GRN}INFO${END}] Installing heimdall-birch syscall-sensor"
cmake -DCMAKE_BUILD_TYPE=Release .
make -C syscall-sensor/
make -C syscall-sensor install