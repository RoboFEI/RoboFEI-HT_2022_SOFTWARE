# generated from rosidl_generator_py/resource/_idl.py.em
# with input from custom_interfaces:srv/Reset.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Reset_Request(type):
    """Metaclass of message 'Reset_Request'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('custom_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'custom_interfaces.srv.Reset_Request')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__reset__request
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__reset__request
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__reset__request
            cls._TYPE_SUPPORT = module.type_support_msg__srv__reset__request
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__reset__request

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Reset_Request(metaclass=Metaclass_Reset_Request):
    """Message class 'Reset_Request'."""

    __slots__ = [
        '_zero_gyros',
        '_reset_ekf',
        '_set_mag_ref',
    ]

    _fields_and_field_types = {
        'zero_gyros': 'boolean',
        'reset_ekf': 'boolean',
        'set_mag_ref': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.zero_gyros = kwargs.get('zero_gyros', bool())
        self.reset_ekf = kwargs.get('reset_ekf', bool())
        self.set_mag_ref = kwargs.get('set_mag_ref', bool())

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        if self.zero_gyros != other.zero_gyros:
            return False
        if self.reset_ekf != other.reset_ekf:
            return False
        if self.set_mag_ref != other.set_mag_ref:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def zero_gyros(self):
        """Message field 'zero_gyros'."""
        return self._zero_gyros

    @zero_gyros.setter
    def zero_gyros(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'zero_gyros' field must be of type 'bool'"
        self._zero_gyros = value

    @property
    def reset_ekf(self):
        """Message field 'reset_ekf'."""
        return self._reset_ekf

    @reset_ekf.setter
    def reset_ekf(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'reset_ekf' field must be of type 'bool'"
        self._reset_ekf = value

    @property
    def set_mag_ref(self):
        """Message field 'set_mag_ref'."""
        return self._set_mag_ref

    @set_mag_ref.setter
    def set_mag_ref(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'set_mag_ref' field must be of type 'bool'"
        self._set_mag_ref = value


# Import statements for member types

# already imported above
# import rosidl_parser.definition


class Metaclass_Reset_Response(type):
    """Metaclass of message 'Reset_Response'."""

    _CREATE_ROS_MESSAGE = None
    _CONVERT_FROM_PY = None
    _CONVERT_TO_PY = None
    _DESTROY_ROS_MESSAGE = None
    _TYPE_SUPPORT = None

    __constants = {
    }

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('custom_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'custom_interfaces.srv.Reset_Response')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__srv__reset__response
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__srv__reset__response
            cls._CONVERT_TO_PY = module.convert_to_py_msg__srv__reset__response
            cls._TYPE_SUPPORT = module.type_support_msg__srv__reset__response
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__srv__reset__response

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Reset_Response(metaclass=Metaclass_Reset_Response):
    """Message class 'Reset_Response'."""

    __slots__ = [
    ]

    _fields_and_field_types = {
    }

    SLOT_TYPES = (
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))

    def __repr__(self):
        typename = self.__class__.__module__.split('.')
        typename.pop()
        typename.append(self.__class__.__name__)
        args = []
        for s, t in zip(self.__slots__, self.SLOT_TYPES):
            field = getattr(self, s)
            fieldstr = repr(field)
            # We use Python array type for fields that can be directly stored
            # in them, and "normal" sequences for everything else.  If it is
            # a type that we store in an array, strip off the 'array' portion.
            if (
                isinstance(t, rosidl_parser.definition.AbstractSequence) and
                isinstance(t.value_type, rosidl_parser.definition.BasicType) and
                t.value_type.typename in ['float', 'double', 'int8', 'uint8', 'int16', 'uint16', 'int32', 'uint32', 'int64', 'uint64']
            ):
                if len(field) == 0:
                    fieldstr = '[]'
                else:
                    assert fieldstr.startswith('array(')
                    prefix = "array('X', "
                    suffix = ')'
                    fieldstr = fieldstr[len(prefix):-len(suffix)]
            args.append(s[1:] + '=' + fieldstr)
        return '%s(%s)' % ('.'.join(typename), ', '.join(args))

    def __eq__(self, other):
        if not isinstance(other, self.__class__):
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)


class Metaclass_Reset(type):
    """Metaclass of service 'Reset'."""

    _TYPE_SUPPORT = None

    @classmethod
    def __import_type_support__(cls):
        try:
            from rosidl_generator_py import import_type_support
            module = import_type_support('custom_interfaces')
        except ImportError:
            import logging
            import traceback
            logger = logging.getLogger(
                'custom_interfaces.srv.Reset')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._TYPE_SUPPORT = module.type_support_srv__srv__reset

            from custom_interfaces.srv import _reset
            if _reset.Metaclass_Reset_Request._TYPE_SUPPORT is None:
                _reset.Metaclass_Reset_Request.__import_type_support__()
            if _reset.Metaclass_Reset_Response._TYPE_SUPPORT is None:
                _reset.Metaclass_Reset_Response.__import_type_support__()


class Reset(metaclass=Metaclass_Reset):
    from custom_interfaces.srv._reset import Reset_Request as Request
    from custom_interfaces.srv._reset import Reset_Response as Response

    def __init__(self):
        raise NotImplementedError('Service classes can not be instantiated')
