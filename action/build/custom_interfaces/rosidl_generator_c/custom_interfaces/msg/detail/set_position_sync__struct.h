// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:msg/SetPositionSync.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_H_

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

// Struct defined in msg/SetPositionSync in the package custom_interfaces.
typedef struct custom_interfaces__msg__SetPositionSync
{
  rosidl_runtime_c__uint8__Sequence id;
  rosidl_runtime_c__int32__Sequence position;
} custom_interfaces__msg__SetPositionSync;

// Struct for a sequence of custom_interfaces__msg__SetPositionSync.
typedef struct custom_interfaces__msg__SetPositionSync__Sequence
{
  custom_interfaces__msg__SetPositionSync * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__msg__SetPositionSync__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_H_
