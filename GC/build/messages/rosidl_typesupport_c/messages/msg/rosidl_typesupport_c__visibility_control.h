// generated from
// rosidl_typesupport_c/resource/rosidl_typesupport_c__visibility_control.h.in
// generated code does not contain a copyright notice

#ifndef MESSAGES__MSG__ROSIDL_TYPESUPPORT_C__VISIBILITY_CONTROL_H_
#define MESSAGES__MSG__ROSIDL_TYPESUPPORT_C__VISIBILITY_CONTROL_H_

#ifdef __cplusplus
extern "C"
{
#endif

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ROSIDL_TYPESUPPORT_C_EXPORT_messages __attribute__ ((dllexport))
    #define ROSIDL_TYPESUPPORT_C_IMPORT_messages __attribute__ ((dllimport))
  #else
    #define ROSIDL_TYPESUPPORT_C_EXPORT_messages __declspec(dllexport)
    #define ROSIDL_TYPESUPPORT_C_IMPORT_messages __declspec(dllimport)
  #endif
  #ifdef ROSIDL_TYPESUPPORT_C_BUILDING_DLL_messages
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_messages ROSIDL_TYPESUPPORT_C_EXPORT_messages
  #else
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_messages ROSIDL_TYPESUPPORT_C_IMPORT_messages
  #endif
#else
  #define ROSIDL_TYPESUPPORT_C_EXPORT_messages __attribute__ ((visibility("default")))
  #define ROSIDL_TYPESUPPORT_C_IMPORT_messages
  #if __GNUC__ >= 4
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_messages __attribute__ ((visibility("default")))
  #else
    #define ROSIDL_TYPESUPPORT_C_PUBLIC_messages
  #endif
#endif

#ifdef __cplusplus
}
#endif

#endif  // MESSAGES__MSG__ROSIDL_TYPESUPPORT_C__VISIBILITY_CONTROL_H_
