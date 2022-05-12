// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/Decision.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__DECISION__TRAITS_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__DECISION__TRAITS_HPP_

#include "dynamixel_sdk_custom_interfaces/msg/detail/decision__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const dynamixel_sdk_custom_interfaces::msg::Decision & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: decision
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    out << "decision: ";
    value_to_yaml(msg.decision, out);
    out << "\n";
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const dynamixel_sdk_custom_interfaces::msg::Decision & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<dynamixel_sdk_custom_interfaces::msg::Decision>()
{
  return "dynamixel_sdk_custom_interfaces::msg::Decision";
}

template<>
inline const char * name<dynamixel_sdk_custom_interfaces::msg::Decision>()
{
  return "dynamixel_sdk_custom_interfaces/msg/Decision";
}

template<>
struct has_fixed_size<dynamixel_sdk_custom_interfaces::msg::Decision>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<dynamixel_sdk_custom_interfaces::msg::Decision>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<dynamixel_sdk_custom_interfaces::msg::Decision>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__DECISION__TRAITS_HPP_
