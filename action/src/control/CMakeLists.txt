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
# find_package(<dependency> REQUIRED)

include_directories(include)
include_directories(src/minIni)

set(EXT_SOURCES
  /home/robofei/ROS2/action/src/control/src/motion/modules/Walking.cpp
  /home/robofei/ROS2/action/src/control/src/motion/AngleEstimator.cpp
  /home/robofei/ROS2/action/src/control/src/math/Matrix.cpp
  /home/robofei/ROS2/action/src/control/src/math/Plane.cpp
  /home/robofei/ROS2/action/src/control/src/math/Point.cpp
  /home/robofei/ROS2/action/src/control/src/math/Vector.cpp
  /home/robofei/ROS2/action/src/control/src/math/QuadraticStateTransform.cpp
  /home/robofei/ROS2/action/src/control/src/math/MotionState.cpp
  /home/robofei/ROS2/action/src/control/src/motion/JointData.cpp
  /home/robofei/ROS2/action/src/control/src/motion/Kinematics.cpp
  /home/robofei/ROS2/action/src/control/src/motion/MotionStatus.cpp
  /home/robofei/ROS2/action/src/control/src/motion/AngleEstimator.cpp
  /home/robofei/ROS2/action/src/control/src/motion/modules/Action.cpp
  /home/robofei/ROS2/action/src/control/src/motion/modules/Walking.cpp
  /home/robofei/ROS2/action/src/control/src/minIni/minIni.cpp
)


# Build
add_executable(control src/control.cpp)
ament_target_dependencies(control
  dynamixel_sdk_custom_interfaces
  rclcpp
  sensor_msgs
)

# Build
add_executable(motion src/motion/MotionManager.cpp ${EXT_SOURCES})
ament_target_dependencies(motion
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
  motion
  DESTINATION lib/${PROJECT_NAME}
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

ament_package()
