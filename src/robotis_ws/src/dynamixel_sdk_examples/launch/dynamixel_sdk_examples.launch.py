# $ ros2 launch dynamixel_sdk_examples dynamixel_sdk_examples.launch.py
 
from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    ld = LaunchDescription()
    read_write_node = Node(
        package="dynamixel_sdk_examples",
        executable="read_write_node",
        output = 'screen'
    )
    minimal_pub = Node(
        package="dynamixel_sdk_examples",
        executable="minimal_pub",
        output = 'screen'
    )
    ld.add_action(read_write_node)
    ld.add_action(minimal_pub)
    return ld