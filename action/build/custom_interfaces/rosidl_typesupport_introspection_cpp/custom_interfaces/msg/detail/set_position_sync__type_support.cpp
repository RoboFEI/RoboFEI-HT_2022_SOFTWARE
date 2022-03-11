// generated from rosidl_typesupport_introspection_cpp/resource/idl__type_support.cpp.em
// with input from custom_interfaces:msg/SetPositionSync.idl
// generated code does not contain a copyright notice

#include "array"
#include "cstddef"
#include "string"
#include "vector"
#include "rosidl_runtime_c/message_type_support_struct.h"
#include "rosidl_typesupport_cpp/message_type_support.hpp"
#include "rosidl_typesupport_interface/macros.h"
#include "custom_interfaces/msg/detail/set_position_sync__struct.hpp"
#include "rosidl_typesupport_introspection_cpp/field_types.hpp"
#include "rosidl_typesupport_introspection_cpp/identifier.hpp"
#include "rosidl_typesupport_introspection_cpp/message_introspection.hpp"
#include "rosidl_typesupport_introspection_cpp/message_type_support_decl.hpp"
#include "rosidl_typesupport_introspection_cpp/visibility_control.h"

namespace custom_interfaces
{

namespace msg
{

namespace rosidl_typesupport_introspection_cpp
{

void SetPositionSync_init_function(
  void * message_memory, rosidl_runtime_cpp::MessageInitialization _init)
{
  new (message_memory) custom_interfaces::msg::SetPositionSync(_init);
}

void SetPositionSync_fini_function(void * message_memory)
{
  auto typed_message = static_cast<custom_interfaces::msg::SetPositionSync *>(message_memory);
  typed_message->~SetPositionSync();
}

size_t size_function__SetPositionSync__id(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<uint8_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SetPositionSync__id(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<uint8_t> *>(untyped_member);
  return &member[index];
}

void * get_function__SetPositionSync__id(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<uint8_t> *>(untyped_member);
  return &member[index];
}

void resize_function__SetPositionSync__id(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<uint8_t> *>(untyped_member);
  member->resize(size);
}

size_t size_function__SetPositionSync__position(const void * untyped_member)
{
  const auto * member = reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return member->size();
}

const void * get_const_function__SetPositionSync__position(const void * untyped_member, size_t index)
{
  const auto & member =
    *reinterpret_cast<const std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void * get_function__SetPositionSync__position(void * untyped_member, size_t index)
{
  auto & member =
    *reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  return &member[index];
}

void resize_function__SetPositionSync__position(void * untyped_member, size_t size)
{
  auto * member =
    reinterpret_cast<std::vector<int32_t> *>(untyped_member);
  member->resize(size);
}

static const ::rosidl_typesupport_introspection_cpp::MessageMember SetPositionSync_message_member_array[2] = {
  {
    "id",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_UINT8,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(custom_interfaces::msg::SetPositionSync, id),  // bytes offset in struct
    nullptr,  // default value
    size_function__SetPositionSync__id,  // size() function pointer
    get_const_function__SetPositionSync__id,  // get_const(index) function pointer
    get_function__SetPositionSync__id,  // get(index) function pointer
    resize_function__SetPositionSync__id  // resize(index) function pointer
  },
  {
    "position",  // name
    ::rosidl_typesupport_introspection_cpp::ROS_TYPE_INT32,  // type
    0,  // upper bound of string
    nullptr,  // members of sub message
    true,  // is array
    0,  // array size
    false,  // is upper bound
    offsetof(custom_interfaces::msg::SetPositionSync, position),  // bytes offset in struct
    nullptr,  // default value
    size_function__SetPositionSync__position,  // size() function pointer
    get_const_function__SetPositionSync__position,  // get_const(index) function pointer
    get_function__SetPositionSync__position,  // get(index) function pointer
    resize_function__SetPositionSync__position  // resize(index) function pointer
  }
};

static const ::rosidl_typesupport_introspection_cpp::MessageMembers SetPositionSync_message_members = {
  "custom_interfaces::msg",  // message namespace
  "SetPositionSync",  // message name
  2,  // number of fields
  sizeof(custom_interfaces::msg::SetPositionSync),
  SetPositionSync_message_member_array,  // message members
  SetPositionSync_init_function,  // function to initialize message memory (memory has to be allocated)
  SetPositionSync_fini_function  // function to terminate message instance (will not free memory)
};

static const rosidl_message_type_support_t SetPositionSync_message_type_support_handle = {
  ::rosidl_typesupport_introspection_cpp::typesupport_identifier,
  &SetPositionSync_message_members,
  get_message_typesupport_handle_function,
};

}  // namespace rosidl_typesupport_introspection_cpp

}  // namespace msg

}  // namespace custom_interfaces


namespace rosidl_typesupport_introspection_cpp
{

template<>
ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
get_message_type_support_handle<custom_interfaces::msg::SetPositionSync>()
{
  return &::custom_interfaces::msg::rosidl_typesupport_introspection_cpp::SetPositionSync_message_type_support_handle;
}

}  // namespace rosidl_typesupport_introspection_cpp

#ifdef __cplusplus
extern "C"
{
#endif

ROSIDL_TYPESUPPORT_INTROSPECTION_CPP_PUBLIC
const rosidl_message_type_support_t *
ROSIDL_TYPESUPPORT_INTERFACE__MESSAGE_SYMBOL_NAME(rosidl_typesupport_introspection_cpp, custom_interfaces, msg, SetPositionSync)() {
  return &::custom_interfaces::msg::rosidl_typesupport_introspection_cpp::SetPositionSync_message_type_support_handle;
}

#ifdef __cplusplus
}
#endif
