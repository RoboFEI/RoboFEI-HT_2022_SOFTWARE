// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from messages:msg/HumanoidLeagueMsgs.idl
// generated code does not contain a copyright notice
#include "messages/msg/detail/humanoid_league_msgs__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "messages/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "messages/msg/detail/humanoid_league_msgs__struct.h"
#include "messages/msg/detail/humanoid_league_msgs__functions.h"
#include "fastcdr/Cdr.h"

#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-parameter"
# ifdef __clang__
#  pragma clang diagnostic ignored "-Wdeprecated-register"
#  pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
# endif
#endif
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif

// includes and forward declarations of message dependencies and their conversion functions

#if defined(__cplusplus)
extern "C"
{
#endif

#include "rosidl_runtime_c/primitives_sequence.h"  // team_mates_with_penalty, team_mates_with_red_card
#include "rosidl_runtime_c/primitives_sequence_functions.h"  // team_mates_with_penalty, team_mates_with_red_card
#include "rosidl_runtime_c/string.h"  // coach_message
#include "rosidl_runtime_c/string_functions.h"  // coach_message
#include "std_msgs/msg/detail/header__functions.h"  // header

// forward declare type support functions
ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_messages
size_t get_serialized_size_std_msgs__msg__Header(
  const void * untyped_ros_message,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_messages
size_t max_serialized_size_std_msgs__msg__Header(
  bool & full_bounded,
  size_t current_alignment);

ROSIDL_TYPESUPPORT_FASTRTPS_C_IMPORT_messages
const rosidl_message_type_support_t *
  ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, std_msgs, msg, Header)();


using _HumanoidLeagueMsgs__ros_msg_type = messages__msg__HumanoidLeagueMsgs;

static bool _HumanoidLeagueMsgs__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _HumanoidLeagueMsgs__ros_msg_type * ros_message = static_cast<const _HumanoidLeagueMsgs__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_serialize(
        &ros_message->header, cdr))
    {
      return false;
    }
  }

  // Field name: game_state
  {
    cdr << ros_message->game_state;
  }

  // Field name: secondary_state
  {
    cdr << ros_message->secondary_state;
  }

  // Field name: secondary_state_team
  {
    cdr << ros_message->secondary_state_team;
  }

  // Field name: secondary_state_mode
  {
    cdr << ros_message->secondary_state_mode;
  }

  // Field name: first_half
  {
    cdr << (ros_message->first_half ? true : false);
  }

  // Field name: own_score
  {
    cdr << ros_message->own_score;
  }

  // Field name: rival_score
  {
    cdr << ros_message->rival_score;
  }

  // Field name: seconds_remaining
  {
    cdr << ros_message->seconds_remaining;
  }

  // Field name: secondary_seconds_remaining
  {
    cdr << ros_message->secondary_seconds_remaining;
  }

  // Field name: has_kick_off
  {
    cdr << (ros_message->has_kick_off ? true : false);
  }

  // Field name: penalized
  {
    cdr << (ros_message->penalized ? true : false);
  }

  // Field name: seconds_till_unpenalized
  {
    cdr << ros_message->seconds_till_unpenalized;
  }

  // Field name: team_color
  {
    cdr << ros_message->team_color;
  }

  // Field name: drop_in_team
  {
    cdr << (ros_message->drop_in_team ? true : false);
  }

  // Field name: drop_in_time
  {
    cdr << ros_message->drop_in_time;
  }

  // Field name: penalty_shot
  {
    cdr << ros_message->penalty_shot;
  }

  // Field name: single_shots
  {
    cdr << ros_message->single_shots;
  }

  // Field name: coach_message
  {
    const rosidl_runtime_c__String * str = &ros_message->coach_message;
    if (str->capacity == 0 || str->capacity <= str->size) {
      fprintf(stderr, "string capacity not greater than size\n");
      return false;
    }
    if (str->data[str->size] != '\0') {
      fprintf(stderr, "string not null-terminated\n");
      return false;
    }
    cdr << str->data;
  }

  // Field name: team_mates_with_penalty
  {
    size_t size = ros_message->team_mates_with_penalty.size;
    auto array_ptr = ros_message->team_mates_with_penalty.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  // Field name: team_mates_with_red_card
  {
    size_t size = ros_message->team_mates_with_red_card.size;
    auto array_ptr = ros_message->team_mates_with_red_card.data;
    cdr << static_cast<uint32_t>(size);
    cdr.serializeArray(array_ptr, size);
  }

  return true;
}

static bool _HumanoidLeagueMsgs__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _HumanoidLeagueMsgs__ros_msg_type * ros_message = static_cast<_HumanoidLeagueMsgs__ros_msg_type *>(untyped_ros_message);
  // Field name: header
  {
    const message_type_support_callbacks_t * callbacks =
      static_cast<const message_type_support_callbacks_t *>(
      ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(
        rosidl_typesupport_fastrtps_c, std_msgs, msg, Header
      )()->data);
    if (!callbacks->cdr_deserialize(
        cdr, &ros_message->header))
    {
      return false;
    }
  }

  // Field name: game_state
  {
    cdr >> ros_message->game_state;
  }

  // Field name: secondary_state
  {
    cdr >> ros_message->secondary_state;
  }

  // Field name: secondary_state_team
  {
    cdr >> ros_message->secondary_state_team;
  }

  // Field name: secondary_state_mode
  {
    cdr >> ros_message->secondary_state_mode;
  }

  // Field name: first_half
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->first_half = tmp ? true : false;
  }

  // Field name: own_score
  {
    cdr >> ros_message->own_score;
  }

  // Field name: rival_score
  {
    cdr >> ros_message->rival_score;
  }

  // Field name: seconds_remaining
  {
    cdr >> ros_message->seconds_remaining;
  }

  // Field name: secondary_seconds_remaining
  {
    cdr >> ros_message->secondary_seconds_remaining;
  }

  // Field name: has_kick_off
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->has_kick_off = tmp ? true : false;
  }

  // Field name: penalized
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->penalized = tmp ? true : false;
  }

  // Field name: seconds_till_unpenalized
  {
    cdr >> ros_message->seconds_till_unpenalized;
  }

  // Field name: team_color
  {
    cdr >> ros_message->team_color;
  }

  // Field name: drop_in_team
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->drop_in_team = tmp ? true : false;
  }

  // Field name: drop_in_time
  {
    cdr >> ros_message->drop_in_time;
  }

  // Field name: penalty_shot
  {
    cdr >> ros_message->penalty_shot;
  }

  // Field name: single_shots
  {
    cdr >> ros_message->single_shots;
  }

  // Field name: coach_message
  {
    std::string tmp;
    cdr >> tmp;
    if (!ros_message->coach_message.data) {
      rosidl_runtime_c__String__init(&ros_message->coach_message);
    }
    bool succeeded = rosidl_runtime_c__String__assign(
      &ros_message->coach_message,
      tmp.c_str());
    if (!succeeded) {
      fprintf(stderr, "failed to assign string into field 'coach_message'\n");
      return false;
    }
  }

  // Field name: team_mates_with_penalty
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->team_mates_with_penalty.data) {
      rosidl_runtime_c__boolean__Sequence__fini(&ros_message->team_mates_with_penalty);
    }
    if (!rosidl_runtime_c__boolean__Sequence__init(&ros_message->team_mates_with_penalty, size)) {
      return "failed to create array for field 'team_mates_with_penalty'";
    }
    auto array_ptr = ros_message->team_mates_with_penalty.data;
    for (size_t i = 0; i < size; ++i) {
      uint8_t tmp;
      cdr >> tmp;
      array_ptr[i] = tmp ? true : false;
    }
  }

  // Field name: team_mates_with_red_card
  {
    uint32_t cdrSize;
    cdr >> cdrSize;
    size_t size = static_cast<size_t>(cdrSize);
    if (ros_message->team_mates_with_red_card.data) {
      rosidl_runtime_c__boolean__Sequence__fini(&ros_message->team_mates_with_red_card);
    }
    if (!rosidl_runtime_c__boolean__Sequence__init(&ros_message->team_mates_with_red_card, size)) {
      return "failed to create array for field 'team_mates_with_red_card'";
    }
    auto array_ptr = ros_message->team_mates_with_red_card.data;
    for (size_t i = 0; i < size; ++i) {
      uint8_t tmp;
      cdr >> tmp;
      array_ptr[i] = tmp ? true : false;
    }
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_messages
size_t get_serialized_size_messages__msg__HumanoidLeagueMsgs(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _HumanoidLeagueMsgs__ros_msg_type * ros_message = static_cast<const _HumanoidLeagueMsgs__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name header

  current_alignment += get_serialized_size_std_msgs__msg__Header(
    &(ros_message->header), current_alignment);
  // field.name game_state
  {
    size_t item_size = sizeof(ros_message->game_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name secondary_state
  {
    size_t item_size = sizeof(ros_message->secondary_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name secondary_state_team
  {
    size_t item_size = sizeof(ros_message->secondary_state_team);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name secondary_state_mode
  {
    size_t item_size = sizeof(ros_message->secondary_state_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name first_half
  {
    size_t item_size = sizeof(ros_message->first_half);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name own_score
  {
    size_t item_size = sizeof(ros_message->own_score);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name rival_score
  {
    size_t item_size = sizeof(ros_message->rival_score);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name seconds_remaining
  {
    size_t item_size = sizeof(ros_message->seconds_remaining);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name secondary_seconds_remaining
  {
    size_t item_size = sizeof(ros_message->secondary_seconds_remaining);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name has_kick_off
  {
    size_t item_size = sizeof(ros_message->has_kick_off);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name penalized
  {
    size_t item_size = sizeof(ros_message->penalized);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name seconds_till_unpenalized
  {
    size_t item_size = sizeof(ros_message->seconds_till_unpenalized);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name team_color
  {
    size_t item_size = sizeof(ros_message->team_color);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name drop_in_team
  {
    size_t item_size = sizeof(ros_message->drop_in_team);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name drop_in_time
  {
    size_t item_size = sizeof(ros_message->drop_in_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name penalty_shot
  {
    size_t item_size = sizeof(ros_message->penalty_shot);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name single_shots
  {
    size_t item_size = sizeof(ros_message->single_shots);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name coach_message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message->coach_message.size + 1);
  // field.name team_mates_with_penalty
  {
    size_t array_size = ros_message->team_mates_with_penalty.size;
    auto array_ptr = ros_message->team_mates_with_penalty.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name team_mates_with_red_card
  {
    size_t array_size = ros_message->team_mates_with_red_card.size;
    auto array_ptr = ros_message->team_mates_with_red_card.data;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    (void)array_ptr;
    size_t item_size = sizeof(array_ptr[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _HumanoidLeagueMsgs__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_messages__msg__HumanoidLeagueMsgs(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_messages
size_t max_serialized_size_messages__msg__HumanoidLeagueMsgs(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        max_serialized_size_std_msgs__msg__Header(
        full_bounded, current_alignment);
    }
  }
  // member: game_state
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: secondary_state
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: secondary_state_team
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: secondary_state_mode
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: first_half
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: own_score
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: rival_score
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: seconds_remaining
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: secondary_seconds_remaining
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: has_kick_off
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: penalized
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: seconds_till_unpenalized
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: team_color
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: drop_in_team
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: drop_in_time
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: penalty_shot
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: single_shots
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }
  // member: coach_message
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }
  // member: team_mates_with_penalty
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: team_mates_with_red_card
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _HumanoidLeagueMsgs__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_messages__msg__HumanoidLeagueMsgs(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_HumanoidLeagueMsgs = {
  "messages::msg",
  "HumanoidLeagueMsgs",
  _HumanoidLeagueMsgs__cdr_serialize,
  _HumanoidLeagueMsgs__cdr_deserialize,
  _HumanoidLeagueMsgs__get_serialized_size,
  _HumanoidLeagueMsgs__max_serialized_size
};

static rosidl_message_type_support_t _HumanoidLeagueMsgs__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_HumanoidLeagueMsgs,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, messages, msg, HumanoidLeagueMsgs)() {
  return &_HumanoidLeagueMsgs__type_support;
}

#if defined(__cplusplus)
}
#endif
