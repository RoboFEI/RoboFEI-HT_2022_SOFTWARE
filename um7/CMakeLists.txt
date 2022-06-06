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

rosidl_generate_interfaces(${PROJECT_NAME}
  "srv/Reset.srv"
)

###########
## Build ##
###########

include_directories(include)

add_library(um7_driver SHARED
  src/main.cpp
  src/registers.cpp
  src/comms.cpp
)
ament_target_dependencies(um7_driver
  rclcpp
  rclcpp_components
  include/serial
  sensor_msgs
)
rosidl_target_interfaces(um7_driver ${PROJECT_NAME} "rosidl_typesupport_cpp")
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

#############
## Testing ##
#############
if(BUILD_TESTING)
  #find_package(roslint REQUIRED)
  find_package(ament_cmake_gtest)

  ament_add_gtest(${PROJECT_NAME}_test_registers test/test_registers.cpp src/registers.cpp)
  ament_target_dependencies(${PROJECT_NAME}_test_registers
    rclcpp
    rclcpp_components
    include/serial
    sensor_msgs
  )

  ament_add_gtest(${PROJECT_NAME}_test_comms test/test_comms.cpp src/comms.cpp src/registers.cpp)
  ament_target_dependencies(${PROJECT_NAME}_test_comms
    rclcpp
    rclcpp_components
    include/serial
    sensor_msgs
  )
  target_link_libraries(${PROJECT_NAME}_test_comms util)


  #file(GLOB LINT_SRCS
  #  src/*.cpp
  #  include/um7/registers.h
  #  include/um7/comms.h)
  #roslint_cpp(${LINT_SRCS})
  #roslint_add_test()
endif()

ament_export_dependencies(rosidl_default_runtime)
ament_package()
