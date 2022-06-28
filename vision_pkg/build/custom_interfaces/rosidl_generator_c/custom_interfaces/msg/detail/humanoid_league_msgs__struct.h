// generated from rosidl_generator_c/resource/idl__struct.h.em
// with input from custom_interfaces:msg/HumanoidLeagueMsgs.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__STRUCT_H_
#define CUSTOM_INTERFACES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__STRUCT_H_

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>


// Constants defined in the message

/// Constant 'GAMESTATE_INITAL'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__GAMESTATE_INITAL = 0
};

/// Constant 'GAMESTATE_READY'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__GAMESTATE_READY = 1
};

/// Constant 'GAMESTATE_SET'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__GAMESTATE_SET = 2
};

/// Constant 'GAMESTATE_PLAYING'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__GAMESTATE_PLAYING = 3
};

/// Constant 'GAMESTATE_FINISHED'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__GAMESTATE_FINISHED = 4
};

/// Constant 'STATE_NORMAL'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_NORMAL = 0
};

/// Constant 'STATE_PENALTYSHOOT'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_PENALTYSHOOT = 1
};

/// Constant 'STATE_OVERTIME'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_OVERTIME = 2
};

/// Constant 'STATE_TIMEOUT'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_TIMEOUT = 3
};

/// Constant 'STATE_DIRECT_FREEKICK'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_DIRECT_FREEKICK = 4
};

/// Constant 'STATE_INDIRECT_FREEKICK'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_INDIRECT_FREEKICK = 5
};

/// Constant 'STATE_PENALTYKICK'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_PENALTYKICK = 6
};

/// Constant 'STATE_CORNER_KICK'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_CORNER_KICK = 7
};

/// Constant 'STATE_GOAL_KICK'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_GOAL_KICK = 8
};

/// Constant 'STATE_THROW_IN'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__STATE_THROW_IN = 9
};

/// Constant 'MODE_PREPARATION'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__MODE_PREPARATION = 0
};

/// Constant 'MODE_PLACING'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__MODE_PLACING = 1
};

/// Constant 'MODE_END'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__MODE_END = 2
};

/// Constant 'BLUE'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__BLUE = 0
};

/// Constant 'RED'.
enum
{
  custom_interfaces__msg__HumanoidLeagueMsgs__RED = 1
};

// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.h"
// Member 'coach_message'
#include "rosidl_runtime_c/string.h"
// Member 'team_mates_with_penalty'
// Member 'team_mates_with_red_card'
#include "rosidl_runtime_c/primitives_sequence.h"

// Struct defined in msg/HumanoidLeagueMsgs in the package custom_interfaces.
typedef struct custom_interfaces__msg__HumanoidLeagueMsgs
{
  std_msgs__msg__Header header;
  uint8_t game_state;
  uint8_t secondary_state;
  uint8_t secondary_state_team;
  uint8_t secondary_state_mode;
  bool first_half;
  uint8_t own_score;
  uint8_t rival_score;
  int16_t seconds_remaining;
  int16_t secondary_seconds_remaining;
  bool has_kick_off;
  bool penalized;
  uint16_t seconds_till_unpenalized;
  uint8_t team_color;
  bool drop_in_team;
  uint16_t drop_in_time;
  uint8_t penalty_shot;
  uint16_t single_shots;
  rosidl_runtime_c__String coach_message;
  rosidl_runtime_c__boolean__Sequence team_mates_with_penalty;
  rosidl_runtime_c__boolean__Sequence team_mates_with_red_card;
} custom_interfaces__msg__HumanoidLeagueMsgs;

// Struct for a sequence of custom_interfaces__msg__HumanoidLeagueMsgs.
typedef struct custom_interfaces__msg__HumanoidLeagueMsgs__Sequence
{
  custom_interfaces__msg__HumanoidLeagueMsgs * data;
  /// The number of valid items in data
  size_t size;
  /// The number of allocated items in data
  size_t capacity;
} custom_interfaces__msg__HumanoidLeagueMsgs__Sequence;

#ifdef __cplusplus
}
#endif

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__STRUCT_H_
