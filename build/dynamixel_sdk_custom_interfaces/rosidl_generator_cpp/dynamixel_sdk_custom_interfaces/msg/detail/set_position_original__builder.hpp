// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/SetPositionOriginal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__BUILDER_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__BUILDER_HPP_

#include "dynamixel_sdk_custom_interfaces/msg/detail/set_position_original__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace dynamixel_sdk_custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_SetPositionOriginal_position
{
public:
  explicit Init_SetPositionOriginal_position(::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal & msg)
  : msg_(msg)
  {}
  ::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal position(::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal msg_;
};

class Init_SetPositionOriginal_address
{
public:
  explicit Init_SetPositionOriginal_address(::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal & msg)
  : msg_(msg)
  {}
  Init_SetPositionOriginal_position address(::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal::_address_type arg)
  {
    msg_.address = std::move(arg);
    return Init_SetPositionOriginal_position(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal msg_;
};

class Init_SetPositionOriginal_id
{
public:
  Init_SetPositionOriginal_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPositionOriginal_address id(::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_SetPositionOriginal_address(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal>()
{
  return dynamixel_sdk_custom_interfaces::msg::builder::Init_SetPositionOriginal_id();
}

}  // namespace dynamixel_sdk_custom_interfaces

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__BUILDER_HPP_
