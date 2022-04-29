// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from messages:msg/HumanoidLeagueMsgs.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__STRUCT_HPP_
#define MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


// Include directives for member types
// Member 'header'
#include "std_msgs/msg/detail/header__struct.hpp"

#ifndef _WIN32
# define DEPRECATED__messages__msg__HumanoidLeagueMsgs __attribute__((deprecated))
#else
# define DEPRECATED__messages__msg__HumanoidLeagueMsgs __declspec(deprecated)
#endif

namespace messages
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct HumanoidLeagueMsgs_
{
  using Type = HumanoidLeagueMsgs_<ContainerAllocator>;

  explicit HumanoidLeagueMsgs_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_init)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->game_state = 0;
      this->secondary_state = 0;
      this->secondary_state_team = 0;
      this->secondary_state_mode = 0;
      this->first_half = false;
      this->own_score = 0;
      this->rival_score = 0;
      this->seconds_remaining = 0;
      this->secondary_seconds_remaining = 0;
      this->has_kick_off = false;
      this->penalized = false;
      this->seconds_till_unpenalized = 0;
      this->team_color = 0;
      this->drop_in_team = false;
      this->drop_in_time = 0;
      this->penalty_shot = 0;
      this->single_shots = 0;
      this->coach_message = "";
    }
  }

  explicit HumanoidLeagueMsgs_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  : header(_alloc, _init),
    coach_message(_alloc)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->game_state = 0;
      this->secondary_state = 0;
      this->secondary_state_team = 0;
      this->secondary_state_mode = 0;
      this->first_half = false;
      this->own_score = 0;
      this->rival_score = 0;
      this->seconds_remaining = 0;
      this->secondary_seconds_remaining = 0;
      this->has_kick_off = false;
      this->penalized = false;
      this->seconds_till_unpenalized = 0;
      this->team_color = 0;
      this->drop_in_team = false;
      this->drop_in_time = 0;
      this->penalty_shot = 0;
      this->single_shots = 0;
      this->coach_message = "";
    }
  }

  // field types and members
  using _header_type =
    std_msgs::msg::Header_<ContainerAllocator>;
  _header_type header;
  using _game_state_type =
    uint8_t;
  _game_state_type game_state;
  using _secondary_state_type =
    uint8_t;
  _secondary_state_type secondary_state;
  using _secondary_state_team_type =
    uint8_t;
  _secondary_state_team_type secondary_state_team;
  using _secondary_state_mode_type =
    uint8_t;
  _secondary_state_mode_type secondary_state_mode;
  using _first_half_type =
    bool;
  _first_half_type first_half;
  using _own_score_type =
    uint8_t;
  _own_score_type own_score;
  using _rival_score_type =
    uint8_t;
  _rival_score_type rival_score;
  using _seconds_remaining_type =
    int16_t;
  _seconds_remaining_type seconds_remaining;
  using _secondary_seconds_remaining_type =
    int16_t;
  _secondary_seconds_remaining_type secondary_seconds_remaining;
  using _has_kick_off_type =
    bool;
  _has_kick_off_type has_kick_off;
  using _penalized_type =
    bool;
  _penalized_type penalized;
  using _seconds_till_unpenalized_type =
    uint16_t;
  _seconds_till_unpenalized_type seconds_till_unpenalized;
  using _team_color_type =
    uint8_t;
  _team_color_type team_color;
  using _drop_in_team_type =
    bool;
  _drop_in_team_type drop_in_team;
  using _drop_in_time_type =
    uint16_t;
  _drop_in_time_type drop_in_time;
  using _penalty_shot_type =
    uint8_t;
  _penalty_shot_type penalty_shot;
  using _single_shots_type =
    uint16_t;
  _single_shots_type single_shots;
  using _coach_message_type =
    std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other>;
  _coach_message_type coach_message;
  using _team_mates_with_penalty_type =
    std::vector<bool, typename ContainerAllocator::template rebind<bool>::other>;
  _team_mates_with_penalty_type team_mates_with_penalty;
  using _team_mates_with_red_card_type =
    std::vector<bool, typename ContainerAllocator::template rebind<bool>::other>;
  _team_mates_with_red_card_type team_mates_with_red_card;

  // setters for named parameter idiom
  Type & set__header(
    const std_msgs::msg::Header_<ContainerAllocator> & _arg)
  {
    this->header = _arg;
    return *this;
  }
  Type & set__game_state(
    const uint8_t & _arg)
  {
    this->game_state = _arg;
    return *this;
  }
  Type & set__secondary_state(
    const uint8_t & _arg)
  {
    this->secondary_state = _arg;
    return *this;
  }
  Type & set__secondary_state_team(
    const uint8_t & _arg)
  {
    this->secondary_state_team = _arg;
    return *this;
  }
  Type & set__secondary_state_mode(
    const uint8_t & _arg)
  {
    this->secondary_state_mode = _arg;
    return *this;
  }
  Type & set__first_half(
    const bool & _arg)
  {
    this->first_half = _arg;
    return *this;
  }
  Type & set__own_score(
    const uint8_t & _arg)
  {
    this->own_score = _arg;
    return *this;
  }
  Type & set__rival_score(
    const uint8_t & _arg)
  {
    this->rival_score = _arg;
    return *this;
  }
  Type & set__seconds_remaining(
    const int16_t & _arg)
  {
    this->seconds_remaining = _arg;
    return *this;
  }
  Type & set__secondary_seconds_remaining(
    const int16_t & _arg)
  {
    this->secondary_seconds_remaining = _arg;
    return *this;
  }
  Type & set__has_kick_off(
    const bool & _arg)
  {
    this->has_kick_off = _arg;
    return *this;
  }
  Type & set__penalized(
    const bool & _arg)
  {
    this->penalized = _arg;
    return *this;
  }
  Type & set__seconds_till_unpenalized(
    const uint16_t & _arg)
  {
    this->seconds_till_unpenalized = _arg;
    return *this;
  }
  Type & set__team_color(
    const uint8_t & _arg)
  {
    this->team_color = _arg;
    return *this;
  }
  Type & set__drop_in_team(
    const bool & _arg)
  {
    this->drop_in_team = _arg;
    return *this;
  }
  Type & set__drop_in_time(
    const uint16_t & _arg)
  {
    this->drop_in_time = _arg;
    return *this;
  }
  Type & set__penalty_shot(
    const uint8_t & _arg)
  {
    this->penalty_shot = _arg;
    return *this;
  }
  Type & set__single_shots(
    const uint16_t & _arg)
  {
    this->single_shots = _arg;
    return *this;
  }
  Type & set__coach_message(
    const std::basic_string<char, std::char_traits<char>, typename ContainerAllocator::template rebind<char>::other> & _arg)
  {
    this->coach_message = _arg;
    return *this;
  }
  Type & set__team_mates_with_penalty(
    const std::vector<bool, typename ContainerAllocator::template rebind<bool>::other> & _arg)
  {
    this->team_mates_with_penalty = _arg;
    return *this;
  }
  Type & set__team_mates_with_red_card(
    const std::vector<bool, typename ContainerAllocator::template rebind<bool>::other> & _arg)
  {
    this->team_mates_with_red_card = _arg;
    return *this;
  }

  // constant declarations
  static constexpr uint8_t GAMESTATE_INITAL =
    0u;
  static constexpr uint8_t GAMESTATE_READY =
    1u;
  static constexpr uint8_t GAMESTATE_SET =
    2u;
  static constexpr uint8_t GAMESTATE_PLAYING =
    3u;
  static constexpr uint8_t GAMESTATE_FINISHED =
    4u;
  static constexpr uint8_t STATE_NORMAL =
    0u;
  static constexpr uint8_t STATE_PENALTYSHOOT =
    1u;
  static constexpr uint8_t STATE_OVERTIME =
    2u;
  static constexpr uint8_t STATE_TIMEOUT =
    3u;
  static constexpr uint8_t STATE_DIRECT_FREEKICK =
    4u;
  static constexpr uint8_t STATE_INDIRECT_FREEKICK =
    5u;
  static constexpr uint8_t STATE_PENALTYKICK =
    6u;
  static constexpr uint8_t STATE_CORNER_KICK =
    7u;
  static constexpr uint8_t STATE_GOAL_KICK =
    8u;
  static constexpr uint8_t STATE_THROW_IN =
    9u;
  static constexpr uint8_t MODE_PREPARATION =
    0u;
  static constexpr uint8_t MODE_PLACING =
    1u;
  static constexpr uint8_t MODE_END =
    2u;
  static constexpr uint8_t BLUE =
    0u;
  static constexpr uint8_t RED =
    1u;

  // pointer types
  using RawPtr =
    messages::msg::HumanoidLeagueMsgs_<ContainerAllocator> *;
  using ConstRawPtr =
    const messages::msg::HumanoidLeagueMsgs_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      messages::msg::HumanoidLeagueMsgs_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      messages::msg::HumanoidLeagueMsgs_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__messages__msg__HumanoidLeagueMsgs
    std::shared_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__messages__msg__HumanoidLeagueMsgs
    std::shared_ptr<messages::msg::HumanoidLeagueMsgs_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const HumanoidLeagueMsgs_ & other) const
  {
    if (this->header != other.header) {
      return false;
    }
    if (this->game_state != other.game_state) {
      return false;
    }
    if (this->secondary_state != other.secondary_state) {
      return false;
    }
    if (this->secondary_state_team != other.secondary_state_team) {
      return false;
    }
    if (this->secondary_state_mode != other.secondary_state_mode) {
      return false;
    }
    if (this->first_half != other.first_half) {
      return false;
    }
    if (this->own_score != other.own_score) {
      return false;
    }
    if (this->rival_score != other.rival_score) {
      return false;
    }
    if (this->seconds_remaining != other.seconds_remaining) {
      return false;
    }
    if (this->secondary_seconds_remaining != other.secondary_seconds_remaining) {
      return false;
    }
    if (this->has_kick_off != other.has_kick_off) {
      return false;
    }
    if (this->penalized != other.penalized) {
      return false;
    }
    if (this->seconds_till_unpenalized != other.seconds_till_unpenalized) {
      return false;
    }
    if (this->team_color != other.team_color) {
      return false;
    }
    if (this->drop_in_team != other.drop_in_team) {
      return false;
    }
    if (this->drop_in_time != other.drop_in_time) {
      return false;
    }
    if (this->penalty_shot != other.penalty_shot) {
      return false;
    }
    if (this->single_shots != other.single_shots) {
      return false;
    }
    if (this->coach_message != other.coach_message) {
      return false;
    }
    if (this->team_mates_with_penalty != other.team_mates_with_penalty) {
      return false;
    }
    if (this->team_mates_with_red_card != other.team_mates_with_red_card) {
      return false;
    }
    return true;
  }
  bool operator!=(const HumanoidLeagueMsgs_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct HumanoidLeagueMsgs_

// alias to use template instance with default allocator
using HumanoidLeagueMsgs =
  messages::msg::HumanoidLeagueMsgs_<std::allocator<void>>;

// constant definitions
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::GAMESTATE_INITAL;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::GAMESTATE_READY;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::GAMESTATE_SET;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::GAMESTATE_PLAYING;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::GAMESTATE_FINISHED;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_NORMAL;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_PENALTYSHOOT;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_OVERTIME;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_TIMEOUT;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_DIRECT_FREEKICK;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_INDIRECT_FREEKICK;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_PENALTYKICK;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_CORNER_KICK;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_GOAL_KICK;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::STATE_THROW_IN;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::MODE_PREPARATION;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::MODE_PLACING;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::MODE_END;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::BLUE;
template<typename ContainerAllocator>
constexpr uint8_t HumanoidLeagueMsgs_<ContainerAllocator>::RED;

}  // namespace msg

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__STRUCT_HPP_
