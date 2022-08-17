// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:srv/GetPosition.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__GET_POSITION__STRUCT_H_
#define CUSTOM_INTERFACES__SRV__DETAIL__GET_POSITION__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in srv/GetPosition in the package custom_interfaces.
typedef struct custom_interfaces__srv__GetPosition_Request
{
  uint8_t id;
} custom_interfaces__srv__GetPosition_Request;

// Struct for a sequence of custom_interfaces__srv__GetPosition_Request.
typedef struct custom_interfaces__srv__GetPosition_Request__Sequence
{
  custom_interfaces__srv__GetPosition_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__GetPosition_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/GetPosition in the package custom_interfaces.
typedef struct custom_interfaces__srv__GetPosition_Response
{
  int32_t position;
} custom_interfaces__srv__GetPosition_Response;

// Struct for a sequence of custom_interfaces__srv__GetPosition_Response.
typedef struct custom_interfaces__srv__GetPosition_Response__Sequence
{
  custom_interfaces__srv__GetPosition_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__GetPosition_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__GET_POSITION__STRUCT_H_
