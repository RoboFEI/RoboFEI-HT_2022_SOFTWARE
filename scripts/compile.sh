#!/bin/bash

cd ~/RoboFEI-HT_2022_SOFTWARE
sudo rm -rf build install log runs
colcon build
source install/setup.bash
