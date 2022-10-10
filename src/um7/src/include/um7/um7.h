/**
 *
 *  \file
 *  \brief      Main entry point for UM7 driver. Handles serial connection
 *              details, as well as all ROS message stuffing, parameters,
 *              topics, etc.
 *  \author     Mike Purvis <mpurvis@clearpathrobotics.com> (original code for UM6)
 *  \copyright  Copyright (c) 2013, Clearpath Robotics, Inc.
 *  \author     Alex Brown <rbirac@cox.net>		    (adapted to UM7)
 *  \copyright  Copyright (c) 2015, Alex Brown.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of Clearpath Robotics, Inc. nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL CLEARPATH ROBOTICS, INC. OR ALEX BROWN BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef UM7_UM7_H_
#define UM7_UM7_H_

#include <thread>
#include <string>

#include "geometry_msgs/msg/vector3_stamped.hpp"
#include "rclcpp/rclcpp.hpp"
#include "sensor_msgs/msg/imu.hpp"
#include "sensor_msgs/msg/magnetic_field.hpp"
#include "serial/serial.h"
#include "std_msgs/msg/float32.hpp"
#include "um7/comms.h"
#include "um7/registers.h"
#include "custom_interfaces/srv/reset.hpp"

namespace um7
{

namespace OutputAxisOptions
{
  enum OutputAxisOption
  {
    DEFAULT, ENU, ROBOT_FRAME
  };
}
typedef OutputAxisOptions::OutputAxisOption OutputAxisOption;

class Driver : public rclcpp::Node
{
public:
  Driver(const rclcpp::NodeOptions & options);

private:
  void publish(um7::Registers& r);

  void update_loop(void);

  void configure_sensor(std::shared_ptr<um7::Comms> sensor);

  template<typename RegT>
  void send_command(const um7::Accessor<RegT>& reg, std::string human_name);

  void handle_reset_service(
    const std::shared_ptr<custom_interfaces::srv::Reset::Request> req,
    std::shared_ptr<custom_interfaces::srv::Reset::Response> resp);

  // ROS2 Interfaces
  rclcpp::Publisher<sensor_msgs::msg::Imu>::SharedPtr imu_pub_;
  rclcpp::Publisher<sensor_msgs::msg::MagneticField>::SharedPtr mag_pub_;
  rclcpp::Publisher<geometry_msgs::msg::Vector3Stamped>::SharedPtr rpy_pub_;
  rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr temperature_pub_;

  OutputAxisOption axes_;
  std::string port_;
  serial::Serial serial_;
  std::shared_ptr<um7::Comms> sensor_;
  sensor_msgs::msg::Imu imu_msg_;

  std::thread update_thread_;
};

}  // namespace um7

#endif  // UM7_UM7_H_
