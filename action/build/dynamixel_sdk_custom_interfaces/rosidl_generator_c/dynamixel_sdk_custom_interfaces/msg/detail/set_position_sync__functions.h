// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from dynamixel_sdk_custom_interfaces:msg/SetPositionSync.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__FUNCTIONS_H_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "dynamixel_sdk_custom_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "dynamixel_sdk_custom_interfaces/msg/detail/set_position_sync__struct.h"

/// Initialize msg/SetPositionSync message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync
 * )) before or use
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
bool
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__init(dynamixel_sdk_custom_interfaces__msg__SetPositionSync * msg);

/// Finalize msg/SetPositionSync message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
void
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__fini(dynamixel_sdk_custom_interfaces__msg__SetPositionSync * msg);

/// Create msg/SetPositionSync message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
dynamixel_sdk_custom_interfaces__msg__SetPositionSync *
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__create();

/// Destroy msg/SetPositionSync message.
/**
 * It calls
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
void
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__destroy(dynamixel_sdk_custom_interfaces__msg__SetPositionSync * msg);


/// Initialize array of msg/SetPositionSync messages.
/**
 * It allocates the memory for the number of elements and calls
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
bool
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence__init(dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence * array, size_t size);

/// Finalize array of msg/SetPositionSync messages.
/**
 * It calls
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
void
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence__fini(dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence * array);

/// Create array of msg/SetPositionSync messages.
/**
 * It allocates the memory for the array and calls
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence *
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence__create(size_t size);

/// Destroy array of msg/SetPositionSync messages.
/**
 * It calls
 * dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_dynamixel_sdk_custom_interfaces
void
dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence__destroy(dynamixel_sdk_custom_interfaces__msg__SetPositionSync__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__FUNCTIONS_H_
