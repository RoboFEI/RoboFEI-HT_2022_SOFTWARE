// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interfaces_vision:msg/Decision.idl
// generated code does not contain a copyright notice
#include "custom_interfaces_vision/msg/detail/decision__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
custom_interfaces_vision__msg__Decision__init(custom_interfaces_vision__msg__Decision * msg)
{
  if (!msg) {
    return false;
  }
  // decision
  return true;
}

void
custom_interfaces_vision__msg__Decision__fini(custom_interfaces_vision__msg__Decision * msg)
{
  if (!msg) {
    return;
  }
  // decision
}

custom_interfaces_vision__msg__Decision *
custom_interfaces_vision__msg__Decision__create()
{
  custom_interfaces_vision__msg__Decision * msg = (custom_interfaces_vision__msg__Decision *)malloc(sizeof(custom_interfaces_vision__msg__Decision));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces_vision__msg__Decision));
  bool success = custom_interfaces_vision__msg__Decision__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
custom_interfaces_vision__msg__Decision__destroy(custom_interfaces_vision__msg__Decision * msg)
{
  if (msg) {
    custom_interfaces_vision__msg__Decision__fini(msg);
  }
  free(msg);
}


bool
custom_interfaces_vision__msg__Decision__Sequence__init(custom_interfaces_vision__msg__Decision__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  custom_interfaces_vision__msg__Decision * data = NULL;
  if (size) {
    data = (custom_interfaces_vision__msg__Decision *)calloc(size, sizeof(custom_interfaces_vision__msg__Decision));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces_vision__msg__Decision__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces_vision__msg__Decision__fini(&data[i - 1]);
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
custom_interfaces_vision__msg__Decision__Sequence__fini(custom_interfaces_vision__msg__Decision__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_interfaces_vision__msg__Decision__fini(&array->data[i]);
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

custom_interfaces_vision__msg__Decision__Sequence *
custom_interfaces_vision__msg__Decision__Sequence__create(size_t size)
{
  custom_interfaces_vision__msg__Decision__Sequence * array = (custom_interfaces_vision__msg__Decision__Sequence *)malloc(sizeof(custom_interfaces_vision__msg__Decision__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces_vision__msg__Decision__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
custom_interfaces_vision__msg__Decision__Sequence__destroy(custom_interfaces_vision__msg__Decision__Sequence * array)
{
  if (array) {
    custom_interfaces_vision__msg__Decision__Sequence__fini(array);
  }
  free(array);
}
