// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/SetPositionSync.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__BUILDER_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__BUILDER_HPP_

#include "dynamixel_sdk_custom_interfaces/msg/detail/set_position_sync__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace dynamixel_sdk_custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_SetPositionSync_position
{
public:
  explicit Init_SetPositionSync_position(::dynamixel_sdk_custom_interfaces::msg::SetPositionSync & msg)
  : msg_(msg)
  {}
  ::dynamixel_sdk_custom_interfaces::msg::SetPositionSync position(::dynamixel_sdk_custom_interfaces::msg::SetPositionSync::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::SetPositionSync msg_;
};

class Init_SetPositionSync_id
{
public:
  Init_SetPositionSync_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPositionSync_position id(::dynamixel_sdk_custom_interfaces::msg::SetPositionSync::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_SetPositionSync_position(msg_);
  }

private:
  ::dynamixel_sdk_custom_interfaces::msg::SetPositionSync msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::dynamixel_sdk_custom_interfaces::msg::SetPositionSync>()
{
  return dynamixel_sdk_custom_interfaces::msg::builder::Init_SetPositionSync_id();
}

}  // namespace dynamixel_sdk_custom_interfaces

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__BUILDER_HPP_
