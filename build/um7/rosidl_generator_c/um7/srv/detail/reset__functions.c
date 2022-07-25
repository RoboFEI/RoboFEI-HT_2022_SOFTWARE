// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from um7:srv/Reset.idl
// generated code does not contain a copyright notice
#include "um7/srv/detail/reset__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool
um7__srv__Reset_Request__init(um7__srv__Reset_Request * msg)
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
um7__srv__Reset_Request__fini(um7__srv__Reset_Request * msg)
{
  if (!msg) {
    return;
  }
  // zero_gyros
  // reset_ekf
  // set_mag_ref
}

um7__srv__Reset_Request *
um7__srv__Reset_Request__create()
{
  um7__srv__Reset_Request * msg = (um7__srv__Reset_Request *)malloc(sizeof(um7__srv__Reset_Request));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(um7__srv__Reset_Request));
  bool success = um7__srv__Reset_Request__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
um7__srv__Reset_Request__destroy(um7__srv__Reset_Request * msg)
{
  if (msg) {
    um7__srv__Reset_Request__fini(msg);
  }
  free(msg);
}


bool
um7__srv__Reset_Request__Sequence__init(um7__srv__Reset_Request__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  um7__srv__Reset_Request * data = NULL;
  if (size) {
    data = (um7__srv__Reset_Request *)calloc(size, sizeof(um7__srv__Reset_Request));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = um7__srv__Reset_Request__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        um7__srv__Reset_Request__fini(&data[i - 1]);
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
um7__srv__Reset_Request__Sequence__fini(um7__srv__Reset_Request__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      um7__srv__Reset_Request__fini(&array->data[i]);
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

um7__srv__Reset_Request__Sequence *
um7__srv__Reset_Request__Sequence__create(size_t size)
{
  um7__srv__Reset_Request__Sequence * array = (um7__srv__Reset_Request__Sequence *)malloc(sizeof(um7__srv__Reset_Request__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = um7__srv__Reset_Request__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
um7__srv__Reset_Request__Sequence__destroy(um7__srv__Reset_Request__Sequence * array)
{
  if (array) {
    um7__srv__Reset_Request__Sequence__fini(array);
  }
  free(array);
}


bool
um7__srv__Reset_Response__init(um7__srv__Reset_Response * msg)
{
  if (!msg) {
    return false;
  }
  // structure_needs_at_least_one_member
  return true;
}

void
um7__srv__Reset_Response__fini(um7__srv__Reset_Response * msg)
{
  if (!msg) {
    return;
  }
  // structure_needs_at_least_one_member
}

um7__srv__Reset_Response *
um7__srv__Reset_Response__create()
{
  um7__srv__Reset_Response * msg = (um7__srv__Reset_Response *)malloc(sizeof(um7__srv__Reset_Response));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(um7__srv__Reset_Response));
  bool success = um7__srv__Reset_Response__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
um7__srv__Reset_Response__destroy(um7__srv__Reset_Response * msg)
{
  if (msg) {
    um7__srv__Reset_Response__fini(msg);
  }
  free(msg);
}


bool
um7__srv__Reset_Response__Sequence__init(um7__srv__Reset_Response__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  um7__srv__Reset_Response * data = NULL;
  if (size) {
    data = (um7__srv__Reset_Response *)calloc(size, sizeof(um7__srv__Reset_Response));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = um7__srv__Reset_Response__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        um7__srv__Reset_Response__fini(&data[i - 1]);
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
um7__srv__Reset_Response__Sequence__fini(um7__srv__Reset_Response__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      um7__srv__Reset_Response__fini(&array->data[i]);
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

um7__srv__Reset_Response__Sequence *
um7__srv__Reset_Response__Sequence__create(size_t size)
{
  um7__srv__Reset_Response__Sequence * array = (um7__srv__Reset_Response__Sequence *)malloc(sizeof(um7__srv__Reset_Response__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = um7__srv__Reset_Response__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
um7__srv__Reset_Response__Sequence__destroy(um7__srv__Reset_Response__Sequence * array)
{
  if (array) {
    um7__srv__Reset_Response__Sequence__fini(array);
  }
  free(array);
}
