// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dynamixel_sdk_custom_interfaces:msg/Walk.idl
// generated code does not contain a copyright notice
#include "dynamixel_sdk_custom_interfaces/msg/detail/walk__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
dynamixel_sdk_custom_interfaces__msg__Walk__init(dynamixel_sdk_custom_interfaces__msg__Walk * msg)
{
  if (!msg) {
    return false;
  }
  // walk
  return true;
}

void
dynamixel_sdk_custom_interfaces__msg__Walk__fini(dynamixel_sdk_custom_interfaces__msg__Walk * msg)
{
  if (!msg) {
    return;
  }
  // walk
}

dynamixel_sdk_custom_interfaces__msg__Walk *
dynamixel_sdk_custom_interfaces__msg__Walk__create()
{
  dynamixel_sdk_custom_interfaces__msg__Walk * msg = (dynamixel_sdk_custom_interfaces__msg__Walk *)malloc(sizeof(dynamixel_sdk_custom_interfaces__msg__Walk));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dynamixel_sdk_custom_interfaces__msg__Walk));
  bool success = dynamixel_sdk_custom_interfaces__msg__Walk__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
dynamixel_sdk_custom_interfaces__msg__Walk__destroy(dynamixel_sdk_custom_interfaces__msg__Walk * msg)
{
  if (msg) {
    dynamixel_sdk_custom_interfaces__msg__Walk__fini(msg);
  }
  free(msg);
}


bool
dynamixel_sdk_custom_interfaces__msg__Walk__Sequence__init(dynamixel_sdk_custom_interfaces__msg__Walk__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  dynamixel_sdk_custom_interfaces__msg__Walk * data = NULL;
  if (size) {
    data = (dynamixel_sdk_custom_interfaces__msg__Walk *)calloc(size, sizeof(dynamixel_sdk_custom_interfaces__msg__Walk));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dynamixel_sdk_custom_interfaces__msg__Walk__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dynamixel_sdk_custom_interfaces__msg__Walk__fini(&data[i - 1]);
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
dynamixel_sdk_custom_interfaces__msg__Walk__Sequence__fini(dynamixel_sdk_custom_interfaces__msg__Walk__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dynamixel_sdk_custom_interfaces__msg__Walk__fini(&array->data[i]);
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

dynamixel_sdk_custom_interfaces__msg__Walk__Sequence *
dynamixel_sdk_custom_interfaces__msg__Walk__Sequence__create(size_t size)
{
  dynamixel_sdk_custom_interfaces__msg__Walk__Sequence * array = (dynamixel_sdk_custom_interfaces__msg__Walk__Sequence *)malloc(sizeof(dynamixel_sdk_custom_interfaces__msg__Walk__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = dynamixel_sdk_custom_interfaces__msg__Walk__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
dynamixel_sdk_custom_interfaces__msg__Walk__Sequence__destroy(dynamixel_sdk_custom_interfaces__msg__Walk__Sequence * array)
{
  if (array) {
    dynamixel_sdk_custom_interfaces__msg__Walk__Sequence__fini(array);
  }
  free(array);
}
