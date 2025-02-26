#!/bin/bash

export PICO_SDK_PATH=/home/racteur/PicoProjects/pico-sdk/

mkdir -p ../build/
cd ../build/
cmake -DPICO_BOARD=pico_w ..

make dummy
