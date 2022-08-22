# RoboFEI-HT_2022_SOFTWARE

This repository contains the code written using ROS2, by RoboFEI team, which is currently used in our physical robots. 

It is divided in 8 packages: 

* control: contains the code related to the robots motion and its parameters;
* custom_interfaces: contains all the custom interfaces used in the code;
* decision: contains the code responsible for the robots decision;
* GC: contains the code responsible for the robots communication with the game controller;
* localization_pkg: contains the code responsible for the robots localization;
* robotis_ws: contains the code responsible for the robots communication with its motors;
* start: contains the launch file to run all the nodes at once;
* um7: contains the code responsible for getting IMU measurements;
* vision_pkg: contains the code responsible for the robots vision.

## Installation:
1. First, download this repo from github:

    ```$ git clone https://github.com/RoboFEI/RoboFEI-HT_2022_SOFTWARE.git```

2. Then, install ROS2 Humble and all the libraries that are used in our code:

    ```$ ./comandos.sh```

3. Compile all the packages, in the source folder (*if there are more folders besides src delete them*):

    ```$ colcon build --symlink-install```

4. Setup the environment:

    ```$ source install/setup.bash```

5. Run all codes at once:

    ```$ ros2 launch start start.launch.py```

6. Run the codes separately:

    - Control: 
    
        ```$ ros2 launch control action.launch.py```

    - Decision: 
    
        ```$ ros2 run decision_pkg decision_node```

    - GC: 
    
        ```$ ros2 run controller talker```

    - IMU: 
    
        ```$ ros2 run um7 um7_node```

    - Localization: 
    
        ```$ ros2 run localization_pkg localization_node --mcl -l -g```

    - Motors: 
    
        ```$ ros2 run dynamixel_sdk_examples read_write_node```
    
    - Vision: 
    
        ```$ ros2 run vision_pkg vision --vb```
