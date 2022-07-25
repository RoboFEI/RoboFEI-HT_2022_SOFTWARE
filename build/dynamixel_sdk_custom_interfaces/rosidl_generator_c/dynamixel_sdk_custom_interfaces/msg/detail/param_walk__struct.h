// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from dynamixel_sdk_custom_interfaces:msg/ParamWalk.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__STRUCT_H_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/ParamWalk in the package dynamixel_sdk_custom_interfaces.
typedef struct dynamixel_sdk_custom_interfaces__msg__ParamWalk
{
  double walk;
  double sidle;
  double turn;
} dynamixel_sdk_custom_interfaces__msg__ParamWalk;

// Struct for a sequence of dynamixel_sdk_custom_interfaces__msg__ParamWalk.
typedef struct dynamixel_sdk_custom_interfaces__msg__ParamWalk__Sequence
{
  dynamixel_sdk_custom_interfaces__msg__ParamWalk * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} dynamixel_sdk_custom_interfaces__msg__ParamWalk__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__STRUCT_H_
