# CMake generated Testfile for 
# Source directory: /home/robo/ROS2/um7
# Build directory: /home/robo/ROS2/um7/build/um7
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(um7_test_registers "/usr/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/robo/ROS2/um7/build/um7/test_results/um7/um7_test_registers.gtest.xml" "--package-name" "um7" "--output-file" "/home/robo/ROS2/um7/build/um7/ament_cmake_gtest/um7_test_registers.txt" "--command" "/home/robo/ROS2/um7/build/um7/um7_test_registers" "--gtest_output=xml:/home/robo/ROS2/um7/build/um7/test_results/um7/um7_test_registers.gtest.xml")
set_tests_properties(um7_test_registers PROPERTIES  LABELS "gtest" REQUIRED_FILES "/home/robo/ROS2/um7/build/um7/um7_test_registers" TIMEOUT "60" WORKING_DIRECTORY "/home/robo/ROS2/um7/build/um7" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;86;ament_add_test;/opt/ros/foxy/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/home/robo/ROS2/um7/CMakeLists.txt;57;ament_add_gtest;/home/robo/ROS2/um7/CMakeLists.txt;0;")
add_test(um7_test_comms "/usr/bin/python3" "-u" "/opt/ros/foxy/share/ament_cmake_test/cmake/run_test.py" "/home/robo/ROS2/um7/build/um7/test_results/um7/um7_test_comms.gtest.xml" "--package-name" "um7" "--output-file" "/home/robo/ROS2/um7/build/um7/ament_cmake_gtest/um7_test_comms.txt" "--command" "/home/robo/ROS2/um7/build/um7/um7_test_comms" "--gtest_output=xml:/home/robo/ROS2/um7/build/um7/test_results/um7/um7_test_comms.gtest.xml")
set_tests_properties(um7_test_comms PROPERTIES  LABELS "gtest" REQUIRED_FILES "/home/robo/ROS2/um7/build/um7/um7_test_comms" TIMEOUT "60" WORKING_DIRECTORY "/home/robo/ROS2/um7/build/um7" _BACKTRACE_TRIPLES "/opt/ros/foxy/share/ament_cmake_test/cmake/ament_add_test.cmake;118;add_test;/opt/ros/foxy/share/ament_cmake_gtest/cmake/ament_add_gtest_test.cmake;86;ament_add_test;/opt/ros/foxy/share/ament_cmake_gtest/cmake/ament_add_gtest.cmake;93;ament_add_gtest_test;/home/robo/ROS2/um7/CMakeLists.txt;64;ament_add_gtest;/home/robo/ROS2/um7/CMakeLists.txt;0;")
subdirs("um7__py")
subdirs("gtest")
