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
find_package(custom_interfaces REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(rclcpp_components REQUIRED)
find_package(rosidl_default_generators REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})
#find_package(rt REQUIRED)
# find_package(<dependency> REQUIRED)
find_library(LIBRT rt) 
set(CURSES_NEED_NCURSES TRUE)
find_package(Curses)


include_directories(include)
include_directories(src/minIni)

add_library(motion SHARED
  src/motion/MotionManager.cpp
  src/motion/modules/Walking.cpp
  src/motion/AngleEstimator.cpp
  src/math/Matrix.cpp
  src/math/Plane.cpp
  src/math/Point.cpp
  src/math/Vector.cpp
  src/math/QuadraticStateTransform.cpp
  src/math/MotionState.cpp
  src/motion/JointData.cpp
  src/motion/Kinematics.cpp
  src/motion/MotionStatus.cpp
  src/motion/AngleEstimator.cpp
  src/motion/modules/Action.cpp
  src/motion/modules/Walking.cpp
  src/minIni/minIni.cpp
  src/GaitMove.cpp
  src/ReadConfig.cpp
)

set(CMAKE_C_FLAGS " -lncurses")

#set(SOURCES
#  /home/robo/ROS2/walk_test/src/control/src/minIni/minIni.cpp
#  /home/robo/ROS2/walk_test/src/control/src/action_editor/cmd_process.cpp
#  )

#add_executable(action ${SOURCES})
#ament_target_dependencies(action
#  rclcpp
#  custom_interfaces
#  Curses
#)
#target_link_libraries(action ${CURSES_LIBRARY})


ament_target_dependencies(motion
  rclcpp
  rclcpp_components
  custom_interfaces
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
  custom_interfaces
  rclcpp
  sensor_msgs
)

add_executable(client src/client.cpp)
ament_target_dependencies(client
  custom_interfaces
  rclcpp
)

# Build
add_executable(decision src/dec.cpp)
ament_target_dependencies(decision
  custom_interfaces
  rclcpp
)

# Install
install(TARGETS
  control
  decision
  client
  DESTINATION lib/${PROJECT_NAME}
)

install(TARGETS motion
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
)

install(
  DIRECTORY include/
  DESTINATION include/
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
