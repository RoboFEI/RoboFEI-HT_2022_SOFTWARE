// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from um7:srv/Reset.idl
// generated code does not contain a copyright notice

#ifndef UM7__SRV__DETAIL__RESET__BUILDER_HPP_
#define UM7__SRV__DETAIL__RESET__BUILDER_HPP_

#include "um7/srv/detail/reset__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace um7
{

namespace srv
{

namespace builder
{

class Init_Reset_Request_set_mag_ref
{
public:
  explicit Init_Reset_Request_set_mag_ref(::um7::srv::Reset_Request & msg)
  : msg_(msg)
  {}
  ::um7::srv::Reset_Request set_mag_ref(::um7::srv::Reset_Request::_set_mag_ref_type arg)
  {
    msg_.set_mag_ref = std::move(arg);
    return std::move(msg_);
  }

private:
  ::um7::srv::Reset_Request msg_;
};

class Init_Reset_Request_reset_ekf
{
public:
  explicit Init_Reset_Request_reset_ekf(::um7::srv::Reset_Request & msg)
  : msg_(msg)
  {}
  Init_Reset_Request_set_mag_ref reset_ekf(::um7::srv::Reset_Request::_reset_ekf_type arg)
  {
    msg_.reset_ekf = std::move(arg);
    return Init_Reset_Request_set_mag_ref(msg_);
  }

private:
  ::um7::srv::Reset_Request msg_;
};

class Init_Reset_Request_zero_gyros
{
public:
  Init_Reset_Request_zero_gyros()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_Reset_Request_reset_ekf zero_gyros(::um7::srv::Reset_Request::_zero_gyros_type arg)
  {
    msg_.zero_gyros = std::move(arg);
    return Init_Reset_Request_reset_ekf(msg_);
  }

private:
  ::um7::srv::Reset_Request msg_;
};

}  // namespace builder

}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::um7::srv::Reset_Request>()
{
  return um7::srv::builder::Init_Reset_Request_zero_gyros();
}

}  // namespace um7


namespace um7
{

namespace srv
{


}  // namespace srv

template<typename MessageType>
auto build();

template<>
inline
auto build<::um7::srv::Reset_Response>()
{
  return ::um7::srv::Reset_Response(rosidl_runtime_cpp::MessageInitialization::ZERO);
}

}  // namespace um7

#endif  // UM7__SRV__DETAIL__RESET__BUILDER_HPP_
