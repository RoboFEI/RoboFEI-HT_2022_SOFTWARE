// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from dynamixel_sdk_custom_interfaces:msg/ParamWalk.idl
// generated code does not contain a copyright notice

#ifndef DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__STRUCT_HPP_
#define DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__dynamixel_sdk_custom_interfaces__msg__ParamWalk __attribute__((deprecated))
#else
# define DEPRECATED__dynamixel_sdk_custom_interfaces__msg__ParamWalk __declspec(deprecated)
#endif

namespace dynamixel_sdk_custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct ParamWalk_
{
  using Type = ParamWalk_<ContainerAllocator>;

  explicit ParamWalk_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->walk = 0.0;
      this->sidle = 0.0;
      this->turn = 0.0;
    }
  }

  explicit ParamWalk_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->walk = 0.0;
      this->sidle = 0.0;
      this->turn = 0.0;
    }
  }

  // field types and members
  using _walk_type =
    double;
  _walk_type walk;
  using _sidle_type =
    double;
  _sidle_type sidle;
  using _turn_type =
    double;
  _turn_type turn;

  // setters for named parameter idiom
  Type & set__walk(
    const double & _arg)
  {
    this->walk = _arg;
    return *this;
  }
  Type & set__sidle(
    const double & _arg)
  {
    this->sidle = _arg;
    return *this;
  }
  Type & set__turn(
    const double & _arg)
  {
    this->turn = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator> *;
  using ConstRawPtr =
    const dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__dynamixel_sdk_custom_interfaces__msg__ParamWalk
    std::shared_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__dynamixel_sdk_custom_interfaces__msg__ParamWalk
    std::shared_ptr<dynamixel_sdk_custom_interfaces::msg::ParamWalk_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const ParamWalk_ & other) const
  {
    if (this->walk != other.walk) {
      return false;
    }
    if (this->sidle != other.sidle) {
      return false;
    }
    if (this->turn != other.turn) {
      return false;
    }
    return true;
  }
  bool operator!=(const ParamWalk_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct ParamWalk_

// alias to use template instance with default allocator
using ParamWalk =
  dynamixel_sdk_custom_interfaces::msg::ParamWalk_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace dynamixel_sdk_custom_interfaces

#endif  // DYNAMIXEL_SDK_CUSTOM_INTERFACES__MSG__DETAIL__PARAM_WALK__STRUCT_HPP_
