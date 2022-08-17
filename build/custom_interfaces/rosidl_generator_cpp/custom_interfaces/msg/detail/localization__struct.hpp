// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/Localization.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__Localization __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__Localization __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Localization_
{
  using Type = Localization_<ContainerAllocator>;

  explicit Localization_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xpos = 0.0;
      this->ypos = 0.0;
      this->theta = 0.0;
      this->standard_deviation = 0.0;
    }
  }

  explicit Localization_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->xpos = 0.0;
      this->ypos = 0.0;
      this->theta = 0.0;
      this->standard_deviation = 0.0;
    }
  }

  // field types and members
  using _xpos_type =
    double;
  _xpos_type xpos;
  using _ypos_type =
    double;
  _ypos_type ypos;
  using _theta_type =
    double;
  _theta_type theta;
  using _standard_deviation_type =
    double;
  _standard_deviation_type standard_deviation;

  // setters for named parameter idiom
  Type & set__xpos(
    const double & _arg)
  {
    this->xpos = _arg;
    return *this;
  }
  Type & set__ypos(
    const double & _arg)
  {
    this->ypos = _arg;
    return *this;
  }
  Type & set__theta(
    const double & _arg)
  {
    this->theta = _arg;
    return *this;
  }
  Type & set__standard_deviation(
    const double & _arg)
  {
    this->standard_deviation = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::Localization_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::Localization_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::Localization_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::Localization_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Localization_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Localization_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Localization_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Localization_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::Localization_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::Localization_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__Localization
    std::shared_ptr<custom_interfaces::msg::Localization_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__Localization
    std::shared_ptr<custom_interfaces::msg::Localization_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Localization_ & other) const
  {
    if (this->xpos != other.xpos) {
      return false;
    }
    if (this->ypos != other.ypos) {
      return false;
    }
    if (this->theta != other.theta) {
      return false;
    }
    if (this->standard_deviation != other.standard_deviation) {
      return false;
    }
    return true;
  }
  bool operator!=(const Localization_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Localization_

// alias to use template instance with default allocator
using Localization =
  custom_interfaces::msg::Localization_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__LOCALIZATION__STRUCT_HPP_
