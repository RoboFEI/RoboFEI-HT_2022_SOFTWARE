// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces_vision:msg/Decision.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES_VISION__MSG__DETAIL__DECISION__BUILDER_HPP_
#define CUSTOM_INTERFACES_VISION__MSG__DETAIL__DECISION__BUILDER_HPP_

#include "custom_interfaces_vision/msg/detail/decision__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_interfaces_vision
{

namespace msg
{

namespace builder
{

class Init_Decision_decision
{
public:
  Init_Decision_decision()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  ::custom_interfaces_vision::msg::Decision decision(::custom_interfaces_vision::msg::Decision::_decision_type arg)
  {
    msg_.decision = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces_vision::msg::Decision msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces_vision::msg::Decision>()
{
  return custom_interfaces_vision::msg::builder::Init_Decision_decision();
}

}  // namespace custom_interfaces_vision

#endif  // CUSTOM_INTERFACES_VISION__MSG__DETAIL__DECISION__BUILDER_HPP_
