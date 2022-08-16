# $ ros2 launch control action.launch.py
 
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
    ld.add_action(control)
    ld.add_action(gait)
    return ld