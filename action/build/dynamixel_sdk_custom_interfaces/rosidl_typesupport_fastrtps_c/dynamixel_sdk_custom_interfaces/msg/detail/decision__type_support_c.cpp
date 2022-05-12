// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/Decision.idl
// generated code does not contain a copyright notice
#include "dynamixel_sdk_custom_interfaces/msg/detail/decision__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "dynamixel_sdk_custom_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "dynamixel_sdk_custom_interfaces/msg/detail/decision__struct.h"
#include "dynamixel_sdk_custom_interfaces/msg/detail/decision__functions.h"
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


using _Decision__ros_msg_type = dynamixel_sdk_custom_interfaces__msg__Decision;

static bool _Decision__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Decision__ros_msg_type * ros_message = static_cast<const _Decision__ros_msg_type *>(untyped_ros_message);
  // Field name: decision
  {
    cdr << ros_message->decision;
  }

  return true;
}

static bool _Decision__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Decision__ros_msg_type * ros_message = static_cast<_Decision__ros_msg_type *>(untyped_ros_message);
  // Field name: decision
  {
    cdr >> ros_message->decision;
  }

  return true;
}  // NOLINT(readability/fn_size)

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_dynamixel_sdk_custom_interfaces
size_t get_serialized_size_dynamixel_sdk_custom_interfaces__msg__Decision(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Decision__ros_msg_type * ros_message = static_cast<const _Decision__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name decision
  {
    size_t item_size = sizeof(ros_message->decision);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Decision__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_dynamixel_sdk_custom_interfaces__msg__Decision(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_dynamixel_sdk_custom_interfaces
size_t max_serialized_size_dynamixel_sdk_custom_interfaces__msg__Decision(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: decision
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static size_t _Decision__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_dynamixel_sdk_custom_interfaces__msg__Decision(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_Decision = {
  "dynamixel_sdk_custom_interfaces::msg",
  "Decision",
  _Decision__cdr_serialize,
  _Decision__cdr_deserialize,
  _Decision__get_serialized_size,
  _Decision__max_serialized_size
};

static rosidl_message_type_support_t _Decision__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Decision,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, dynamixel_sdk_custom_interfaces, msg, Decision)() {
  return &_Decision__type_support;
}

#if defined(__cplusplus)
}
#endif
