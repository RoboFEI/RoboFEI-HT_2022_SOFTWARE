// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from dynamixel_sdk_custom_interfaces:msg/Decision.idl
// generated code does not contain a copyright notice
#include "dynamixel_sdk_custom_interfaces/msg/detail/decision__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


bool
dynamixel_sdk_custom_interfaces__msg__Decision__init(dynamixel_sdk_custom_interfaces__msg__Decision * msg)
{
  if (!msg) {
    return false;
  }
  // decision
  return true;
}

void
dynamixel_sdk_custom_interfaces__msg__Decision__fini(dynamixel_sdk_custom_interfaces__msg__Decision * msg)
{
  if (!msg) {
    return;
  }
  // decision
}

bool
dynamixel_sdk_custom_interfaces__msg__Decision__are_equal(const dynamixel_sdk_custom_interfaces__msg__Decision * lhs, const dynamixel_sdk_custom_interfaces__msg__Decision * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  // decision
  if (lhs->decision != rhs->decision) {
    return false;
  }
  return true;
}

bool
dynamixel_sdk_custom_interfaces__msg__Decision__copy(
  const dynamixel_sdk_custom_interfaces__msg__Decision * input,
  dynamixel_sdk_custom_interfaces__msg__Decision * output)
{
  if (!input || !output) {
    return false;
  }
  // decision
  output->decision = input->decision;
  return true;
}

dynamixel_sdk_custom_interfaces__msg__Decision *
dynamixel_sdk_custom_interfaces__msg__Decision__create()
{
  dynamixel_sdk_custom_interfaces__msg__Decision * msg = (dynamixel_sdk_custom_interfaces__msg__Decision *)malloc(sizeof(dynamixel_sdk_custom_interfaces__msg__Decision));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(dynamixel_sdk_custom_interfaces__msg__Decision));
  bool success = dynamixel_sdk_custom_interfaces__msg__Decision__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
dynamixel_sdk_custom_interfaces__msg__Decision__destroy(dynamixel_sdk_custom_interfaces__msg__Decision * msg)
{
  if (msg) {
    dynamixel_sdk_custom_interfaces__msg__Decision__fini(msg);
  }
  free(msg);
}


bool
dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__init(dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  dynamixel_sdk_custom_interfaces__msg__Decision * data = NULL;
  if (size) {
    data = (dynamixel_sdk_custom_interfaces__msg__Decision *)calloc(size, sizeof(dynamixel_sdk_custom_interfaces__msg__Decision));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = dynamixel_sdk_custom_interfaces__msg__Decision__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        dynamixel_sdk_custom_interfaces__msg__Decision__fini(&data[i - 1]);
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
dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__fini(dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      dynamixel_sdk_custom_interfaces__msg__Decision__fini(&array->data[i]);
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

dynamixel_sdk_custom_interfaces__msg__Decision__Sequence *
dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__create(size_t size)
{
  dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * array = (dynamixel_sdk_custom_interfaces__msg__Decision__Sequence *)malloc(sizeof(dynamixel_sdk_custom_interfaces__msg__Decision__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__destroy(dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * array)
{
  if (array) {
    dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__fini(array);
  }
  free(array);
}

bool
dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__are_equal(const dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * lhs, const dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * rhs)
{
  if (!lhs || !rhs) {
    return false;
  }
  if (lhs->size != rhs->size) {
    return false;
  }
  for (size_t i = 0; i < lhs->size; ++i) {
    if (!dynamixel_sdk_custom_interfaces__msg__Decision__are_equal(&(lhs->data[i]), &(rhs->data[i]))) {
      return false;
    }
  }
  return true;
}

bool
dynamixel_sdk_custom_interfaces__msg__Decision__Sequence__copy(
  const dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * input,
  dynamixel_sdk_custom_interfaces__msg__Decision__Sequence * output)
{
  if (!input || !output) {
    return false;
  }
  if (output->capacity < input->size) {
    const size_t allocation_size =
      input->size * sizeof(dynamixel_sdk_custom_interfaces__msg__Decision);
    dynamixel_sdk_custom_interfaces__msg__Decision * data =
      (dynamixel_sdk_custom_interfaces__msg__Decision *)realloc(output->data, allocation_size);
    if (!data) {
      return false;
    }
    for (size_t i = output->capacity; i < input->size; ++i) {
      if (!dynamixel_sdk_custom_interfaces__msg__Decision__init(&data[i])) {
        /* free currently allocated and return false */
        for (; i-- > output->capacity; ) {
          dynamixel_sdk_custom_interfaces__msg__Decision__fini(&data[i]);
        }
        free(data);
        return false;
      }
    }
    output->data = data;
    output->capacity = input->size;
  }
  output->size = input->size;
  for (size_t i = 0; i < input->size; ++i) {
    if (!dynamixel_sdk_custom_interfaces__msg__Decision__copy(
        &(input->data[i]), &(output->data[i])))
    {
      return false;
    }
  }
  return true;
}
