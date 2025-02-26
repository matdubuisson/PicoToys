#!/bin/bash

mkdir -p ~/USB/
sudo mount /dev/sda1 ~/USB/
sudo cp ../build/ln298_motor_driver_api/test_ln298_motor_driver_api.uf2 ~/USB/.
sudo umount /dev/sda1
