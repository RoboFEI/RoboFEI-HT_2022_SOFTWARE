// generated from rosidl_typesupport_fastrtps_c/resource/idl__type_support_c.cpp.em
// with input from custom_interfaces:msg/Localization.idl
// generated code does not contain a copyright notice
#include "custom_interfaces/msg/detail/localization__rosidl_typesupport_fastrtps_c.h"


#include <cassert>
#include <limits>
#include <string>
#include "rosidl_typesupport_fastrtps_c/identifier.h"
#include "rosidl_typesupport_fastrtps_c/wstring_conversion.hpp"
#include "rosidl_typesupport_fastrtps_cpp/message_type_support.h"
#include "custom_interfaces/msg/rosidl_typesupport_fastrtps_c__visibility_control.h"
#include "custom_interfaces/msg/detail/localization__struct.h"
#include "custom_interfaces/msg/detail/localization__functions.h"
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


using _Localization__ros_msg_type = custom_interfaces__msg__Localization;

static bool _Localization__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  const _Localization__ros_msg_type * ros_message = static_cast<const _Localization__ros_msg_type *>(untyped_ros_message);
  // Field name: xpos
  {
    cdr << ros_message->xpos;
  }

  // Field name: ypos
  {
    cdr << ros_message->ypos;
  }

  // Field name: theta
  {
    cdr << ros_message->theta;
  }

  // Field name: standard_deviation
  {
    cdr << ros_message->standard_deviation;
  }

  return true;
}

static bool _Localization__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  if (!untyped_ros_message) {
    fprintf(stderr, "ros message handle is null\n");
    return false;
  }
  _Localization__ros_msg_type * ros_message = static_cast<_Localization__ros_msg_type *>(untyped_ros_message);
  // Field name: xpos
  {
    cdr >> ros_message->xpos;
  }

  // Field name: ypos
  {
    cdr >> ros_message->ypos;
  }

  // Field name: theta
  {
    cdr >> ros_message->theta;
  }

  // Field name: standard_deviation
  {
    cdr >> ros_message->standard_deviation;
  }

  return true;
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_custom_interfaces
size_t get_serialized_size_custom_interfaces__msg__Localization(
  const void * untyped_ros_message,
  size_t current_alignment)
{
  const _Localization__ros_msg_type * ros_message = static_cast<const _Localization__ros_msg_type *>(untyped_ros_message);
  (void)ros_message;
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // field.name xpos
  {
    size_t item_size = sizeof(ros_message->xpos);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name ypos
  {
    size_t item_size = sizeof(ros_message->ypos);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name theta
  {
    size_t item_size = sizeof(ros_message->theta);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }
  // field.name standard_deviation
  {
    size_t item_size = sizeof(ros_message->standard_deviation);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

static uint32_t _Localization__get_serialized_size(const void * untyped_ros_message)
{
  return static_cast<uint32_t>(
    get_serialized_size_custom_interfaces__msg__Localization(
      untyped_ros_message, 0));
}

ROSIDL_TYPESUPPORT_FASTRTPS_C_PUBLIC_custom_interfaces
size_t max_serialized_size_custom_interfaces__msg__Localization(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;

  // member: xpos
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: ypos
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: theta
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }
  // member: standard_deviation
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint64_t) +
      eprosima::fastcdr::Cdr::alignment(current_alignment, sizeof(uint64_t));
  }

  return current_alignment - initial_alignment;
}

static size_t _Localization__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_custom_interfaces__msg__Localization(
    full_bounded, 0);
}


static message_type_support_callbacks_t __callbacks_Localization = {
  "custom_interfaces::msg",
  "Localization",
  _Localization__cdr_serialize,
  _Localization__cdr_deserialize,
  _Localization__get_serialized_size,
  _Localization__max_serialized_size
};

static rosidl_message_type_support_t _Localization__type_support = {
  rosidl_typesupport_fastrtps_c__identifier,
  &__callbacks_Localization,
  get_message_typesupport_handle_function,
};

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_c, custom_interfaces, msg, Localization)() {
  return &_Localization__type_support;
}

#if defined(__cplusplus)
}
#endif
