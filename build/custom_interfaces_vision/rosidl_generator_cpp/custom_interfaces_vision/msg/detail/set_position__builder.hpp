// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces_vision:msg/SetPosition.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES_VISION__MSG__DETAIL__SET_POSITION__BUILDER_HPP_
#define CUSTOM_INTERFACES_VISION__MSG__DETAIL__SET_POSITION__BUILDER_HPP_

#include "custom_interfaces_vision/msg/detail/set_position__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_interfaces_vision
{

namespace msg
{

namespace builder
{

class Init_SetPosition_position
{
public:
  explicit Init_SetPosition_position(::custom_interfaces_vision::msg::SetPosition & msg)
  : msg_(msg)
  {}
  ::custom_interfaces_vision::msg::SetPosition position(::custom_interfaces_vision::msg::SetPosition::_position_type arg)
  {
    msg_.position = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces_vision::msg::SetPosition msg_;
};

class Init_SetPosition_id
{
public:
  Init_SetPosition_id()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_SetPosition_position id(::custom_interfaces_vision::msg::SetPosition::_id_type arg)
  {
    msg_.id = std::move(arg);
    return Init_SetPosition_position(msg_);
  }

private:
  ::custom_interfaces_vision::msg::SetPosition msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces_vision::msg::SetPosition>()
{
  return custom_interfaces_vision::msg::builder::Init_SetPosition_id();
}

}  // namespace custom_interfaces_vision

#endif  // CUSTOM_INTERFACES_VISION__MSG__DETAIL__SET_POSITION__BUILDER_HPP_
