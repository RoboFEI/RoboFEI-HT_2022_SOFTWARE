// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from custom_interfaces:srv/Reset.idl
// generated code does not contain a copyright notice
#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
#include <Python.h>
#include <stdbool.h>
#ifndef _WIN32
# pragma GCC diagnostic push
# pragma GCC diagnostic ignored "-Wunused-function"
#endif
#include "numpy/ndarrayobject.h"
#ifndef _WIN32
# pragma GCC diagnostic pop
#endif
#include "rosidl_runtime_c/visibility_control.h"
#include "custom_interfaces/srv/detail/reset__struct.h"
#include "custom_interfaces/srv/detail/reset__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool custom_interfaces__srv__reset__request__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[43];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("custom_interfaces.srv._reset.Reset_Request", full_classname_dest, 42) == 0);
  }
  custom_interfaces__srv__Reset_Request * ros_message = _ros_message;
  {  // zero_gyros
    PyObject * field = PyObject_GetAttrString(_pymsg, "zero_gyros");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->zero_gyros = (Py_True == field);
    Py_DECREF(field);
  }
  {  // reset_ekf
    PyObject * field = PyObject_GetAttrString(_pymsg, "reset_ekf");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->reset_ekf = (Py_True == field);
    Py_DECREF(field);
  }
  {  // set_mag_ref
    PyObject * field = PyObject_GetAttrString(_pymsg, "set_mag_ref");
    if (!field) {
      return false;
    }
    assert(PyBool_Check(field));
    ros_message->set_mag_ref = (Py_True == field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * custom_interfaces__srv__reset__request__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Reset_Request */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("custom_interfaces.srv._reset");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Reset_Request");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  custom_interfaces__srv__Reset_Request * ros_message = (custom_interfaces__srv__Reset_Request *)raw_ros_message;
  {  // zero_gyros
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->zero_gyros ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "zero_gyros", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // reset_ekf
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->reset_ekf ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "reset_ekf", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // set_mag_ref
    PyObject * field = NULL;
    field = PyBool_FromLong(ros_message->set_mag_ref ? 1 : 0);
    {
      int rc = PyObject_SetAttrString(_pymessage, "set_mag_ref", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}

#define NPY_NO_DEPRECATED_API NPY_1_7_API_VERSION
// already included above
// #include <Python.h>
// already included above
// #include <stdbool.h>
// already included above
// #include "numpy/ndarrayobject.h"
// already included above
// #include "rosidl_runtime_c/visibility_control.h"
// already included above
// #include "custom_interfaces/srv/detail/reset__struct.h"
// already included above
// #include "custom_interfaces/srv/detail/reset__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool custom_interfaces__srv__reset__response__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[44];
    {
      char * class_name = NULL;
      char * module_name = NULL;
      {
        PyObject * class_attr = PyObject_GetAttrString(_pymsg, "__class__");
        if (class_attr) {
          PyObject * name_attr = PyObject_GetAttrString(class_attr, "__name__");
          if (name_attr) {
            class_name = (char *)PyUnicode_1BYTE_DATA(name_attr);
            Py_DECREF(name_attr);
          }
          PyObject * module_attr = PyObject_GetAttrString(class_attr, "__module__");
          if (module_attr) {
            module_name = (char *)PyUnicode_1BYTE_DATA(module_attr);
            Py_DECREF(module_attr);
          }
          Py_DECREF(class_attr);
        }
      }
      if (!class_name || !module_name) {
        return false;
      }
      snprintf(full_classname_dest, sizeof(full_classname_dest), "%s.%s", module_name, class_name);
    }
    assert(strncmp("custom_interfaces.srv._reset.Reset_Response", full_classname_dest, 43) == 0);
  }
  custom_interfaces__srv__Reset_Response * ros_message = _ros_message;
  ros_message->structure_needs_at_least_one_member = 0;

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * custom_interfaces__srv__reset__response__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Reset_Response */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("custom_interfaces.srv._reset");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Reset_Response");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  (void)raw_ros_message;

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
