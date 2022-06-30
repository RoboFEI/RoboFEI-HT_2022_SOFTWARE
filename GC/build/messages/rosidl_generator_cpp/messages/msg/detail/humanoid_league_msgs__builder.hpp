// generated from rosidl_generator_cpp/resource/idl__builder.hpp.em
// with input from messages:msg/HumanoidLeagueMsgs.idl
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__BUILDER_HPP_
#define MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__BUILDER_HPP_

#include "messages/msg/detail/humanoid_league_msgs__struct.hpp"
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <utility>


namespace messages
{

namespace msg
{

namespace builder
{

class Init_HumanoidLeagueMsgs_team_mates_with_red_card
{
public:
  explicit Init_HumanoidLeagueMsgs_team_mates_with_red_card(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  ::messages::msg::HumanoidLeagueMsgs team_mates_with_red_card(::messages::msg::HumanoidLeagueMsgs::_team_mates_with_red_card_type arg)
  {
    msg_.team_mates_with_red_card = std::move(arg);
    return std::move(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_team_mates_with_penalty
{
public:
  explicit Init_HumanoidLeagueMsgs_team_mates_with_penalty(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_team_mates_with_red_card team_mates_with_penalty(::messages::msg::HumanoidLeagueMsgs::_team_mates_with_penalty_type arg)
  {
    msg_.team_mates_with_penalty = std::move(arg);
    return Init_HumanoidLeagueMsgs_team_mates_with_red_card(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_coach_message
{
public:
  explicit Init_HumanoidLeagueMsgs_coach_message(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_team_mates_with_penalty coach_message(::messages::msg::HumanoidLeagueMsgs::_coach_message_type arg)
  {
    msg_.coach_message = std::move(arg);
    return Init_HumanoidLeagueMsgs_team_mates_with_penalty(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_single_shots
{
public:
  explicit Init_HumanoidLeagueMsgs_single_shots(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_coach_message single_shots(::messages::msg::HumanoidLeagueMsgs::_single_shots_type arg)
  {
    msg_.single_shots = std::move(arg);
    return Init_HumanoidLeagueMsgs_coach_message(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_penalty_shot
{
public:
  explicit Init_HumanoidLeagueMsgs_penalty_shot(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_single_shots penalty_shot(::messages::msg::HumanoidLeagueMsgs::_penalty_shot_type arg)
  {
    msg_.penalty_shot = std::move(arg);
    return Init_HumanoidLeagueMsgs_single_shots(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_drop_in_time
{
public:
  explicit Init_HumanoidLeagueMsgs_drop_in_time(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_penalty_shot drop_in_time(::messages::msg::HumanoidLeagueMsgs::_drop_in_time_type arg)
  {
    msg_.drop_in_time = std::move(arg);
    return Init_HumanoidLeagueMsgs_penalty_shot(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_drop_in_team
{
public:
  explicit Init_HumanoidLeagueMsgs_drop_in_team(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_drop_in_time drop_in_team(::messages::msg::HumanoidLeagueMsgs::_drop_in_team_type arg)
  {
    msg_.drop_in_team = std::move(arg);
    return Init_HumanoidLeagueMsgs_drop_in_time(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_team_color
{
public:
  explicit Init_HumanoidLeagueMsgs_team_color(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_drop_in_team team_color(::messages::msg::HumanoidLeagueMsgs::_team_color_type arg)
  {
    msg_.team_color = std::move(arg);
    return Init_HumanoidLeagueMsgs_drop_in_team(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_seconds_till_unpenalized
{
public:
  explicit Init_HumanoidLeagueMsgs_seconds_till_unpenalized(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_team_color seconds_till_unpenalized(::messages::msg::HumanoidLeagueMsgs::_seconds_till_unpenalized_type arg)
  {
    msg_.seconds_till_unpenalized = std::move(arg);
    return Init_HumanoidLeagueMsgs_team_color(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_penalized
{
public:
  explicit Init_HumanoidLeagueMsgs_penalized(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_seconds_till_unpenalized penalized(::messages::msg::HumanoidLeagueMsgs::_penalized_type arg)
  {
    msg_.penalized = std::move(arg);
    return Init_HumanoidLeagueMsgs_seconds_till_unpenalized(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_has_kick_off
{
public:
  explicit Init_HumanoidLeagueMsgs_has_kick_off(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_penalized has_kick_off(::messages::msg::HumanoidLeagueMsgs::_has_kick_off_type arg)
  {
    msg_.has_kick_off = std::move(arg);
    return Init_HumanoidLeagueMsgs_penalized(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_secondary_seconds_remaining
{
public:
  explicit Init_HumanoidLeagueMsgs_secondary_seconds_remaining(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_has_kick_off secondary_seconds_remaining(::messages::msg::HumanoidLeagueMsgs::_secondary_seconds_remaining_type arg)
  {
    msg_.secondary_seconds_remaining = std::move(arg);
    return Init_HumanoidLeagueMsgs_has_kick_off(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_seconds_remaining
{
public:
  explicit Init_HumanoidLeagueMsgs_seconds_remaining(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_secondary_seconds_remaining seconds_remaining(::messages::msg::HumanoidLeagueMsgs::_seconds_remaining_type arg)
  {
    msg_.seconds_remaining = std::move(arg);
    return Init_HumanoidLeagueMsgs_secondary_seconds_remaining(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_rival_score
{
public:
  explicit Init_HumanoidLeagueMsgs_rival_score(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_seconds_remaining rival_score(::messages::msg::HumanoidLeagueMsgs::_rival_score_type arg)
  {
    msg_.rival_score = std::move(arg);
    return Init_HumanoidLeagueMsgs_seconds_remaining(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_own_score
{
public:
  explicit Init_HumanoidLeagueMsgs_own_score(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_rival_score own_score(::messages::msg::HumanoidLeagueMsgs::_own_score_type arg)
  {
    msg_.own_score = std::move(arg);
    return Init_HumanoidLeagueMsgs_rival_score(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_first_half
{
public:
  explicit Init_HumanoidLeagueMsgs_first_half(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_own_score first_half(::messages::msg::HumanoidLeagueMsgs::_first_half_type arg)
  {
    msg_.first_half = std::move(arg);
    return Init_HumanoidLeagueMsgs_own_score(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_secondary_state_mode
{
public:
  explicit Init_HumanoidLeagueMsgs_secondary_state_mode(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_first_half secondary_state_mode(::messages::msg::HumanoidLeagueMsgs::_secondary_state_mode_type arg)
  {
    msg_.secondary_state_mode = std::move(arg);
    return Init_HumanoidLeagueMsgs_first_half(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_secondary_state_team
{
public:
  explicit Init_HumanoidLeagueMsgs_secondary_state_team(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_secondary_state_mode secondary_state_team(::messages::msg::HumanoidLeagueMsgs::_secondary_state_team_type arg)
  {
    msg_.secondary_state_team = std::move(arg);
    return Init_HumanoidLeagueMsgs_secondary_state_mode(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_secondary_state
{
public:
  explicit Init_HumanoidLeagueMsgs_secondary_state(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_secondary_state_team secondary_state(::messages::msg::HumanoidLeagueMsgs::_secondary_state_type arg)
  {
    msg_.secondary_state = std::move(arg);
    return Init_HumanoidLeagueMsgs_secondary_state_team(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_game_state
{
public:
  explicit Init_HumanoidLeagueMsgs_game_state(::messages::msg::HumanoidLeagueMsgs & msg)
  : msg_(msg)
  {}
  Init_HumanoidLeagueMsgs_secondary_state game_state(::messages::msg::HumanoidLeagueMsgs::_game_state_type arg)
  {
    msg_.game_state = std::move(arg);
    return Init_HumanoidLeagueMsgs_secondary_state(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

class Init_HumanoidLeagueMsgs_header
{
public:
  Init_HumanoidLeagueMsgs_header()
  : msg_(::rosidl_runtime_cpp::MessageInitialization::SKIP)
  {}
  Init_HumanoidLeagueMsgs_game_state header(::messages::msg::HumanoidLeagueMsgs::_header_type arg)
  {
    msg_.header = std::move(arg);
    return Init_HumanoidLeagueMsgs_game_state(msg_);
  }

private:
  ::messages::msg::HumanoidLeagueMsgs msg_;
};

}  // namespace builder

}  // namespace msg

template<typename MessageType>
auto build();

template<>
inline
auto build<::messages::msg::HumanoidLeagueMsgs>()
{
  return messages::msg::builder::Init_HumanoidLeagueMsgs_header();
}

}  // namespace messages

#endif  // MESSAGES__MSG__DETAIL__HUMANOID_LEAGUE_MSGS__BUILDER_HPP_
