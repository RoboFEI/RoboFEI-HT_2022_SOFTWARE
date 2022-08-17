// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:msg/Walk.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__WALK__STRUCT_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__WALK__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Walk in the package custom_interfaces.
typedef struct custom_interfaces__msg__Walk
{
  uint8_t walk;
} custom_interfaces__msg__Walk;

// Struct for a sequence of custom_interfaces__msg__Walk.
typedef struct custom_interfaces__msg__Walk__Sequence
{
  custom_interfaces__msg__Walk * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__msg__Walk__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__WALK__STRUCT_H_
