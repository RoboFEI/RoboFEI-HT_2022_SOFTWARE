# $ ros2 launch dynamixel_sdk_examples dynamixel_sdk_examples.launch.py
 
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    minimal_publisher = Node(
        package="control",
        executable="minimal_pub",
        output = 'screen'
    )
    ld.add_action(minimal_publisher)
    return ld