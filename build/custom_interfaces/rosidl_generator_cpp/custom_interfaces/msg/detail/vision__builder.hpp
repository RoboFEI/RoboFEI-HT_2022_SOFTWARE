// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from custom_interfaces:msg/Vision.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__VISION__BUILDER_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__VISION__BUILDER_HPP_

#include "custom_interfaces/msg/detail/vision__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace custom_interfaces
{

namespace msg
{

namespace builder
{

class Init_Vision_ball_close
{
public:
  explicit Init_Vision_ball_close(::custom_interfaces::msg::Vision & msg)
  : msg_(msg)
  {}
  ::custom_interfaces::msg::Vision ball_close(::custom_interfaces::msg::Vision::_ball_close_type arg)
  {
    msg_.ball_close = std::move(arg);
    return std::move(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

class Init_Vision_ball_med
{
public:
  explicit Init_Vision_ball_med(::custom_interfaces::msg::Vision & msg)
  : msg_(msg)
  {}
  Init_Vision_ball_close ball_med(::custom_interfaces::msg::Vision::_ball_med_type arg)
  {
    msg_.ball_med = std::move(arg);
    return Init_Vision_ball_close(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

class Init_Vision_ball_far
{
public:
  explicit Init_Vision_ball_far(::custom_interfaces::msg::Vision & msg)
  : msg_(msg)
  {}
  Init_Vision_ball_med ball_far(::custom_interfaces::msg::Vision::_ball_far_type arg)
  {
    msg_.ball_far = std::move(arg);
    return Init_Vision_ball_med(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

class Init_Vision_ball_center_right
{
public:
  explicit Init_Vision_ball_center_right(::custom_interfaces::msg::Vision & msg)
  : msg_(msg)
  {}
  Init_Vision_ball_far ball_center_right(::custom_interfaces::msg::Vision::_ball_center_right_type arg)
  {
    msg_.ball_center_right = std::move(arg);
    return Init_Vision_ball_far(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

class Init_Vision_ball_right
{
public:
  explicit Init_Vision_ball_right(::custom_interfaces::msg::Vision & msg)
  : msg_(msg)
  {}
  Init_Vision_ball_center_right ball_right(::custom_interfaces::msg::Vision::_ball_right_type arg)
  {
    msg_.ball_right = std::move(arg);
    return Init_Vision_ball_center_right(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

class Init_Vision_ball_center_left
{
public:
  explicit Init_Vision_ball_center_left(::custom_interfaces::msg::Vision & msg)
  : msg_(msg)
  {}
  Init_Vision_ball_right ball_center_left(::custom_interfaces::msg::Vision::_ball_center_left_type arg)
  {
    msg_.ball_center_left = std::move(arg);
    return Init_Vision_ball_right(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

class Init_Vision_ball_left
{
public:
  explicit Init_Vision_ball_left(::custom_interfaces::msg::Vision & msg)
  : msg_(msg)
  {}
  Init_Vision_ball_center_left ball_left(::custom_interfaces::msg::Vision::_ball_left_type arg)
  {
    msg_.ball_left = std::move(arg);
    return Init_Vision_ball_center_left(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

class Init_Vision_ball_detected
{
public:
  Init_Vision_ball_detected()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Vision_ball_left ball_detected(::custom_interfaces::msg::Vision::_ball_detected_type arg)
  {
    msg_.ball_detected = std::move(arg);
    return Init_Vision_ball_left(msg_);
  }

private:
  ::custom_interfaces::msg::Vision msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::custom_interfaces::msg::Vision>()
{
  return custom_interfaces::msg::builder::Init_Vision_ball_detected();
}

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__VISION__BUILDER_HPP_
