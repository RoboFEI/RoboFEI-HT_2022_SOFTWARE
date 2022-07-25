// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:msg/SetPosition.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION__STRUCT_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Include directives for member types
// Member 'id'
// Member 'position'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/SetPosition in the package custom_interfaces.
typedef struct custom_interfaces__msg__SetPosition
{
  rosidl_runtime_c__uint8__Sequence id;
  rosidl_runtime_c__int32__Sequence position;
} custom_interfaces__msg__SetPosition;

// Struct for a sequence of custom_interfaces__msg__SetPosition.
typedef struct custom_interfaces__msg__SetPosition__Sequence
{
  custom_interfaces__msg__SetPosition * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__msg__SetPosition__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION__STRUCT_H_
