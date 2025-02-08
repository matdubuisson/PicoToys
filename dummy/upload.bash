#!/bin/bash

mkdir -p ~/USB/
sudo mount /dev/sda1 ~/USB/
sudo cp ../build/dummy/dummy.uf2 ~/USB/.
sudo umount /dev/sda1
