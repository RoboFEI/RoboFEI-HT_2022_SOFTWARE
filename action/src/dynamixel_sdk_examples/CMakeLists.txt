cmake_minimum_required(VERSION 3.5)
project(dynamixel_sdk_examples)

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
find_package(dynamixel_sdk REQUIRED)
find_package(dynamixel_sdk_custom_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
# find_package(<dependency> REQUIRED)

include_directories(include)
include_directories(Framework)
include_directories(Linux)

# Build
add_executable(cmd_node src/cmd_process.cpp)
ament_target_dependencies(cmd_node
  dynamixel_sdk_custom_interfaces
  dynamixel_sdk
  rclcpp
)
#add_executable(motion_manager_node src/MotionManager.cpp)
#ament_target_dependencies(motion_manager_node
#  dynamixel_sdk_custom_interfaces
#  dynamixel_sdk
#  rclcpp
#)

# Install
install(TARGETS
  cmd_node
#  motion_manager_node
  DESTINATION lib/${PROJECT_NAME}
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
