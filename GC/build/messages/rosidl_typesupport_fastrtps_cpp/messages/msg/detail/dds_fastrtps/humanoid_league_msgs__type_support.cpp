// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from messages:msg/HumanoidLeagueMsgs.idl
// generated code does not contain a copyright notice
#include "messages/msg/detail/humanoid_league_msgs__rosidl_typesupport_fastrtps_cpp.hpp"
#include "messages/msg/detail/humanoid_league_msgs__struct.hpp"

#include <limits>
#include <stdexcept>
#include <string>
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_fastrtps_cpp/identifier.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_fastrtps_cpp/wstring_conversion.hpp"
#include "fastcdr/Cdr.h"


// forward declaration of message dependencies and their conversion functions
namespace std_msgs
{
namespace msg
{
namespace typesupport_fastrtps_cpp
{
bool cdr_serialize(
  const std_msgs::msg::Header &,
  eprosima::fastcdr::Cdr &);
bool cdr_deserialize(
  eprosima::fastcdr::Cdr &,
  std_msgs::msg::Header &);
size_t get_serialized_size(
  const std_msgs::msg::Header &,
  size_t current_alignment);
size_t
max_serialized_size_Header(
  bool & full_bounded,
  size_t current_alignment);
}  // namespace typesupport_fastrtps_cpp
}  // namespace msg
}  // namespace std_msgs


namespace messages
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_messages
cdr_serialize(
  const messages::msg::HumanoidLeagueMsgs & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_serialize(
    ros_message.header,
    cdr);
  // Member: game_state
  cdr << ros_message.game_state;
  // Member: secondary_state
  cdr << ros_message.secondary_state;
  // Member: secondary_state_team
  cdr << ros_message.secondary_state_team;
  // Member: secondary_state_mode
  cdr << ros_message.secondary_state_mode;
  // Member: first_half
  cdr << (ros_message.first_half ? true : false);
  // Member: own_score
  cdr << ros_message.own_score;
  // Member: rival_score
  cdr << ros_message.rival_score;
  // Member: seconds_remaining
  cdr << ros_message.seconds_remaining;
  // Member: secondary_seconds_remaining
  cdr << ros_message.secondary_seconds_remaining;
  // Member: has_kick_off
  cdr << (ros_message.has_kick_off ? true : false);
  // Member: penalized
  cdr << (ros_message.penalized ? true : false);
  // Member: seconds_till_unpenalized
  cdr << ros_message.seconds_till_unpenalized;
  // Member: team_color
  cdr << ros_message.team_color;
  // Member: drop_in_team
  cdr << (ros_message.drop_in_team ? true : false);
  // Member: drop_in_time
  cdr << ros_message.drop_in_time;
  // Member: penalty_shot
  cdr << ros_message.penalty_shot;
  // Member: single_shots
  cdr << ros_message.single_shots;
  // Member: coach_message
  cdr << ros_message.coach_message;
  // Member: team_mates_with_penalty
  {
    cdr << ros_message.team_mates_with_penalty;
  }
  // Member: team_mates_with_red_card
  {
    cdr << ros_message.team_mates_with_red_card;
  }
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_messages
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  messages::msg::HumanoidLeagueMsgs & ros_message)
{
  // Member: header
  std_msgs::msg::typesupport_fastrtps_cpp::cdr_deserialize(
    cdr, ros_message.header);

  // Member: game_state
  cdr >> ros_message.game_state;

  // Member: secondary_state
  cdr >> ros_message.secondary_state;

  // Member: secondary_state_team
  cdr >> ros_message.secondary_state_team;

  // Member: secondary_state_mode
  cdr >> ros_message.secondary_state_mode;

  // Member: first_half
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.first_half = tmp ? true : false;
  }

  // Member: own_score
  cdr >> ros_message.own_score;

  // Member: rival_score
  cdr >> ros_message.rival_score;

  // Member: seconds_remaining
  cdr >> ros_message.seconds_remaining;

  // Member: secondary_seconds_remaining
  cdr >> ros_message.secondary_seconds_remaining;

  // Member: has_kick_off
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.has_kick_off = tmp ? true : false;
  }

  // Member: penalized
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.penalized = tmp ? true : false;
  }

  // Member: seconds_till_unpenalized
  cdr >> ros_message.seconds_till_unpenalized;

  // Member: team_color
  cdr >> ros_message.team_color;

  // Member: drop_in_team
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.drop_in_team = tmp ? true : false;
  }

  // Member: drop_in_time
  cdr >> ros_message.drop_in_time;

  // Member: penalty_shot
  cdr >> ros_message.penalty_shot;

  // Member: single_shots
  cdr >> ros_message.single_shots;

  // Member: coach_message
  cdr >> ros_message.coach_message;

  // Member: team_mates_with_penalty
  {
    cdr >> ros_message.team_mates_with_penalty;
  }

  // Member: team_mates_with_red_card
  {
    cdr >> ros_message.team_mates_with_red_card;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_messages
get_serialized_size(
  const messages::msg::HumanoidLeagueMsgs & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: header

  current_alignment +=
    std_msgs::msg::typesupport_fastrtps_cpp::get_serialized_size(
    ros_message.header, current_alignment);
  // Member: game_state
  {
    size_t item_size = sizeof(ros_message.game_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: secondary_state
  {
    size_t item_size = sizeof(ros_message.secondary_state);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: secondary_state_team
  {
    size_t item_size = sizeof(ros_message.secondary_state_team);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: secondary_state_mode
  {
    size_t item_size = sizeof(ros_message.secondary_state_mode);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: first_half
  {
    size_t item_size = sizeof(ros_message.first_half);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: own_score
  {
    size_t item_size = sizeof(ros_message.own_score);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: rival_score
  {
    size_t item_size = sizeof(ros_message.rival_score);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: seconds_remaining
  {
    size_t item_size = sizeof(ros_message.seconds_remaining);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: secondary_seconds_remaining
  {
    size_t item_size = sizeof(ros_message.secondary_seconds_remaining);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: has_kick_off
  {
    size_t item_size = sizeof(ros_message.has_kick_off);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: penalized
  {
    size_t item_size = sizeof(ros_message.penalized);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: seconds_till_unpenalized
  {
    size_t item_size = sizeof(ros_message.seconds_till_unpenalized);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: team_color
  {
    size_t item_size = sizeof(ros_message.team_color);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: drop_in_team
  {
    size_t item_size = sizeof(ros_message.drop_in_team);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: drop_in_time
  {
    size_t item_size = sizeof(ros_message.drop_in_time);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: penalty_shot
  {
    size_t item_size = sizeof(ros_message.penalty_shot);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: single_shots
  {
    size_t item_size = sizeof(ros_message.single_shots);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: coach_message
  current_alignment += padding +
    eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
    (ros_message.coach_message.size() + 1);
  // Member: team_mates_with_penalty
  {
    size_t array_size = ros_message.team_mates_with_penalty.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.team_mates_with_penalty[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: team_mates_with_red_card
  {
    size_t array_size = ros_message.team_mates_with_red_card.size();

    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);
    size_t item_size = sizeof(ros_message.team_mates_with_red_card[0]);
    current_alignment += array_size * item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_messages
max_serialized_size_HumanoidLeagueMsgs(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: header
  {
    size_t array_size = 1;


    for (size_t index = 0; index < array_size; ++index) {
      current_alignment +=
        std_msgs::msg::typesupport_fastrtps_cpp::max_serialized_size_Header(
        full_bounded, current_alignment);
    }
  }

  // Member: game_state
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: secondary_state
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: secondary_state_team
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: secondary_state_mode
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: first_half
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: own_score
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: rival_score
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: seconds_remaining
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: secondary_seconds_remaining
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: has_kick_off
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: penalized
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: seconds_till_unpenalized
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: team_color
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: drop_in_team
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: drop_in_time
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: penalty_shot
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: single_shots
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint16_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint16_t));
  }

  // Member: coach_message
  {
    size_t array_size = 1;

    full_bounded = false;
    for (size_t index = 0; index < array_size; ++index) {
      current_alignment += padding +
        eprosima::fastcdr::Cdr::alignment(current_alignment, padding) +
        1;
    }
  }

  // Member: team_mates_with_penalty
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: team_mates_with_red_card
  {
    size_t array_size = 0;
    full_bounded = false;
    current_alignment += padding +
      eprosima::fastcdr::Cdr::alignment(current_alignment, padding);

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static bool _HumanoidLeagueMsgs__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const messages::msg::HumanoidLeagueMsgs *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _HumanoidLeagueMsgs__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<messages::msg::HumanoidLeagueMsgs *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _HumanoidLeagueMsgs__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const messages::msg::HumanoidLeagueMsgs *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _HumanoidLeagueMsgs__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_HumanoidLeagueMsgs(full_bounded, 0);
}

static message_type_support_callbacks_t _HumanoidLeagueMsgs__callbacks = {
  "messages::msg",
  "HumanoidLeagueMsgs",
  _HumanoidLeagueMsgs__cdr_serialize,
  _HumanoidLeagueMsgs__cdr_deserialize,
  _HumanoidLeagueMsgs__get_serialized_size,
  _HumanoidLeagueMsgs__max_serialized_size
};

static rosidl_message_type_support_t _HumanoidLeagueMsgs__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_HumanoidLeagueMsgs__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace messages

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_messages
const rosidl_message_type_support_t *
get_message_type_support_handle<messages::msg::HumanoidLeagueMsgs>()
{
  return &messages::msg::typesupport_fastrtps_cpp::_HumanoidLeagueMsgs__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, messages, msg, HumanoidLeagueMsgs)() {
  return &messages::msg::typesupport_fastrtps_cpp::_HumanoidLeagueMsgs__handle;
}

#ifdef __cplusplus
}
#endif
