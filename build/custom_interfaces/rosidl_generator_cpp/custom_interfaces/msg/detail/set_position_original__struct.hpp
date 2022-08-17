// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from custom_interfaces:msg/SetPositionOriginal.idl
// generated code does not contain a copyright notice

#ifndef CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_HPP_
#define CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__custom_interfaces__msg__SetPositionOriginal __attribute__((deprecated))
#else
# define DEPRECATED__custom_interfaces__msg__SetPositionOriginal __declspec(deprecated)
#endif

namespace custom_interfaces
{

namespace msg
{

// message struct
template<class ContainerAllocator>
struct SetPositionOriginal_
{
  using Type = SetPositionOriginal_<ContainerAllocator>;

  explicit SetPositionOriginal_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->address = 0l;
      this->position = 0l;
    }
  }

  explicit SetPositionOriginal_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->id = 0;
      this->address = 0l;
      this->position = 0l;
    }
  }

  // field types and members
  using _id_type =
    uint8_t;
  _id_type id;
  using _address_type =
    int32_t;
  _address_type address;
  using _position_type =
    int32_t;
  _position_type position;

  // setters for named parameter idiom
  Type & set__id(
    const uint8_t & _arg)
  {
    this->id = _arg;
    return *this;
  }
  Type & set__address(
    const int32_t & _arg)
  {
    this->address = _arg;
    return *this;
  }
  Type & set__position(
    const int32_t & _arg)
  {
    this->position = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator> *;
  using ConstRawPtr =
    const custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__custom_interfaces__msg__SetPositionOriginal
    std::shared_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__custom_interfaces__msg__SetPositionOriginal
    std::shared_ptr<custom_interfaces::msg::SetPositionOriginal_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const SetPositionOriginal_ & other) const
  {
    if (this->id != other.id) {
      return false;
    }
    if (this->address != other.address) {
      return false;
    }
    if (this->position != other.position) {
      return false;
    }
    return true;
  }
  bool operator!=(const SetPositionOriginal_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct SetPositionOriginal_

// alias to use template instance with default allocator
using SetPositionOriginal =
  custom_interfaces::msg::SetPositionOriginal_<std::allocator<void>>;

// constant definitions

}  // namespace msg

}  // namespace custom_interfaces

#endif  // CUSTOM_INTERFACES__MSG__DETAIL__SET_POSITION_ORIGINAL__STRUCT_HPP_
