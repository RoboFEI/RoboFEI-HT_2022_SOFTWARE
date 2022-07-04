// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from custom_interfaces_vision:msg/Vision.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES_VISION__MSG__DETAIL__VISION__FUNCTIONS_H_
#define CUSTOM_INTERFACES_VISION__MSG__DETAIL__VISION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "custom_interfaces_vision/msg/rosidl_generator_c__visibility_control.h"

#include "custom_interfaces_vision/msg/detail/vision__struct.h"

/// Initialize msg/Vision message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * custom_interfaces_vision__msg__Vision
 * )) before or use
 * custom_interfaces_vision__msg__Vision__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
bool
custom_interfaces_vision__msg__Vision__init(custom_interfaces_vision__msg__Vision * msg);

/// Finalize msg/Vision message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
void
custom_interfaces_vision__msg__Vision__fini(custom_interfaces_vision__msg__Vision * msg);

/// Create msg/Vision message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * custom_interfaces_vision__msg__Vision__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
custom_interfaces_vision__msg__Vision *
custom_interfaces_vision__msg__Vision__create();

/// Destroy msg/Vision message.
/**
 * It calls
 * custom_interfaces_vision__msg__Vision__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
void
custom_interfaces_vision__msg__Vision__destroy(custom_interfaces_vision__msg__Vision * msg);


/// Initialize array of msg/Vision messages.
/**
 * It allocates the memory for the number of elements and calls
 * custom_interfaces_vision__msg__Vision__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
bool
custom_interfaces_vision__msg__Vision__Sequence__init(custom_interfaces_vision__msg__Vision__Sequence * array, size_t size);

/// Finalize array of msg/Vision messages.
/**
 * It calls
 * custom_interfaces_vision__msg__Vision__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
void
custom_interfaces_vision__msg__Vision__Sequence__fini(custom_interfaces_vision__msg__Vision__Sequence * array);

/// Create array of msg/Vision messages.
/**
 * It allocates the memory for the array and calls
 * custom_interfaces_vision__msg__Vision__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
custom_interfaces_vision__msg__Vision__Sequence *
custom_interfaces_vision__msg__Vision__Sequence__create(size_t size);

/// Destroy array of msg/Vision messages.
/**
 * It calls
 * custom_interfaces_vision__msg__Vision__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces_vision
void
custom_interfaces_vision__msg__Vision__Sequence__destroy(custom_interfaces_vision__msg__Vision__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES_VISION__MSG__DETAIL__VISION__FUNCTIONS_H_
