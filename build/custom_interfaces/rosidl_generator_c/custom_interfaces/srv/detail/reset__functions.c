// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interfaces:srv/Reset.idl
// generated code does not contain a copyright notice
#include "custom_interfaces/srv/detail/reset__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool
custom_interfaces__srv__Reset_Request__init(custom_interfaces__srv__Reset_Request * msg)
{
  if (!msg) {
    return false;
  }
  // zero_gyros
  // reset_ekf
  // set_mag_ref
  return true;
}

void
custom_interfaces__srv__Reset_Request__fini(custom_interfaces__srv__Reset_Request * msg)
{
  if (!msg) {
    return;
  }
  // zero_gyros
  // reset_ekf
  // set_mag_ref
}

custom_interfaces__srv__Reset_Request *
custom_interfaces__srv__Reset_Request__create()
{
  custom_interfaces__srv__Reset_Request * msg = (custom_interfaces__srv__Reset_Request *)malloc(sizeof(custom_interfaces__srv__Reset_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces__srv__Reset_Request));
  bool success = custom_interfaces__srv__Reset_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
custom_interfaces__srv__Reset_Request__destroy(custom_interfaces__srv__Reset_Request * msg)
{
  if (msg) {
    custom_interfaces__srv__Reset_Request__fini(msg);
  }
  free(msg);
}


bool
custom_interfaces__srv__Reset_Request__Sequence__init(custom_interfaces__srv__Reset_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  custom_interfaces__srv__Reset_Request * data = NULL;
  if (size) {
    data = (custom_interfaces__srv__Reset_Request *)calloc(size, sizeof(custom_interfaces__srv__Reset_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces__srv__Reset_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces__srv__Reset_Request__fini(&data[i - 1]);
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
custom_interfaces__srv__Reset_Request__Sequence__fini(custom_interfaces__srv__Reset_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_interfaces__srv__Reset_Request__fini(&array->data[i]);
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

custom_interfaces__srv__Reset_Request__Sequence *
custom_interfaces__srv__Reset_Request__Sequence__create(size_t size)
{
  custom_interfaces__srv__Reset_Request__Sequence * array = (custom_interfaces__srv__Reset_Request__Sequence *)malloc(sizeof(custom_interfaces__srv__Reset_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces__srv__Reset_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
custom_interfaces__srv__Reset_Request__Sequence__destroy(custom_interfaces__srv__Reset_Request__Sequence * array)
{
  if (array) {
    custom_interfaces__srv__Reset_Request__Sequence__fini(array);
  }
  free(array);
}


bool
custom_interfaces__srv__Reset_Response__init(custom_interfaces__srv__Reset_Response * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
custom_interfaces__srv__Reset_Response__fini(custom_interfaces__srv__Reset_Response * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

custom_interfaces__srv__Reset_Response *
custom_interfaces__srv__Reset_Response__create()
{
  custom_interfaces__srv__Reset_Response * msg = (custom_interfaces__srv__Reset_Response *)malloc(sizeof(custom_interfaces__srv__Reset_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces__srv__Reset_Response));
  bool success = custom_interfaces__srv__Reset_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
custom_interfaces__srv__Reset_Response__destroy(custom_interfaces__srv__Reset_Response * msg)
{
  if (msg) {
    custom_interfaces__srv__Reset_Response__fini(msg);
  }
  free(msg);
}


bool
custom_interfaces__srv__Reset_Response__Sequence__init(custom_interfaces__srv__Reset_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  custom_interfaces__srv__Reset_Response * data = NULL;
  if (size) {
    data = (custom_interfaces__srv__Reset_Response *)calloc(size, sizeof(custom_interfaces__srv__Reset_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces__srv__Reset_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces__srv__Reset_Response__fini(&data[i - 1]);
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
custom_interfaces__srv__Reset_Response__Sequence__fini(custom_interfaces__srv__Reset_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_interfaces__srv__Reset_Response__fini(&array->data[i]);
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

custom_interfaces__srv__Reset_Response__Sequence *
custom_interfaces__srv__Reset_Response__Sequence__create(size_t size)
{
  custom_interfaces__srv__Reset_Response__Sequence * array = (custom_interfaces__srv__Reset_Response__Sequence *)malloc(sizeof(custom_interfaces__srv__Reset_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces__srv__Reset_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
custom_interfaces__srv__Reset_Response__Sequence__destroy(custom_interfaces__srv__Reset_Response__Sequence * array)
{
  if (array) {
    custom_interfaces__srv__Reset_Response__Sequence__fini(array);
  }
  free(array);
}
