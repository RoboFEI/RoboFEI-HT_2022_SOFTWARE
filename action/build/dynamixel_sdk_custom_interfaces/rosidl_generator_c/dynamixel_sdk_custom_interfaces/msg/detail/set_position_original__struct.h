// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dynamixel_sdk_custom_interfaces:msg/SetPositionOriginal.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_H_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/SetPositionOriginal in the package dynamixel_sdk_custom_interfaces.
typedef struct dynamixel_sdk_custom_interfaces__msg__SetPositionOriginal
{
  uint8_t id;
  int32_t position;
} dynamixel_sdk_custom_interfaces__msg__SetPositionOriginal;

// Struct for a sequence of dynamixel_sdk_custom_interfaces__msg__SetPositionOriginal.
typedef struct dynamixel_sdk_custom_interfaces__msg__SetPositionOriginal__Sequence
{
  dynamixel_sdk_custom_interfaces__msg__SetPositionOriginal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dynamixel_sdk_custom_interfaces__msg__SetPositionOriginal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_H_
