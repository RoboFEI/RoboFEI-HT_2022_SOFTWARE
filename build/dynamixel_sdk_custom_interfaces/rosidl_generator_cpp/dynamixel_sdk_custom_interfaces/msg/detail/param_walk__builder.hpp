// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/ParamWalk.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__BUILDER_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__BUILDER_HPP_

#include "dynamixel_sdk_custom_interfaces/msg/detail/param_walk__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace dynamixel_sdk_custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_ParamWalk_turn
{
public:
  explicit Init_ParamWalk_turn(::dynamixel_sdk_custom_interfaces::msg::ParamWalk & msg)
  : msg_(msg)
  {}
  ::dynamixel_sdk_custom_interfaces::msg::ParamWalk turn(::dynamixel_sdk_custom_interfaces::msg::ParamWalk::_turn_type arg)
  {
    msg_.turn = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::ParamWalk msg_;
};

class Init_ParamWalk_sidle
{
public:
  explicit Init_ParamWalk_sidle(::dynamixel_sdk_custom_interfaces::msg::ParamWalk & msg)
  : msg_(msg)
  {}
  Init_ParamWalk_turn sidle(::dynamixel_sdk_custom_interfaces::msg::ParamWalk::_sidle_type arg)
  {
    msg_.sidle = std::move(arg);
    return Init_ParamWalk_turn(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::ParamWalk msg_;
};

class Init_ParamWalk_walk
{
public:
  Init_ParamWalk_walk()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ParamWalk_sidle walk(::dynamixel_sdk_custom_interfaces::msg::ParamWalk::_walk_type arg)
  {
    msg_.walk = std::move(arg);
    return Init_ParamWalk_sidle(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::ParamWalk msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dynamixel_sdk_custom_interfaces::msg::ParamWalk>()
{
  return dynamixel_sdk_custom_interfaces::msg::builder::Init_ParamWalk_walk();
}

}  // namespace dynamixel_sdk_custom_interfaces

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__BUILDER_HPP_
