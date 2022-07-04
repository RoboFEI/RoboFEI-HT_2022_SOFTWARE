// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces_vision:msg/Decision.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES_VISION__MSG__DETAIL__DECISION__STRUCT_H_
#define CUSTOM_INTERFACES_VISION__MSG__DETAIL__DECISION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Decision in the package custom_interfaces_vision.
typedef struct custom_interfaces_vision__msg__Decision
{
  uint8_t decision;
} custom_interfaces_vision__msg__Decision;

// Struct for a sequence of custom_interfaces_vision__msg__Decision.
typedef struct custom_interfaces_vision__msg__Decision__Sequence
{
  custom_interfaces_vision__msg__Decision * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces_vision__msg__Decision__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES_VISION__MSG__DETAIL__DECISION__STRUCT_H_
