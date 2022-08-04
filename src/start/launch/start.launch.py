# $ ros2 launch start start.launch.py 
 
from launch import LaunchDescription
from launch_ros.actions import Node


def generate_launch_description():
    ld = LaunchDescription()
    control = Node(
        package="control",
        executable="control",
        output = 'screen'
    )
    gait = Node(
        package="control",
        executable="gait_publisher",
        output = 'screen'
    )
    vision = Node(
        package="vision_pkg",
        executable="vision",
        output = 'screen'
    )
    dynamixel = Node(
        package="dynamixel_sdk_examples",
        executable="read_write_node",
        output = 'screen'
    )
    imu = Node(
        package="um7",
        executable="um7_node",
        output = 'screen'
    )
    gc = Node(
        package="controller",
        executable="talker",
        output = 'screen'
    )
    decision = Node(
        package="decision_pkg",
        executable="decision_node",
        output = 'screen'
    )
    ld.add_action(control)
    ld.add_action(gait)
    ld.add_action(dynamixel)
    ld.add_action(vision)
    ld.add_action(imu)
    ld.add_action(gc)
    ld.add_action(decision)
    return ld