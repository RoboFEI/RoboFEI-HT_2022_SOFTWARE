// generated from rosidl_generator_c/resource/idl__functions.c.em
// with input from custom_interfaces:msg/HumanoidLeagueMsgs.idl
// generated code does not contain a copyright notice
#include "custom_interfaces/msg/detail/humanoid_league_msgs__functions.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


// Include directives for member types
// Member `header`
#include "std_msgs/msg/detail/header__functions.h"
// Member `coach_message`
#include "rosidl_runtime_c/string_functions.h"
// Member `team_mates_with_penalty`
// Member `team_mates_with_red_card`
#include "rosidl_runtime_c/primitives_sequence_functions.h"

bool
custom_interfaces__msg__HumanoidLeagueMsgs__init(custom_interfaces__msg__HumanoidLeagueMsgs * msg)
{
  if (!msg) {
    return false;
  }
  // header
  if (!std_msgs__msg__Header__init(&msg->header)) {
    custom_interfaces__msg__HumanoidLeagueMsgs__fini(msg);
    return false;
  }
  // game_state
  // secondary_state
  // secondary_state_team
  // secondary_state_mode
  // first_half
  // own_score
  // rival_score
  // seconds_remaining
  // secondary_seconds_remaining
  // has_kick_off
  // penalized
  // seconds_till_unpenalized
  // team_color
  // drop_in_team
  // drop_in_time
  // penalty_shot
  // single_shots
  // coach_message
  if (!rosidl_runtime_c__String__init(&msg->coach_message)) {
    custom_interfaces__msg__HumanoidLeagueMsgs__fini(msg);
    return false;
  }
  // team_mates_with_penalty
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->team_mates_with_penalty, 0)) {
    custom_interfaces__msg__HumanoidLeagueMsgs__fini(msg);
    return false;
  }
  // team_mates_with_red_card
  if (!rosidl_runtime_c__boolean__Sequence__init(&msg->team_mates_with_red_card, 0)) {
    custom_interfaces__msg__HumanoidLeagueMsgs__fini(msg);
    return false;
  }
  return true;
}

void
custom_interfaces__msg__HumanoidLeagueMsgs__fini(custom_interfaces__msg__HumanoidLeagueMsgs * msg)
{
  if (!msg) {
    return;
  }
  // header
  std_msgs__msg__Header__fini(&msg->header);
  // game_state
  // secondary_state
  // secondary_state_team
  // secondary_state_mode
  // first_half
  // own_score
  // rival_score
  // seconds_remaining
  // secondary_seconds_remaining
  // has_kick_off
  // penalized
  // seconds_till_unpenalized
  // team_color
  // drop_in_team
  // drop_in_time
  // penalty_shot
  // single_shots
  // coach_message
  rosidl_runtime_c__String__fini(&msg->coach_message);
  // team_mates_with_penalty
  rosidl_runtime_c__boolean__Sequence__fini(&msg->team_mates_with_penalty);
  // team_mates_with_red_card
  rosidl_runtime_c__boolean__Sequence__fini(&msg->team_mates_with_red_card);
}

custom_interfaces__msg__HumanoidLeagueMsgs *
custom_interfaces__msg__HumanoidLeagueMsgs__create()
{
  custom_interfaces__msg__HumanoidLeagueMsgs * msg = (custom_interfaces__msg__HumanoidLeagueMsgs *)malloc(sizeof(custom_interfaces__msg__HumanoidLeagueMsgs));
  if (!msg) {
    return NULL;
  }
  memset(msg, 0, sizeof(custom_interfaces__msg__HumanoidLeagueMsgs));
  bool success = custom_interfaces__msg__HumanoidLeagueMsgs__init(msg);
  if (!success) {
    free(msg);
    return NULL;
  }
  return msg;
}

void
custom_interfaces__msg__HumanoidLeagueMsgs__destroy(custom_interfaces__msg__HumanoidLeagueMsgs * msg)
{
  if (msg) {
    custom_interfaces__msg__HumanoidLeagueMsgs__fini(msg);
  }
  free(msg);
}


bool
custom_interfaces__msg__HumanoidLeagueMsgs__Sequence__init(custom_interfaces__msg__HumanoidLeagueMsgs__Sequence * array, size_t size)
{
  if (!array) {
    return false;
  }
  custom_interfaces__msg__HumanoidLeagueMsgs * data = NULL;
  if (size) {
    data = (custom_interfaces__msg__HumanoidLeagueMsgs *)calloc(size, sizeof(custom_interfaces__msg__HumanoidLeagueMsgs));
    if (!data) {
      return false;
    }
    // initialize all array elements
    size_t i;
    for (i = 0; i < size; ++i) {
      bool success = custom_interfaces__msg__HumanoidLeagueMsgs__init(&data[i]);
      if (!success) {
        break;
      }
    }
    if (i < size) {
      // if initialization failed finalize the already initialized array elements
      for (; i > 0; --i) {
        custom_interfaces__msg__HumanoidLeagueMsgs__fini(&data[i - 1]);
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
custom_interfaces__msg__HumanoidLeagueMsgs__Sequence__fini(custom_interfaces__msg__HumanoidLeagueMsgs__Sequence * array)
{
  if (!array) {
    return;
  }
  if (array->data) {
    // ensure that data and capacity values are consistent
    assert(array->capacity > 0);
    // finalize all array elements
    for (size_t i = 0; i < array->capacity; ++i) {
      custom_interfaces__msg__HumanoidLeagueMsgs__fini(&array->data[i]);
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

custom_interfaces__msg__HumanoidLeagueMsgs__Sequence *
custom_interfaces__msg__HumanoidLeagueMsgs__Sequence__create(size_t size)
{
  custom_interfaces__msg__HumanoidLeagueMsgs__Sequence * array = (custom_interfaces__msg__HumanoidLeagueMsgs__Sequence *)malloc(sizeof(custom_interfaces__msg__HumanoidLeagueMsgs__Sequence));
  if (!array) {
    return NULL;
  }
  bool success = custom_interfaces__msg__HumanoidLeagueMsgs__Sequence__init(array, size);
  if (!success) {
    free(array);
    return NULL;
  }
  return array;
}

void
custom_interfaces__msg__HumanoidLeagueMsgs__Sequence__destroy(custom_interfaces__msg__HumanoidLeagueMsgs__Sequence * array)
{
  if (array) {
    custom_interfaces__msg__HumanoidLeagueMsgs__Sequence__fini(array);
  }
  free(array);
}
