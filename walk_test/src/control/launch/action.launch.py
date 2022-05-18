# $ ros2 launch dynamixel_sdk_examples dynamixel_sdk_examples.launch.py
 
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    control = Node(
        package="control",
        executable="control",
        output = 'screen'
    )
    decision = Node(
        package="control",
        executable="decision",
        output = 'screen'
    )
    ld.add_action(control)
    ld.add_action(decision)
    return ld