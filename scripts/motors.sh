#!/bin/bash

cd ~/RoboFEI-HT_2022_SOFTWARE
source install/setup.bash
ros2 run dynamixel_sdk_examples read_write_node
