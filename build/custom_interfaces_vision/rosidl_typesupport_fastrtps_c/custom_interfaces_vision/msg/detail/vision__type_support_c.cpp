// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from custom_interfaces_vision:msg/Vision.idl
// generated code does not contain a copyright notice
#include "custom_interfaces_vision/msg/detail/vision__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "custom_interfaces_vision/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "custom_interfaces_vision/msg/detail/vision__struct.h"
#include "custom_interfaces_vision/msg/detail/vision__functions.h"
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


// forward declare type support functions


using _Vision__ros_msg_type = custom_interfaces_vision__msg__Vision;

static bool _Vision__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Vision__ros_msg_type * ros_message = static_cast<const _Vision__ros_msg_type *>(untyped_ros_message);
  // Field name: ball_detected
  {
    cdr << (ros_message->ball_detected ? true : false);
  }

  // Field name: ball_left
  {
    cdr << (ros_message->ball_left ? true : false);
  }

  // Field name: ball_center_left
  {
    cdr << (ros_message->ball_center_left ? true : false);
  }

  // Field name: ball_right
  {
    cdr << (ros_message->ball_right ? true : false);
  }

  // Field name: ball_center_right
  {
    cdr << (ros_message->ball_center_right ? true : false);
  }

  // Field name: ball_far
  {
    cdr << (ros_message->ball_far ? true : false);
  }

  // Field name: ball_med
  {
    cdr << (ros_message->ball_med ? true : false);
  }

  // Field name: ball_close
  {
    cdr << (ros_message->ball_close ? true : false);
  }

  return true;
}

static bool _Vision__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Vision__ros_msg_type * ros_message = static_cast<_Vision__ros_msg_type *>(untyped_ros_message);
  // Field name: ball_detected
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_detected = tmp ? true : false;
  }

  // Field name: ball_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_left = tmp ? true : false;
  }

  // Field name: ball_center_left
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_center_left = tmp ? true : false;
  }

  // Field name: ball_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_right = tmp ? true : false;
  }

  // Field name: ball_center_right
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_center_right = tmp ? true : false;
  }

  // Field name: ball_far
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_far = tmp ? true : false;
  }

  // Field name: ball_med
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_med = tmp ? true : false;
  }

  // Field name: ball_close
  {
    uint8_t tmp;
    cdr >> tmp;
    ros_message->ball_close = tmp ? true : false;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_custom_interfaces_vision
size_t get_serialized_size_custom_interfaces_vision__msg__Vision(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Vision__ros_msg_type * ros_message = static_cast<const _Vision__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name ball_detected
  {
    size_t item_size = sizeof(ros_message->ball_detected);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ball_left
  {
    size_t item_size = sizeof(ros_message->ball_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ball_center_left
  {
    size_t item_size = sizeof(ros_message->ball_center_left);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ball_right
  {
    size_t item_size = sizeof(ros_message->ball_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ball_center_right
  {
    size_t item_size = sizeof(ros_message->ball_center_right);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ball_far
  {
    size_t item_size = sizeof(ros_message->ball_far);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ball_med
  {
    size_t item_size = sizeof(ros_message->ball_med);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ball_close
  {
    size_t item_size = sizeof(ros_message->ball_close);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Vision__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_custom_interfaces_vision__msg__Vision(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_custom_interfaces_vision
size_t max_serialized_size_custom_interfaces_vision__msg__Vision(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: ball_detected
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ball_left
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ball_center_left
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ball_right
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ball_center_right
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ball_far
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ball_med
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }
  // member: ball_close
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _Vision__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_custom_interfaces_vision__msg__Vision(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_Vision = {
  "custom_interfaces_vision::msg",
  "Vision",
  _Vision__cdr_serialize,
  _Vision__cdr_deserialize,
  _Vision__get_serialized_size,
  _Vision__max_serialized_size
};

static rosidl_message_type_support_t _Vision__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Vision,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, custom_interfaces_vision, msg, Vision)() {
  return &_Vision__type_support;
}

#if defined(__cplusplus)
}
#endif
