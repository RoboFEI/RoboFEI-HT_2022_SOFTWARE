from setuptools import setup

package_name = 'controller'

setup(
    name=package_name,
    version='0.0.0',
    packages=[package_name],
    data_files=[
        ('share/ament_index/resource_index/packages',
            ['resource/' + package_name]),
        ('share/' + package_name, ['package.xml']),
    ],
    install_requires=['setuptools'],
    zip_safe=True,
    maintainer='robofei',
    maintainer_email='robofei@fei.edu.br',
    description='The controller packages receives packets from the GameController and republishes them as msg/humanoid_league_msgs ROS2 messages. It sends response packetsback to the GameController',
    license='Apache License',
    tests_require=['pytest'],
    entry_points={
        'console_scripts': [
                'talker = controller.receiver:main',
        ],
    },
)
