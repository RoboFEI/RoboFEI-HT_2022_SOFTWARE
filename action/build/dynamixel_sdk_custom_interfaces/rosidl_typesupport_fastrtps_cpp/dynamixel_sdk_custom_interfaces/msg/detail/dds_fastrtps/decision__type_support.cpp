// generated from rosidl_typesupport_fastrtps_cpp/resource/idl__type_support.cpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/Decision.idl
// generated code does not contain a copyright notice
#include "dynamixel_sdk_custom_interfaces/msg/detail/decision__rosidl_typesupport_fastrtps_cpp.hpp"
#include "dynamixel_sdk_custom_interfaces/msg/detail/decision__struct.hpp"

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

namespace dynamixel_sdk_custom_interfaces
{

namespace msg
{

namespace typesupport_fastrtps_cpp
{

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamixel_sdk_custom_interfaces
cdr_serialize(
  const dynamixel_sdk_custom_interfaces::msg::Decision & ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  // Member: decision
  cdr << ros_message.decision;
  return true;
}

bool
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamixel_sdk_custom_interfaces
cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  dynamixel_sdk_custom_interfaces::msg::Decision & ros_message)
{
  // Member: decision
  cdr >> ros_message.decision;

  return true;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamixel_sdk_custom_interfaces
get_serialized_size(
  const dynamixel_sdk_custom_interfaces::msg::Decision & ros_message,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;

  // Member: decision
  {
    size_t item_size = sizeof(ros_message.decision);
    current_alignment += item_size +
      eprosima::fastcdr::Cdr::alignment(current_alignment, item_size);
  }

  return current_alignment - initial_alignment;
}

size_t
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_PUBLIC_dynamixel_sdk_custom_interfaces
max_serialized_size_Decision(
  bool & full_bounded,
  size_t current_alignment)
{
  size_t initial_alignment = current_alignment;

  const size_t padding = 4;
  const size_t wchar_size = 4;
  (void)padding;
  (void)wchar_size;
  (void)full_bounded;


  // Member: decision
  {
    size_t array_size = 1;

    current_alignment += array_size * sizeof(uint8_t);
  }

  return current_alignment - initial_alignment;
}

static bool _Decision__cdr_serialize(
  const void * untyped_ros_message,
  eprosima::fastcdr::Cdr & cdr)
{
  auto typed_message =
    static_cast<const dynamixel_sdk_custom_interfaces::msg::Decision *>(
    untyped_ros_message);
  return cdr_serialize(*typed_message, cdr);
}

static bool _Decision__cdr_deserialize(
  eprosima::fastcdr::Cdr & cdr,
  void * untyped_ros_message)
{
  auto typed_message =
    static_cast<dynamixel_sdk_custom_interfaces::msg::Decision *>(
    untyped_ros_message);
  return cdr_deserialize(cdr, *typed_message);
}

static uint32_t _Decision__get_serialized_size(
  const void * untyped_ros_message)
{
  auto typed_message =
    static_cast<const dynamixel_sdk_custom_interfaces::msg::Decision *>(
    untyped_ros_message);
  return static_cast<uint32_t>(get_serialized_size(*typed_message, 0));
}

static size_t _Decision__max_serialized_size(bool & full_bounded)
{
  return max_serialized_size_Decision(full_bounded, 0);
}

static message_type_support_callbacks_t _Decision__callbacks = {
  "dynamixel_sdk_custom_interfaces::msg",
  "Decision",
  _Decision__cdr_serialize,
  _Decision__cdr_deserialize,
  _Decision__get_serialized_size,
  _Decision__max_serialized_size
};

static rosidl_message_type_support_t _Decision__handle = {
  rosidl_typesupport_fastrtps_cpp::typesupport_identifier,
  &_Decision__callbacks,
  get_message_typesupport_handle_function,
};

}  // namespace typesupport_fastrtps_cpp

}  // namespace msg

}  // namespace dynamixel_sdk_custom_interfaces

namespace rosidl_typesupport_fastrtps_cpp
{

template<>
ROSIDL_TYPESUPPORT_FASTRTPS_CPP_EXPORT_dynamixel_sdk_custom_interfaces
const rosidl_message_type_support_t *
get_message_type_support_handle<dynamixel_sdk_custom_interfaces::msg::Decision>()
{
  return &dynamixel_sdk_custom_interfaces::msg::typesupport_fastrtps_cpp::_Decision__handle;
}

}  // namespace rosidl_typesupport_fastrtps_cpp

#ifdef __cplusplus
extern "C"
{
#endif

const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_fastrtps_cpp, dynamixel_sdk_custom_interfaces, msg, Decision)() {
  return &dynamixel_sdk_custom_interfaces::msg::typesupport_fastrtps_cpp::_Decision__handle;
}

#ifdef __cplusplus
}
#endif
