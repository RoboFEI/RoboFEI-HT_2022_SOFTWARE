// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:msg/Localization.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__BUILDER_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__BUILDER_HPP_

#include "custom_interfaces/msg/detail/localization__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_Localization_standard_deviation
{
public:
  explicit Init_Localization_standard_deviation(::custom_interfaces::msg::Localization & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::msg::Localization standard_deviation(::custom_interfaces::msg::Localization::_standard_deviation_type arg)
  {
    msg_.standard_deviation = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::msg::Localization msg_;
};

class Init_Localization_theta
{
public:
  explicit Init_Localization_theta(::custom_interfaces::msg::Localization & msg)
  : msg_(msg)
  {}
  Init_Localization_standard_deviation theta(::custom_interfaces::msg::Localization::_theta_type arg)
  {
    msg_.theta = std::move(arg);
    return Init_Localization_standard_deviation(msg_);
  }

private:
  ::custom_interfaces::msg::Localization msg_;
};

class Init_Localization_ypos
{
public:
  explicit Init_Localization_ypos(::custom_interfaces::msg::Localization & msg)
  : msg_(msg)
  {}
  Init_Localization_theta ypos(::custom_interfaces::msg::Localization::_ypos_type arg)
  {
    msg_.ypos = std::move(arg);
    return Init_Localization_theta(msg_);
  }

private:
  ::custom_interfaces::msg::Localization msg_;
};

class Init_Localization_xpos
{
public:
  Init_Localization_xpos()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Localization_ypos xpos(::custom_interfaces::msg::Localization::_xpos_type arg)
  {
    msg_.xpos = std::move(arg);
    return Init_Localization_ypos(msg_);
  }

private:
  ::custom_interfaces::msg::Localization msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::msg::Localization>()
{
  return custom_interfaces::msg::builder::Init_Localization_xpos();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__BUILDER_HPP_
