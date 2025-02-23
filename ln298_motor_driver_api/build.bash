#!/bin/bash

export PICO_SDK_PATH=/home/racteur/PicoProjects/pico-sdk/

cd ../build/
cmake -DPICO_BOARD=pico_w ..
make test_ln298_motor_driver_api
