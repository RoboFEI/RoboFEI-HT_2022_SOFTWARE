// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:srv/Reset.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__RESET__STRUCT_H_
#define CUSTOM_INTERFACES__SRV__DETAIL__RESET__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

// Struct defined in srv/Reset in the package custom_interfaces.
typedef struct custom_interfaces__srv__Reset_Request
{
  bool zero_gyros;
  bool reset_ekf;
  bool set_mag_ref;
} custom_interfaces__srv__Reset_Request;

// Struct for a sequence of custom_interfaces__srv__Reset_Request.
typedef struct custom_interfaces__srv__Reset_Request__Sequence
{
  custom_interfaces__srv__Reset_Request * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__Reset_Request__Sequence;


// Constants defined in the message

// Struct defined in srv/Reset in the package custom_interfaces.
typedef struct custom_interfaces__srv__Reset_Response
{
  uint8_t structure_needs_at_least_one_member;
} custom_interfaces__srv__Reset_Response;

// Struct for a sequence of custom_interfaces__srv__Reset_Response.
typedef struct custom_interfaces__srv__Reset_Response__Sequence
{
  custom_interfaces__srv__Reset_Response * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__srv__Reset_Response__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__RESET__STRUCT_H_
