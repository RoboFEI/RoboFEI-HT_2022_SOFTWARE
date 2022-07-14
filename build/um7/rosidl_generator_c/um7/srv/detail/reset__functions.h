// generated from rosidl_generator_c/resource/idl__functions.h.em
// with input from um7:srv/Reset.idl
// generated code does not contain a copyright notice

#ifndef UM7__SRV__DETAIL__RESET__FUNCTIONS_H_
#define UM7__SRV__DETAIL__RESET__FUNCTIONS_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stdlib.h>

#include "rosidl_runtime_c/visibility_control.h"
#include "um7/msg/rosidl_generator_c__visibility_control.h"

#include "um7/srv/detail/reset__struct.h"

/// Initialize srv/Reset message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * um7__srv__Reset_Request
 * )) before or use
 * um7__srv__Reset_Request__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
bool
um7__srv__Reset_Request__init(um7__srv__Reset_Request * msg);

/// Finalize srv/Reset message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Request__fini(um7__srv__Reset_Request * msg);

/// Create srv/Reset message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * um7__srv__Reset_Request__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
um7__srv__Reset_Request *
um7__srv__Reset_Request__create();

/// Destroy srv/Reset message.
/**
 * It calls
 * um7__srv__Reset_Request__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Request__destroy(um7__srv__Reset_Request * msg);


/// Initialize array of srv/Reset messages.
/**
 * It allocates the memory for the number of elements and calls
 * um7__srv__Reset_Request__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
bool
um7__srv__Reset_Request__Sequence__init(um7__srv__Reset_Request__Sequence * array, size_t size);

/// Finalize array of srv/Reset messages.
/**
 * It calls
 * um7__srv__Reset_Request__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Request__Sequence__fini(um7__srv__Reset_Request__Sequence * array);

/// Create array of srv/Reset messages.
/**
 * It allocates the memory for the array and calls
 * um7__srv__Reset_Request__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
um7__srv__Reset_Request__Sequence *
um7__srv__Reset_Request__Sequence__create(size_t size);

/// Destroy array of srv/Reset messages.
/**
 * It calls
 * um7__srv__Reset_Request__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Request__Sequence__destroy(um7__srv__Reset_Request__Sequence * array);

/// Initialize srv/Reset message.
/**
 * If the init function is called twice for the same message without
 * calling fini inbetween previously allocated memory will be leaked.
 * \param[in,out] msg The previously allocated message pointer.
 * Fields without a default value will not be initialized by this function.
 * You might want to call memset(msg, 0, sizeof(
 * um7__srv__Reset_Response
 * )) before or use
 * um7__srv__Reset_Response__create()
 * to allocate and initialize the message.
 * \return true if initialization was successful, otherwise false
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
bool
um7__srv__Reset_Response__init(um7__srv__Reset_Response * msg);

/// Finalize srv/Reset message.
/**
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Response__fini(um7__srv__Reset_Response * msg);

/// Create srv/Reset message.
/**
 * It allocates the memory for the message, sets the memory to zero, and
 * calls
 * um7__srv__Reset_Response__init().
 * \return The pointer to the initialized message if successful,
 * otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
um7__srv__Reset_Response *
um7__srv__Reset_Response__create();

/// Destroy srv/Reset message.
/**
 * It calls
 * um7__srv__Reset_Response__fini()
 * and frees the memory of the message.
 * \param[in,out] msg The allocated message pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Response__destroy(um7__srv__Reset_Response * msg);


/// Initialize array of srv/Reset messages.
/**
 * It allocates the memory for the number of elements and calls
 * um7__srv__Reset_Response__init()
 * for each element of the array.
 * \param[in,out] array The allocated array pointer.
 * \param[in] size The size / capacity of the array.
 * \return true if initialization was successful, otherwise false
 * If the array pointer is valid and the size is zero it is guaranteed
 # to return true.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
bool
um7__srv__Reset_Response__Sequence__init(um7__srv__Reset_Response__Sequence * array, size_t size);

/// Finalize array of srv/Reset messages.
/**
 * It calls
 * um7__srv__Reset_Response__fini()
 * for each element of the array and frees the memory for the number of
 * elements.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Response__Sequence__fini(um7__srv__Reset_Response__Sequence * array);

/// Create array of srv/Reset messages.
/**
 * It allocates the memory for the array and calls
 * um7__srv__Reset_Response__Sequence__init().
 * \param[in] size The size / capacity of the array.
 * \return The pointer to the initialized array if successful, otherwise NULL
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
um7__srv__Reset_Response__Sequence *
um7__srv__Reset_Response__Sequence__create(size_t size);

/// Destroy array of srv/Reset messages.
/**
 * It calls
 * um7__srv__Reset_Response__Sequence__fini()
 * on the array,
 * and frees the memory of the array.
 * \param[in,out] array The initialized array pointer.
 */
ROSIDL_GENERATOR_C_PUBLIC_um7
void
um7__srv__Reset_Response__Sequence__destroy(um7__srv__Reset_Response__Sequence * array);

#ifdef __cplusplus
}
#endif

#endif  // UM7__SRV__DETAIL__RESET__FUNCTIONS_H_
