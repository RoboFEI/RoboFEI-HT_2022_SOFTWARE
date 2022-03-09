// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dynamixel_sdk_custom_interfaces:msg/SetPositionSync.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_H_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_H_

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

// Struct defined in msg/SetPositionSync in the package dynamixel_sdk_custom_interfaces.
typedef struct dynamixel_sdk_custom_interfaces__msg__SetPositionSync
{
  rosidl_runtime_c__uint8__Sequence id;
  rosidl_runtime_c__int32__Sequence position;
} dynamixel_sdk_custom_interfaces__msg__SetPositionSync;

// Struct for a sequence of dynamixel_sdk_custom_interfaces__msg__SetPositionSync.
typedef struct dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence
{
  dynamixel_sdk_custom_interfaces__msg__SetPositionSync * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_H_
