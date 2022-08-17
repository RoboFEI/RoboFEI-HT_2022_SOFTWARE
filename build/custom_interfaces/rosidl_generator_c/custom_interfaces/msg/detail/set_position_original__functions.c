// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interfaces:msg/SetPositionOriginal.idl
// generated code does not contain a copyright notice
#include "custom_interfaces/msg/detail/set_position_original__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
custom_interfaces__msg__SetPositionOriginal__init(custom_interfaces__msg__SetPositionOriginal * msg)
{
  if (!msg) {
    return false;
  }
  // id
  // address
  // position
  return true;
}

void
custom_interfaces__msg__SetPositionOriginal__fini(custom_interfaces__msg__SetPositionOriginal * msg)
{
  if (!msg) {
    return;
  }
  // id
  // address
  // position
}

custom_interfaces__msg__SetPositionOriginal *
custom_interfaces__msg__SetPositionOriginal__create()
{
  custom_interfaces__msg__SetPositionOriginal * msg = (custom_interfaces__msg__SetPositionOriginal *)malloc(sizeof(custom_interfaces__msg__SetPositionOriginal));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces__msg__SetPositionOriginal));
  bool success = custom_interfaces__msg__SetPositionOriginal__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
custom_interfaces__msg__SetPositionOriginal__destroy(custom_interfaces__msg__SetPositionOriginal * msg)
{
  if (msg) {
    custom_interfaces__msg__SetPositionOriginal__fini(msg);
  }
  free(msg);
}


bool
custom_interfaces__msg__SetPositionOriginal__Sequence__init(custom_interfaces__msg__SetPositionOriginal__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  custom_interfaces__msg__SetPositionOriginal * data = NULL;
  if (size) {
    data = (custom_interfaces__msg__SetPositionOriginal *)calloc(size, sizeof(custom_interfaces__msg__SetPositionOriginal));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces__msg__SetPositionOriginal__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces__msg__SetPositionOriginal__fini(&data[i - 1]);
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
custom_interfaces__msg__SetPositionOriginal__Sequence__fini(custom_interfaces__msg__SetPositionOriginal__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_interfaces__msg__SetPositionOriginal__fini(&array->data[i]);
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

custom_interfaces__msg__SetPositionOriginal__Sequence *
custom_interfaces__msg__SetPositionOriginal__Sequence__create(size_t size)
{
  custom_interfaces__msg__SetPositionOriginal__Sequence * array = (custom_interfaces__msg__SetPositionOriginal__Sequence *)malloc(sizeof(custom_interfaces__msg__SetPositionOriginal__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces__msg__SetPositionOriginal__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
custom_interfaces__msg__SetPositionOriginal__Sequence__destroy(custom_interfaces__msg__SetPositionOriginal__Sequence * array)
{
  if (array) {
    custom_interfaces__msg__SetPositionOriginal__Sequence__fini(array);
  }
  free(array);
}
