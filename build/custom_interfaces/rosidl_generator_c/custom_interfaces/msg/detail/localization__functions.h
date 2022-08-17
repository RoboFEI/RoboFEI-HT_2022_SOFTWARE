// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from custom_interfaces:msg/Localization.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__FUNCTIONS_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "custom_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "custom_interfaces/msg/detail/localization__struct.h"

/// Initialize msg/Localization message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * custom_interfaces__msg__Localization
 * )) before or use
 * custom_interfaces__msg__Localization__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
bool
custom_interfaces__msg__Localization__init(custom_interfaces__msg__Localization * msg);

/// Finalize msg/Localization message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__msg__Localization__fini(custom_interfaces__msg__Localization * msg);

/// Create msg/Localization message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * custom_interfaces__msg__Localization__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
custom_interfaces__msg__Localization *
custom_interfaces__msg__Localization__create();

/// Destroy msg/Localization message.
/**
 * It calls
 * custom_interfaces__msg__Localization__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__msg__Localization__destroy(custom_interfaces__msg__Localization * msg);


/// Initialize array of msg/Localization messages.
/**
 * It allocates the memory for the number of elements and calls
 * custom_interfaces__msg__Localization__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
bool
custom_interfaces__msg__Localization__Sequence__init(custom_interfaces__msg__Localization__Sequence * array, size_t size);

/// Finalize array of msg/Localization messages.
/**
 * It calls
 * custom_interfaces__msg__Localization__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__msg__Localization__Sequence__fini(custom_interfaces__msg__Localization__Sequence * array);

/// Create array of msg/Localization messages.
/**
 * It allocates the memory for the array and calls
 * custom_interfaces__msg__Localization__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
custom_interfaces__msg__Localization__Sequence *
custom_interfaces__msg__Localization__Sequence__create(size_t size);

/// Destroy array of msg/Localization messages.
/**
 * It calls
 * custom_interfaces__msg__Localization__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__msg__Localization__Sequence__destroy(custom_interfaces__msg__Localization__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__FUNCTIONS_H_
