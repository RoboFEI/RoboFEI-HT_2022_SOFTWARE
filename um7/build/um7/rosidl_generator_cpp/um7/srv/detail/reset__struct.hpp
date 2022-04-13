// generated from rosidl_generator_cpp/resource/idl__struct.hpp.em
// with input from um7:srv/Reset.idl
// generated code does not contain a copyright notice

#ifndef UM7__SRV__DETAIL__RESET__STRUCT_HPP_
#define UM7__SRV__DETAIL__RESET__STRUCT_HPP_

#include <rosidl_runtime_cpp/bounded_vector.hpp>
#include <rosidl_runtime_cpp/message_initialization.hpp>
#include <algorithm>
#include <array>
#include <memory>
#include <string>
#include <vector>


#ifndef _WIN32
# define DEPRECATED__um7__srv__Reset_Request __attribute__((deprecated))
#else
# define DEPRECATED__um7__srv__Reset_Request __declspec(deprecated)
#endif

namespace um7
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Reset_Request_
{
  using Type = Reset_Request_<ContainerAllocator>;

  explicit Reset_Request_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->zero_gyros = false;
      this->reset_ekf = false;
      this->set_mag_ref = false;
    }
  }

  explicit Reset_Request_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->zero_gyros = false;
      this->reset_ekf = false;
      this->set_mag_ref = false;
    }
  }

  // field types and members
  using _zero_gyros_type =
    bool;
  _zero_gyros_type zero_gyros;
  using _reset_ekf_type =
    bool;
  _reset_ekf_type reset_ekf;
  using _set_mag_ref_type =
    bool;
  _set_mag_ref_type set_mag_ref;

  // setters for named parameter idiom
  Type & set__zero_gyros(
    const bool & _arg)
  {
    this->zero_gyros = _arg;
    return *this;
  }
  Type & set__reset_ekf(
    const bool & _arg)
  {
    this->reset_ekf = _arg;
    return *this;
  }
  Type & set__set_mag_ref(
    const bool & _arg)
  {
    this->set_mag_ref = _arg;
    return *this;
  }

  // constant declarations

  // pointer types
  using RawPtr =
    um7::srv::Reset_Request_<ContainerAllocator> *;
  using ConstRawPtr =
    const um7::srv::Reset_Request_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<um7::srv::Reset_Request_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<um7::srv::Reset_Request_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      um7::srv::Reset_Request_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<um7::srv::Reset_Request_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      um7::srv::Reset_Request_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<um7::srv::Reset_Request_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<um7::srv::Reset_Request_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<um7::srv::Reset_Request_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__um7__srv__Reset_Request
    std::shared_ptr<um7::srv::Reset_Request_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__um7__srv__Reset_Request
    std::shared_ptr<um7::srv::Reset_Request_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Reset_Request_ & other) const
  {
    if (this->zero_gyros != other.zero_gyros) {
      return false;
    }
    if (this->reset_ekf != other.reset_ekf) {
      return false;
    }
    if (this->set_mag_ref != other.set_mag_ref) {
      return false;
    }
    return true;
  }
  bool operator!=(const Reset_Request_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Reset_Request_

// alias to use template instance with default allocator
using Reset_Request =
  um7::srv::Reset_Request_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace um7


#ifndef _WIN32
# define DEPRECATED__um7__srv__Reset_Response __attribute__((deprecated))
#else
# define DEPRECATED__um7__srv__Reset_Response __declspec(deprecated)
#endif

namespace um7
{

namespace srv
{

// message struct
template<class ContainerAllocator>
struct Reset_Response_
{
  using Type = Reset_Response_<ContainerAllocator>;

  explicit Reset_Response_(rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  explicit Reset_Response_(const ContainerAllocator & _alloc, rosidl_runtime_cpp::MessageInitialization _init = rosidl_runtime_cpp::MessageInitialization::ALL)
  {
    (void)_alloc;
    if (rosidl_runtime_cpp::MessageInitialization::ALL == _init ||
      rosidl_runtime_cpp::MessageInitialization::ZERO == _init)
    {
      this->structure_needs_at_least_one_member = 0;
    }
  }

  // field types and members
  using _structure_needs_at_least_one_member_type =
    uint8_t;
  _structure_needs_at_least_one_member_type structure_needs_at_least_one_member;


  // constant declarations

  // pointer types
  using RawPtr =
    um7::srv::Reset_Response_<ContainerAllocator> *;
  using ConstRawPtr =
    const um7::srv::Reset_Response_<ContainerAllocator> *;
  using SharedPtr =
    std::shared_ptr<um7::srv::Reset_Response_<ContainerAllocator>>;
  using ConstSharedPtr =
    std::shared_ptr<um7::srv::Reset_Response_<ContainerAllocator> const>;

  template<typename Deleter = std::default_delete<
      um7::srv::Reset_Response_<ContainerAllocator>>>
  using UniquePtrWithDeleter =
    std::unique_ptr<um7::srv::Reset_Response_<ContainerAllocator>, Deleter>;

  using UniquePtr = UniquePtrWithDeleter<>;

  template<typename Deleter = std::default_delete<
      um7::srv::Reset_Response_<ContainerAllocator>>>
  using ConstUniquePtrWithDeleter =
    std::unique_ptr<um7::srv::Reset_Response_<ContainerAllocator> const, Deleter>;
  using ConstUniquePtr = ConstUniquePtrWithDeleter<>;

  using WeakPtr =
    std::weak_ptr<um7::srv::Reset_Response_<ContainerAllocator>>;
  using ConstWeakPtr =
    std::weak_ptr<um7::srv::Reset_Response_<ContainerAllocator> const>;

  // pointer types similar to ROS 1, use SharedPtr / ConstSharedPtr instead
  // NOTE: Can't use 'using' here because GNU C++ can't parse attributes properly
  typedef DEPRECATED__um7__srv__Reset_Response
    std::shared_ptr<um7::srv::Reset_Response_<ContainerAllocator>>
    Ptr;
  typedef DEPRECATED__um7__srv__Reset_Response
    std::shared_ptr<um7::srv::Reset_Response_<ContainerAllocator> const>
    ConstPtr;

  // comparison operators
  bool operator==(const Reset_Response_ & other) const
  {
    if (this->structure_needs_at_least_one_member != other.structure_needs_at_least_one_member) {
      return false;
    }
    return true;
  }
  bool operator!=(const Reset_Response_ & other) const
  {
    return !this->operator==(other);
  }
};  // struct Reset_Response_

// alias to use template instance with default allocator
using Reset_Response =
  um7::srv::Reset_Response_<std::allocator<void>>;

// constant definitions

}  // namespace srv

}  // namespace um7

namespace um7
{

namespace srv
{

struct Reset
{
  using Request = um7::srv::Reset_Request;
  using Response = um7::srv::Reset_Response;
};

}  // namespace srv

}  // namespace um7

#endif  // UM7__SRV__DETAIL__RESET__STRUCT_HPP_
