cmake_minimum_required(VERSION 3.5)
project(control)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(dynamixel_sdk_custom_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rosidl_default_generators REQUIRED)
# find_package(<dependency> REQUIRED)

include_directories(include)
include_directories(src/minIni)

add_library(motion SHARED
  src/motion/MotionManager.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/modules/Walking.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/AngleEstimator.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/math/Matrix.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/math/Plane.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/math/Point.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/math/Vector.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/math/QuadraticStateTransform.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/math/MotionState.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/JointData.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/Kinematics.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/MotionStatus.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/AngleEstimator.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/modules/Action.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/motion/modules/Walking.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/minIni/minIni.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/GaitMove.cpp
  /home/robofei/Desktop/ROS2/walk_test/src/control/src/ReadConfig.cpp
  
)
ament_target_dependencies(motion
  rclcpp
  rclcpp_components
  dynamixel_sdk_custom_interfaces
  sensor_msgs
)

#rosidl_target_interfaces(motion ${PROJECT_NAME} "rosidl_typesupport_cpp")

rclcpp_components_register_node(motion
  PLUGIN "Robot::MotionManager"
  EXECUTABLE gait_publisher
)

# Build
add_executable(control src/control.cpp)
ament_target_dependencies(control
  dynamixel_sdk_custom_interfaces
  rclcpp
  sensor_msgs
)

# Build
add_executable(decision src/dec.cpp)
ament_target_dependencies(decision
  dynamixel_sdk_custom_interfaces
  rclcpp
)

# Install
install(TARGETS
  control
  decision
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS motion
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

# Install launch files.
install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  # the following line skips the linter which checks for copyrights
  # uncomment the line when a copyright and license is not present in all source files
  #set(ament_cmake_copyright_FOUND TRUE)
  # the following line skips cpplint (only works in a git repo)
  # uncomment the line when this package is not in a git repo
  #set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_export_dependencies(rosidl_default_runtime)
ament_package()
