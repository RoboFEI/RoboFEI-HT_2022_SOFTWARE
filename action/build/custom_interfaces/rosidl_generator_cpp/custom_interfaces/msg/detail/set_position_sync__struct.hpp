// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/SetPositionSync.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__SetPositionSync __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__SetPositionSync __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SetPositionSync_
{
  using Type = SetPositionSync_<ContainerAllocator>;

  explicit SetPositionSync_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
  }

  explicit SetPositionSync_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_init;
    (void)_alloc;
  }

  // field types and members
  using _id_type =
    std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other>;
  _id_type id;
  using _position_type =
    std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other>;
  _position_type position;

  // setters for named parameter idiom
  Type & set__id(
    const std::vector<uint8_t, typename ContainerAllocator::template rebind<uint8_t>::other> & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__position(
    const std::vector<int32_t, typename ContainerAllocator::template rebind<int32_t>::other> & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::SetPositionSync_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::SetPositionSync_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::SetPositionSync_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::SetPositionSync_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__SetPositionSync
    std::shared_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__SetPositionSync
    std::shared_ptr<custom_interfaces::msg::SetPositionSync_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetPositionSync_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetPositionSync_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetPositionSync_

// alias to use template instance with default allocator
using SetPositionSync =
  custom_interfaces::msg::SetPositionSync_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_SYNC__STRUCT_HPP_
