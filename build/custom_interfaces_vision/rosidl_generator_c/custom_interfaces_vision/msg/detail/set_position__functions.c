// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interfaces_vision:msg/SetPosition.idl
// generated code does not contain a copyright notice
#include "custom_interfaces_vision/msg/detail/set_position__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `id`
// Member `position`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
custom_interfaces_vision__msg__SetPosition__init(custom_interfaces_vision__msg__SetPosition * msg)
{
  if (!msg) {
    return false;
  }
  // id
  if (!rosidl_runtime_c__uint8__Sequence__init(&msg->id, 0)) {
    custom_interfaces_vision__msg__SetPosition__fini(msg);
    return false;
  }
  // position
  if (!rosidl_runtime_c__int32__Sequence__init(&msg->position, 0)) {
    custom_interfaces_vision__msg__SetPosition__fini(msg);
    return false;
  }
  return true;
}

void
custom_interfaces_vision__msg__SetPosition__fini(custom_interfaces_vision__msg__SetPosition * msg)
{
  if (!msg) {
    return;
  }
  // id
  rosidl_runtime_c__uint8__Sequence__fini(&msg->id);
  // position
  rosidl_runtime_c__int32__Sequence__fini(&msg->position);
}

custom_interfaces_vision__msg__SetPosition *
custom_interfaces_vision__msg__SetPosition__create()
{
  custom_interfaces_vision__msg__SetPosition * msg = (custom_interfaces_vision__msg__SetPosition *)malloc(sizeof(custom_interfaces_vision__msg__SetPosition));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces_vision__msg__SetPosition));
  bool success = custom_interfaces_vision__msg__SetPosition__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
custom_interfaces_vision__msg__SetPosition__destroy(custom_interfaces_vision__msg__SetPosition * msg)
{
  if (msg) {
    custom_interfaces_vision__msg__SetPosition__fini(msg);
  }
  free(msg);
}


bool
custom_interfaces_vision__msg__SetPosition__Sequence__init(custom_interfaces_vision__msg__SetPosition__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  custom_interfaces_vision__msg__SetPosition * data = NULL;
  if (size) {
    data = (custom_interfaces_vision__msg__SetPosition *)calloc(size, sizeof(custom_interfaces_vision__msg__SetPosition));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces_vision__msg__SetPosition__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces_vision__msg__SetPosition__fini(&data[i - 1]);
      }
      free(data);
      return false;
    }
  }
  array->data = data;
  array->size = size;
  array->capacity = size;
  return true;
}

void
custom_interfaces_vision__msg__SetPosition__Sequence__fini(custom_interfaces_vision__msg__SetPosition__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_interfaces_vision__msg__SetPosition__fini(&array->data[i]);
    }
    free(array->data);
    array->data = NULL;
    array->size = 0;
    array->capacity = 0;
  } else {
    // ensure that data, size, and capacity values are consistent
    assert(0 == array->size);
    assert(0 == array->capacity);
  }
}

custom_interfaces_vision__msg__SetPosition__Sequence *
custom_interfaces_vision__msg__SetPosition__Sequence__create(size_t size)
{
  custom_interfaces_vision__msg__SetPosition__Sequence * array = (custom_interfaces_vision__msg__SetPosition__Sequence *)malloc(sizeof(custom_interfaces_vision__msg__SetPosition__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces_vision__msg__SetPosition__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
custom_interfaces_vision__msg__SetPosition__Sequence__destroy(custom_interfaces_vision__msg__SetPosition__Sequence * array)
{
  if (array) {
    custom_interfaces_vision__msg__SetPosition__Sequence__fini(array);
  }
  free(array);
}
