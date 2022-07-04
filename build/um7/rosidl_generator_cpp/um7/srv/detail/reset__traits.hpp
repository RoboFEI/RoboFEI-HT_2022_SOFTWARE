// generated from rosidl_generator_cpp/resource/idl__traits.hpp.em
// with input from um7:srv/Reset.idl
// generated code does not contain a copyright notice

#ifndef UM7__SRV__DETAIL__RESET__TRAITS_HPP_
#define UM7__SRV__DETAIL__RESET__TRAITS_HPP_

#include "um7/srv/detail/reset__struct.hpp"
#include <rosidl_runtime_cpp/traits.hpp>
#include <stdint.h>
#include <type_traits>

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<um7::srv::Reset_Request>()
{
  return "um7::srv::Reset_Request";
}

template<>
inline const char * name<um7::srv::Reset_Request>()
{
  return "um7/srv/Reset_Request";
}

template<>
struct has_fixed_size<um7::srv::Reset_Request>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<um7::srv::Reset_Request>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<um7::srv::Reset_Request>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<um7::srv::Reset_Response>()
{
  return "um7::srv::Reset_Response";
}

template<>
inline const char * name<um7::srv::Reset_Response>()
{
  return "um7/srv/Reset_Response";
}

template<>
struct has_fixed_size<um7::srv::Reset_Response>
  : std::integral_constant<bool, true> {};

template<>
struct has_bounded_size<um7::srv::Reset_Response>
  : std::integral_constant<bool, true> {};

template<>
struct is_message<um7::srv::Reset_Response>
  : std::true_type {};

}  // namespace rosidl_generator_traits

namespace rosidl_generator_traits
{

template<>
inline const char * data_type<um7::srv::Reset>()
{
  return "um7::srv::Reset";
}

template<>
inline const char * name<um7::srv::Reset>()
{
  return "um7/srv/Reset";
}

template<>
struct has_fixed_size<um7::srv::Reset>
  : std::integral_constant<
    bool,
    has_fixed_size<um7::srv::Reset_Request>::value &&
    has_fixed_size<um7::srv::Reset_Response>::value
  >
{
};

template<>
struct has_bounded_size<um7::srv::Reset>
  : std::integral_constant<
    bool,
    has_bounded_size<um7::srv::Reset_Request>::value &&
    has_bounded_size<um7::srv::Reset_Response>::value
  >
{
};

template<>
struct is_service<um7::srv::Reset>
  : std::true_type
{
};

template<>
struct is_service_request<um7::srv::Reset_Request>
  : std::true_type
{
};

template<>
struct is_service_response<um7::srv::Reset_Response>
  : std::true_type
{
};

}  // namespace rosidl_generator_traits

#endif  // UM7__SRV__DETAIL__RESET__TRAITS_HPP_
