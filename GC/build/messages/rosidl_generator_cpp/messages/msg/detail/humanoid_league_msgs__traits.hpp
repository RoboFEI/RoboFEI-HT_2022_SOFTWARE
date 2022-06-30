// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from messages:msg/HumanoidLeagueMsgs.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__TRAITS_HPP_
#define MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__TRAITS_HPP_

#include "messages/msg/detail/humanoid_league_msgs__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__traits.hpp"

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<messages::msg::HumanoidLeagueMsgs>()
{
  return "messages::msg::HumanoidLeagueMsgs";
}

template<>
inline const char * name<messages::msg::HumanoidLeagueMsgs>()
{
  return "messages/msg/HumanoidLeagueMsgs";
}

template<>
struct has_fixed_size<messages::msg::HumanoidLeagueMsgs>
  : std::integral_constant<bool, false> {};

template<>
struct has_bounded_size<messages::msg::HumanoidLeagueMsgs>
  : std::integral_constant<bool, false> {};

template<>
struct is_message<messages::msg::HumanoidLeagueMsgs>
  : std::true_type {};

}  // namespace rosidl_generator_traits

#endif  // MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__TRAITS_HPP_
