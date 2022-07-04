// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces_vision:msg/Vision.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES_VISION__MSG__DETAIL__VISION__STRUCT_H_
#define CUSTOM_INTERFACES_VISION__MSG__DETAIL__VISION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in msg/Vision in the package custom_interfaces_vision.
typedef struct custom_interfaces_vision__msg__Vision
{
  bool ball_detected;
  bool ball_left;
  bool ball_center_left;
  bool ball_right;
  bool ball_center_right;
  bool ball_far;
  bool ball_med;
  bool ball_close;
} custom_interfaces_vision__msg__Vision;

// Struct for a sequence of custom_interfaces_vision__msg__Vision.
typedef struct custom_interfaces_vision__msg__Vision__Sequence
{
  custom_interfaces_vision__msg__Vision * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces_vision__msg__Vision__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES_VISION__MSG__DETAIL__VISION__STRUCT_H_
