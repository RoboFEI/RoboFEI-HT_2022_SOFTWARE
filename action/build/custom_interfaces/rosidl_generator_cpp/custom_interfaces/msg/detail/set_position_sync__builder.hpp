// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:msg/SetPositionSync.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__BUILDER_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__BUILDER_HPP_

#include "custom_interfaces/msg/detail/set_position_sync__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_SetPositionSync_position
{
public:
  explicit Init_SetPositionSync_position(::custom_interfaces::msg::SetPositionSync & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::msg::SetPositionSync position(::custom_interfaces::msg::SetPositionSync::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::msg::SetPositionSync msg_;
};

class Init_SetPositionSync_id
{
public:
  Init_SetPositionSync_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPositionSync_position id(::custom_interfaces::msg::SetPositionSync::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_SetPositionSync_position(msg_);
  }

private:
  ::custom_interfaces::msg::SetPositionSync msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::msg::SetPositionSync>()
{
  return custom_interfaces::msg::builder::Init_SetPositionSync_id();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__BUILDER_HPP_
