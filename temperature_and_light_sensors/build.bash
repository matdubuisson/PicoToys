#!/bin/bash

export PICO_SDK_PATH=/home/racteur/PicoProjects/pico-sdk/

if [[ -e build/ ]]; then
    rm -rf build/
fi

mkdir build/
cd build/
cmake -DPICO_BOARD=pico_w ..
make

