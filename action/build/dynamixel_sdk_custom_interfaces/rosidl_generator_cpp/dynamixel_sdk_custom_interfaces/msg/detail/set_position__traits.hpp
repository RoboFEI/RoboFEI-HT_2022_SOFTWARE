// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/SetPosition.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION__TRAITS_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION__TRAITS_HPP_

#include "dynamixel_sdk_custom_interfaces/msg/detail/set_position__struct.hpp"
#include <stdint.h>
#include <rosidl_runtime_cpp/traits.hpp>
#include <sstream>
#include <string>
#include <type_traits>

namespace rosidl_generator_traits
{

inline void to_yaml(
  const dynamixel_sdk_custom_interfaces::msg::SetPosition & msg,
  std::ostream & out, size_t indentation = 0)
{
  // member: id
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.id.size() == 0) {
      out << "id: []\n";
    } else {
      out << "id:\n";
      for (auto item : msg.id) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
  }

  // member: position
  {
    if (indentation > 0) {
      out << std::string(indentation, ' ');
    }
    if (msg.position.size() == 0) {
      out << "position: []\n";
    } else {
      out << "position:\n";
      for (auto item : msg.position) {
        if (indentation > 0) {
          out << std::string(indentation, ' ');
        }
        out << "- ";
        value_to_yaml(item, out);
        out << "\n";
      }
    }
  }
}  // NOLINT(readability/fn_size)

inline std::string to_yaml(const dynamixel_sdk_custom_interfaces::msg::SetPosition & msg)
{
  std::ostringstream out;
  to_yaml(msg, out);
  return out.str();
}

template<>
inline const char * data_type<dynamixel_sdk_custom_interfaces::msg::SetPosition>()
{
  return "dynamixel_sdk_custom_interfaces::msg::SetPosition";
}

template<>
inline const char * name<dynamixel_sdk_custom_interfaces::msg::SetPosition>()
{
  return "dynamixel_sdk_custom_interfaces/msg/SetPosition";
}

template<>
struct has_fixed_size<dynamixel_sdk_custom_interfaces::msg::SetPosition>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<dynamixel_sdk_custom_interfaces::msg::SetPosition>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<dynamixel_sdk_custom_interfaces::msg::SetPosition>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION__TRAITS_HPP_
