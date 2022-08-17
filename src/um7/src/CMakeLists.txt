cmake_minimum_required(VERSION 3.5)
project(um7)

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rosidl_default_generators REQUIRED)
find_package(serial REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(custom_interfaces REQUIRED)

###########
## Build ##
###########

include_directories(include)

add_library(um7_driver SHARED
  um7/main.cpp
  um7/registers.cpp
  um7/comms.cpp
)
ament_target_dependencies(um7_driver
  rclcpp
  rclcpp_components
  serial
  sensor_msgs
  custom_interfaces
)

rclcpp_components_register_node(um7_driver
  PLUGIN "um7::Driver"
  EXECUTABLE um7_node
)

#############
## Install ##
#############

install(TARGETS um7_driver
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

ament_export_dependencies(rosidl_default_runtime)
ament_package()
