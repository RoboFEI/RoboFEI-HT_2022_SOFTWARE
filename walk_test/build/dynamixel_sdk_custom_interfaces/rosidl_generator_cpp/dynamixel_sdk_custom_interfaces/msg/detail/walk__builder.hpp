// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/Walk.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__WALK__BUILDER_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__WALK__BUILDER_HPP_

#include "dynamixel_sdk_custom_interfaces/msg/detail/walk__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace dynamixel_sdk_custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_Walk_walk
{
public:
  Init_Walk_walk()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::dynamixel_sdk_custom_interfaces::msg::Walk walk(::dynamixel_sdk_custom_interfaces::msg::Walk::_walk_type arg)
  {
    msg_.walk = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::Walk msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dynamixel_sdk_custom_interfaces::msg::Walk>()
{
  return dynamixel_sdk_custom_interfaces::msg::builder::Init_Walk_walk();
}

}  // namespace dynamixel_sdk_custom_interfaces

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__WALK__BUILDER_HPP_
