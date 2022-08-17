// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:msg/SetPositionOriginal.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/SetPositionOriginal in the package custom_interfaces.
typedef struct custom_interfaces__msg__SetPositionOriginal
{
  uint8_t id;
  int32_t address;
  int32_t position;
} custom_interfaces__msg__SetPositionOriginal;

// Struct for a sequence of custom_interfaces__msg__SetPositionOriginal.
typedef struct custom_interfaces__msg__SetPositionOriginal__Sequence
{
  custom_interfaces__msg__SetPositionOriginal * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__msg__SetPositionOriginal__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_H_
