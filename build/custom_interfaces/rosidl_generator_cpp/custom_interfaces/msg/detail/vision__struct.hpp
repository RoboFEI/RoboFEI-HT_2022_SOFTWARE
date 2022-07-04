// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/Vision.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__VISION__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__VISION__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__Vision __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__Vision __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct Vision_
{
  using Type = Vision_<ContainerAllocator>;

  explicit Vision_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ball_detected = false;
      this->ball_left = false;
      this->ball_center_left = false;
      this->ball_right = false;
      this->ball_center_right = false;
      this->ball_far = false;
      this->ball_med = false;
      this->ball_close = false;
    }
  }

  explicit Vision_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->ball_detected = false;
      this->ball_left = false;
      this->ball_center_left = false;
      this->ball_right = false;
      this->ball_center_right = false;
      this->ball_far = false;
      this->ball_med = false;
      this->ball_close = false;
    }
  }

  // field types and members
  using _ball_detected_type =
    bool;
  _ball_detected_type ball_detected;
  using _ball_left_type =
    bool;
  _ball_left_type ball_left;
  using _ball_center_left_type =
    bool;
  _ball_center_left_type ball_center_left;
  using _ball_right_type =
    bool;
  _ball_right_type ball_right;
  using _ball_center_right_type =
    bool;
  _ball_center_right_type ball_center_right;
  using _ball_far_type =
    bool;
  _ball_far_type ball_far;
  using _ball_med_type =
    bool;
  _ball_med_type ball_med;
  using _ball_close_type =
    bool;
  _ball_close_type ball_close;

  // setters for named parameter idiom
  Type & set__ball_detected(
    const bool & _arg)
  {
    this->ball_detected = _arg;
    return *this;
  }
  Type & set__ball_left(
    const bool & _arg)
  {
    this->ball_left = _arg;
    return *this;
  }
  Type & set__ball_center_left(
    const bool & _arg)
  {
    this->ball_center_left = _arg;
    return *this;
  }
  Type & set__ball_right(
    const bool & _arg)
  {
    this->ball_right = _arg;
    return *this;
  }
  Type & set__ball_center_right(
    const bool & _arg)
  {
    this->ball_center_right = _arg;
    return *this;
  }
  Type & set__ball_far(
    const bool & _arg)
  {
    this->ball_far = _arg;
    return *this;
  }
  Type & set__ball_med(
    const bool & _arg)
  {
    this->ball_med = _arg;
    return *this;
  }
  Type & set__ball_close(
    const bool & _arg)
  {
    this->ball_close = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::Vision_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::Vision_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::Vision_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::Vision_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Vision_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Vision_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::Vision_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::Vision_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::Vision_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::Vision_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__Vision
    std::shared_ptr<custom_interfaces::msg::Vision_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__Vision
    std::shared_ptr<custom_interfaces::msg::Vision_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Vision_ & other) const
  {
    if (this->ball_detected != other.ball_detected) {
      return false;
    }
    if (this->ball_left != other.ball_left) {
      return false;
    }
    if (this->ball_center_left != other.ball_center_left) {
      return false;
    }
    if (this->ball_right != other.ball_right) {
      return false;
    }
    if (this->ball_center_right != other.ball_center_right) {
      return false;
    }
    if (this->ball_far != other.ball_far) {
      return false;
    }
    if (this->ball_med != other.ball_med) {
      return false;
    }
    if (this->ball_close != other.ball_close) {
      return false;
    }
    return true;
  }
  bool operator!=(const Vision_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Vision_

// alias to use template instance with default allocator
using Vision =
  custom_interfaces::msg::Vision_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__VISION__STRUCT_HPP_
