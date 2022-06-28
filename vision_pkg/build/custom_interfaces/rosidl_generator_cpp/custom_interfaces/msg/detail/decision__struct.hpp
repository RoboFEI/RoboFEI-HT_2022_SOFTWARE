// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/Decision.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__DECISION__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__DECISION__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__Decision __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__Decision __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Decision_
{
  using Type = Decision_<ContainerAllocator>;

  explicit Decision_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->decision = 0;
    }
  }

  explicit Decision_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->decision = 0;
    }
  }

  // field types and members
  using _decision_type =
    uint8_t;
  _decision_type decision;

  // setters for named parameter idiom
  Type & set__decision(
    const uint8_t & _arg)
  {
    this->decision = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::Decision_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::Decision_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::Decision_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::Decision_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Decision_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Decision_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Decision_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Decision_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::Decision_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::Decision_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__Decision
    std::shared_ptr<custom_interfaces::msg::Decision_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__Decision
    std::shared_ptr<custom_interfaces::msg::Decision_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Decision_ & other) const
  {
    if (this->decision != other.decision) {
      return false;
    }
    return true;
  }
  bool operator!=(const Decision_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Decision_

// alias to use template instance with default allocator
using Decision =
  custom_interfaces::msg::Decision_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__DECISION__STRUCT_HPP_
