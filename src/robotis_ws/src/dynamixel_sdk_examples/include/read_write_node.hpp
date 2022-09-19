// Copyright 2021 ROBOTIS CO., LTD.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef READ_WRITE_NODE_HPP_
#define READ_WRITE_NODE_HPP_

#include <cstdio>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "rcutils/cmdline_parser.h"
#include "dynamixel_sdk/dynamixel_sdk.h"
#include "custom_interfaces/msg/set_position.hpp"
#include "custom_interfaces/msg/set_position_original.hpp"
#include "custom_interfaces/srv/get_position.hpp"
#include "custom_interfaces/msg/neck_position.hpp"


class ReadWriteNode : public rclcpp::Node
{
public:
  using SetPosition = custom_interfaces::msg::SetPosition;
  using SetPositionOriginal = custom_interfaces::msg::SetPositionOriginal;
  using GetPosition = custom_interfaces::srv::GetPosition;
  using NeckPosition = custom_interfaces::msg::NeckPosition;

  void timer_callback();

  ReadWriteNode();
  virtual ~ReadWriteNode();

private:
  rclcpp::Subscription<SetPosition>::SharedPtr set_position_subscriber_;
  rclcpp::Subscription<SetPositionOriginal>::SharedPtr set_position_subscriber_single;
  rclcpp::Service<GetPosition>::SharedPtr get_position_server_;
  rclcpp::Publisher<NeckPosition>::SharedPtr neck_position_publisher;

  rclcpp::TimerBase::SharedPtr timer_; // declaration of timer to publish the neck position

  int present_position;
  int motor[2];
};

#endif  // READ_WRITE_NODE_HPP_
