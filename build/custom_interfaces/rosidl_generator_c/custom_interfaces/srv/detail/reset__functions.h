// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from custom_interfaces:srv/Reset.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__SRV__DETAIL__RESET__FUNCTIONS_H_
#define CUSTOM_INTERFACES__SRV__DETAIL__RESET__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "custom_interfaces/msg/rosidl_generator_c__visibility_control.h"

#include "custom_interfaces/srv/detail/reset__struct.h"

/// Initialize srv/Reset message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * custom_interfaces__srv__Reset_Request
 * )) before or use
 * custom_interfaces__srv__Reset_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
bool
custom_interfaces__srv__Reset_Request__init(custom_interfaces__srv__Reset_Request * msg);

/// Finalize srv/Reset message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Request__fini(custom_interfaces__srv__Reset_Request * msg);

/// Create srv/Reset message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * custom_interfaces__srv__Reset_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
custom_interfaces__srv__Reset_Request *
custom_interfaces__srv__Reset_Request__create();

/// Destroy srv/Reset message.
/**
 * It calls
 * custom_interfaces__srv__Reset_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Request__destroy(custom_interfaces__srv__Reset_Request * msg);


/// Initialize array of srv/Reset messages.
/**
 * It allocates the memory for the number of elements and calls
 * custom_interfaces__srv__Reset_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
bool
custom_interfaces__srv__Reset_Request__Sequence__init(custom_interfaces__srv__Reset_Request__Sequence * array, size_t size);

/// Finalize array of srv/Reset messages.
/**
 * It calls
 * custom_interfaces__srv__Reset_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Request__Sequence__fini(custom_interfaces__srv__Reset_Request__Sequence * array);

/// Create array of srv/Reset messages.
/**
 * It allocates the memory for the array and calls
 * custom_interfaces__srv__Reset_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
custom_interfaces__srv__Reset_Request__Sequence *
custom_interfaces__srv__Reset_Request__Sequence__create(size_t size);

/// Destroy array of srv/Reset messages.
/**
 * It calls
 * custom_interfaces__srv__Reset_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Request__Sequence__destroy(custom_interfaces__srv__Reset_Request__Sequence * array);

/// Initialize srv/Reset message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * custom_interfaces__srv__Reset_Response
 * )) before or use
 * custom_interfaces__srv__Reset_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
bool
custom_interfaces__srv__Reset_Response__init(custom_interfaces__srv__Reset_Response * msg);

/// Finalize srv/Reset message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Response__fini(custom_interfaces__srv__Reset_Response * msg);

/// Create srv/Reset message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * custom_interfaces__srv__Reset_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
custom_interfaces__srv__Reset_Response *
custom_interfaces__srv__Reset_Response__create();

/// Destroy srv/Reset message.
/**
 * It calls
 * custom_interfaces__srv__Reset_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Response__destroy(custom_interfaces__srv__Reset_Response * msg);


/// Initialize array of srv/Reset messages.
/**
 * It allocates the memory for the number of elements and calls
 * custom_interfaces__srv__Reset_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
bool
custom_interfaces__srv__Reset_Response__Sequence__init(custom_interfaces__srv__Reset_Response__Sequence * array, size_t size);

/// Finalize array of srv/Reset messages.
/**
 * It calls
 * custom_interfaces__srv__Reset_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Response__Sequence__fini(custom_interfaces__srv__Reset_Response__Sequence * array);

/// Create array of srv/Reset messages.
/**
 * It allocates the memory for the array and calls
 * custom_interfaces__srv__Reset_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
custom_interfaces__srv__Reset_Response__Sequence *
custom_interfaces__srv__Reset_Response__Sequence__create(size_t size);

/// Destroy array of srv/Reset messages.
/**
 * It calls
 * custom_interfaces__srv__Reset_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_custom_interfaces
void
custom_interfaces__srv__Reset_Response__Sequence__destroy(custom_interfaces__srv__Reset_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__SRV__DETAIL__RESET__FUNCTIONS_H_
