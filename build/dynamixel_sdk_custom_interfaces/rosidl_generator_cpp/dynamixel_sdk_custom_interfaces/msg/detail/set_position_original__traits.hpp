// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/SetPositionOriginal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__TRAITS_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__TRAITS_HPP_

#include "dynamixel_sdk_custom_interfaces/msg/detail/set_position_original__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal>()
{
  return "dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal";
}

template<>
inline const char * name<dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal>()
{
  return "dynamixel_sdk_custom_interfaces/msg/SetPositionOriginal";
}

template<>
struct has_fixed_size<dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<dynamixel_sdk_custom_interfaces::msg::SetPositionOriginal>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__TRAITS_HPP_
