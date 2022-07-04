// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from custom_interfaces_vision:msg/Vision.idl
// generated code does not contain a copyright notice
#include "custom_interfaces_vision/msg/detail/vision__rosidl_typesupport_fastrtps_cpp.hpp"
#include "custom_interfaces_vision/msg/detail/vision__struct.hpp"

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

namespace custom_interfaces_vision
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_custom_interfaces_vision
cdr_serialize(
  const custom_interfaces_vision::msg::Vision & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: ball_detected
  cdr << (ros_message.ball_detected ? true : false);
  // Member: ball_left
  cdr << (ros_message.ball_left ? true : false);
  // Member: ball_center_left
  cdr << (ros_message.ball_center_left ? true : false);
  // Member: ball_right
  cdr << (ros_message.ball_right ? true : false);
  // Member: ball_center_right
  cdr << (ros_message.ball_center_right ? true : false);
  // Member: ball_far
  cdr << (ros_message.ball_far ? true : false);
  // Member: ball_med
  cdr << (ros_message.ball_med ? true : false);
  // Member: ball_close
  cdr << (ros_message.ball_close ? true : false);
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_custom_interfaces_vision
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  custom_interfaces_vision::msg::Vision & ros_message)
{
  // Member: ball_detected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_detected = tmp ? true : false;
  }

  // Member: ball_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_left = tmp ? true : false;
  }

  // Member: ball_center_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_center_left = tmp ? true : false;
  }

  // Member: ball_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_right = tmp ? true : false;
  }

  // Member: ball_center_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_center_right = tmp ? true : false;
  }

  // Member: ball_far
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_far = tmp ? true : false;
  }

  // Member: ball_med
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_med = tmp ? true : false;
  }

  // Member: ball_close
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message.ball_close = tmp ? true : false;
  }

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_custom_interfaces_vision
get_serialized_size(
  const custom_interfaces_vision::msg::Vision & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: ball_detected
  {
    size_t item_size = sizeof(ros_message.ball_detected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ball_left
  {
    size_t item_size = sizeof(ros_message.ball_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ball_center_left
  {
    size_t item_size = sizeof(ros_message.ball_center_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ball_right
  {
    size_t item_size = sizeof(ros_message.ball_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ball_center_right
  {
    size_t item_size = sizeof(ros_message.ball_center_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ball_far
  {
    size_t item_size = sizeof(ros_message.ball_far);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ball_med
  {
    size_t item_size = sizeof(ros_message.ball_med);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // Member: ball_close
  {
    size_t item_size = sizeof(ros_message.ball_close);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_custom_interfaces_vision
max_serialized_size_Vision(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: ball_detected
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ball_left
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ball_center_left
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ball_right
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ball_center_right
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ball_far
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ball_med
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  // Member: ball_close
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static bool _Vision__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const custom_interfaces_vision::msg::Vision *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Vision__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<custom_interfaces_vision::msg::Vision *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Vision__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const custom_interfaces_vision::msg::Vision *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Vision__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_Vision(full_bounded, 0);
}

static message_type_support_callbacks_t _Vision__callbacks = {
  "custom_interfaces_vision::msg",
  "Vision",
  _Vision__cdr_serialize,
  _Vision__cdr_deserialize,
  _Vision__get_serialized_size,
  _Vision__max_serialized_size
};

static rosidl_message_type_support_t _Vision__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Vision__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace custom_interfaces_vision

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_custom_interfaces_vision
const rosidl_message_type_support_t *
get_message_type_support_handle<custom_interfaces_vision::msg::Vision>()
{
  return &custom_interfaces_vision::msg::typesupport_fastrtps_cpp::_Vision__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, custom_interfaces_vision, msg, Vision)() {
  return &custom_interfaces_vision::msg::typesupport_fastrtps_cpp::_Vision__handle;
}

#ifdef __cplusplus
}
#endif
