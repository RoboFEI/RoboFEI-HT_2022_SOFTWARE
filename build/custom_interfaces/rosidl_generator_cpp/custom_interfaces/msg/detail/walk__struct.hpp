// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/Walk.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__WALK__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__WALK__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__Walk __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__Walk __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Walk_
{
  using Type = Walk_<ContainerAllocator>;

  explicit Walk_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->walk = 0;
    }
  }

  explicit Walk_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->walk = 0;
    }
  }

  // field types and members
  using _walk_type =
    uint8_t;
  _walk_type walk;

  // setters for named parameter idiom
  Type & set__walk(
    const uint8_t & _arg)
  {
    this->walk = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::Walk_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::Walk_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::Walk_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::Walk_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Walk_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Walk_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Walk_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Walk_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::Walk_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::Walk_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__Walk
    std::shared_ptr<custom_interfaces::msg::Walk_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__Walk
    std::shared_ptr<custom_interfaces::msg::Walk_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Walk_ & other) const
  {
    if (this->walk != other.walk) {
      return false;
    }
    return true;
  }
  bool operator!=(const Walk_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Walk_

// alias to use template instance with default allocator
using Walk =
  custom_interfaces::msg::Walk_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__WALK__STRUCT_HPP_
