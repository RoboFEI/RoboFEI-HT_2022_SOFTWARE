// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:msg/ParamWalk.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__BUILDER_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__BUILDER_HPP_

#include "custom_interfaces/msg/detail/param_walk__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_ParamWalk_turn
{
public:
  explicit Init_ParamWalk_turn(::custom_interfaces::msg::ParamWalk & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::msg::ParamWalk turn(::custom_interfaces::msg::ParamWalk::_turn_type arg)
  {
    msg_.turn = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::msg::ParamWalk msg_;
};

class Init_ParamWalk_sidle
{
public:
  explicit Init_ParamWalk_sidle(::custom_interfaces::msg::ParamWalk & msg)
  : msg_(msg)
  {}
  Init_ParamWalk_turn sidle(::custom_interfaces::msg::ParamWalk::_sidle_type arg)
  {
    msg_.sidle = std::move(arg);
    return Init_ParamWalk_turn(msg_);
  }

private:
  ::custom_interfaces::msg::ParamWalk msg_;
};

class Init_ParamWalk_walk
{
public:
  Init_ParamWalk_walk()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_ParamWalk_sidle walk(::custom_interfaces::msg::ParamWalk::_walk_type arg)
  {
    msg_.walk = std::move(arg);
    return Init_ParamWalk_sidle(msg_);
  }

private:
  ::custom_interfaces::msg::ParamWalk msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::msg::ParamWalk>()
{
  return custom_interfaces::msg::builder::Init_ParamWalk_walk();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__BUILDER_HPP_
