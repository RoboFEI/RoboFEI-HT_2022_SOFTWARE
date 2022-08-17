// generated from rosidl_generator_py/resource/_idl_support.c.em
// with input from custom_interfaces:msg/Localization.idl
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
#include "custom_interfaces/msg/detail/localization__struct.h"
#include "custom_interfaces/msg/detail/localization__functions.h"


ROSIDL_GENERATOR_C_EXPORT
bool custom_interfaces__msg__localization__convert_from_py(PyObject * _pymsg, void * _ros_message)
{
  // check that the passed message is of the expected Python class
  {
    char full_classname_dest[49];
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
    assert(strncmp("custom_interfaces.msg._localization.Localization", full_classname_dest, 48) == 0);
  }
  custom_interfaces__msg__Localization * ros_message = _ros_message;
  {  // xpos
    PyObject * field = PyObject_GetAttrString(_pymsg, "xpos");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->xpos = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // ypos
    PyObject * field = PyObject_GetAttrString(_pymsg, "ypos");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->ypos = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // theta
    PyObject * field = PyObject_GetAttrString(_pymsg, "theta");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->theta = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }
  {  // standard_deviation
    PyObject * field = PyObject_GetAttrString(_pymsg, "standard_deviation");
    if (!field) {
      return false;
    }
    assert(PyFloat_Check(field));
    ros_message->standard_deviation = PyFloat_AS_DOUBLE(field);
    Py_DECREF(field);
  }

  return true;
}

ROSIDL_GENERATOR_C_EXPORT
PyObject * custom_interfaces__msg__localization__convert_to_py(void * raw_ros_message)
{
  /* NOTE(esteve): Call constructor of Localization */
  PyObject * _pymessage = NULL;
  {
    PyObject * pymessage_module = PyImport_ImportModule("custom_interfaces.msg._localization");
    assert(pymessage_module);
    PyObject * pymessage_class = PyObject_GetAttrString(pymessage_module, "Localization");
    assert(pymessage_class);
    Py_DECREF(pymessage_module);
    _pymessage = PyObject_CallObject(pymessage_class, NULL);
    Py_DECREF(pymessage_class);
    if (!_pymessage) {
      return NULL;
    }
  }
  custom_interfaces__msg__Localization * ros_message = (custom_interfaces__msg__Localization *)raw_ros_message;
  {  // xpos
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->xpos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "xpos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // ypos
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->ypos);
    {
      int rc = PyObject_SetAttrString(_pymessage, "ypos", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // theta
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->theta);
    {
      int rc = PyObject_SetAttrString(_pymessage, "theta", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }
  {  // standard_deviation
    PyObject * field = NULL;
    field = PyFloat_FromDouble(ros_message->standard_deviation);
    {
      int rc = PyObject_SetAttrString(_pymessage, "standard_deviation", field);
      Py_DECREF(field);
      if (rc) {
        return NULL;
      }
    }
  }

  // ownership of _pymessage is transferred to the caller
  return _pymessage;
}
