#!/bin/bash

mkdir -p ~/USB/
sudo mount /dev/sda1 ~/USB/
sudo cp ../build/ultrasonic_api/test_ultrasonic_api.uf2 ~/USB/.
sudo umount /dev/sda1
