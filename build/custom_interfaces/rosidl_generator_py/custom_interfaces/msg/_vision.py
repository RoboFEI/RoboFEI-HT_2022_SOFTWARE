# generated from rosidl_generator_py/resource/_idl.py.em
# with input from custom_interfaces:msg/Vision.idl
# generated code does not contain a copyright notice


# Import statements for member types

import rosidl_parser.definition  # noqa: E402, I100


class Metaclass_Vision(type):
    """Metaclass of message 'Vision'."""

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
                'custom_interfaces.msg.Vision')
            logger.debug(
                'Failed to import needed modules for type support:\n' +
                traceback.format_exc())
        else:
            cls._CREATE_ROS_MESSAGE = module.create_ros_message_msg__msg__vision
            cls._CONVERT_FROM_PY = module.convert_from_py_msg__msg__vision
            cls._CONVERT_TO_PY = module.convert_to_py_msg__msg__vision
            cls._TYPE_SUPPORT = module.type_support_msg__msg__vision
            cls._DESTROY_ROS_MESSAGE = module.destroy_ros_message_msg__msg__vision

    @classmethod
    def __prepare__(cls, name, bases, **kwargs):
        # list constant names here so that they appear in the help text of
        # the message class under "Data and other attributes defined here:"
        # as well as populate each message instance
        return {
        }


class Vision(metaclass=Metaclass_Vision):
    """Message class 'Vision'."""

    __slots__ = [
        '_ball_detected',
        '_ball_left',
        '_ball_center_left',
        '_ball_right',
        '_ball_center_right',
        '_ball_far',
        '_ball_med',
        '_ball_close',
    ]

    _fields_and_field_types = {
        'ball_detected': 'boolean',
        'ball_left': 'boolean',
        'ball_center_left': 'boolean',
        'ball_right': 'boolean',
        'ball_center_right': 'boolean',
        'ball_far': 'boolean',
        'ball_med': 'boolean',
        'ball_close': 'boolean',
    }

    SLOT_TYPES = (
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
        rosidl_parser.definition.BasicType('boolean'),  # noqa: E501
    )

    def __init__(self, **kwargs):
        assert all('_' + key in self.__slots__ for key in kwargs.keys()), \
            'Invalid arguments passed to constructor: %s' % \
            ', '.join(sorted(k for k in kwargs.keys() if '_' + k not in self.__slots__))
        self.ball_detected = kwargs.get('ball_detected', bool())
        self.ball_left = kwargs.get('ball_left', bool())
        self.ball_center_left = kwargs.get('ball_center_left', bool())
        self.ball_right = kwargs.get('ball_right', bool())
        self.ball_center_right = kwargs.get('ball_center_right', bool())
        self.ball_far = kwargs.get('ball_far', bool())
        self.ball_med = kwargs.get('ball_med', bool())
        self.ball_close = kwargs.get('ball_close', bool())

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
        if self.ball_detected != other.ball_detected:
            return False
        if self.ball_left != other.ball_left:
            return False
        if self.ball_center_left != other.ball_center_left:
            return False
        if self.ball_right != other.ball_right:
            return False
        if self.ball_center_right != other.ball_center_right:
            return False
        if self.ball_far != other.ball_far:
            return False
        if self.ball_med != other.ball_med:
            return False
        if self.ball_close != other.ball_close:
            return False
        return True

    @classmethod
    def get_fields_and_field_types(cls):
        from copy import copy
        return copy(cls._fields_and_field_types)

    @property
    def ball_detected(self):
        """Message field 'ball_detected'."""
        return self._ball_detected

    @ball_detected.setter
    def ball_detected(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_detected' field must be of type 'bool'"
        self._ball_detected = value

    @property
    def ball_left(self):
        """Message field 'ball_left'."""
        return self._ball_left

    @ball_left.setter
    def ball_left(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_left' field must be of type 'bool'"
        self._ball_left = value

    @property
    def ball_center_left(self):
        """Message field 'ball_center_left'."""
        return self._ball_center_left

    @ball_center_left.setter
    def ball_center_left(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_center_left' field must be of type 'bool'"
        self._ball_center_left = value

    @property
    def ball_right(self):
        """Message field 'ball_right'."""
        return self._ball_right

    @ball_right.setter
    def ball_right(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_right' field must be of type 'bool'"
        self._ball_right = value

    @property
    def ball_center_right(self):
        """Message field 'ball_center_right'."""
        return self._ball_center_right

    @ball_center_right.setter
    def ball_center_right(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_center_right' field must be of type 'bool'"
        self._ball_center_right = value

    @property
    def ball_far(self):
        """Message field 'ball_far'."""
        return self._ball_far

    @ball_far.setter
    def ball_far(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_far' field must be of type 'bool'"
        self._ball_far = value

    @property
    def ball_med(self):
        """Message field 'ball_med'."""
        return self._ball_med

    @ball_med.setter
    def ball_med(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_med' field must be of type 'bool'"
        self._ball_med = value

    @property
    def ball_close(self):
        """Message field 'ball_close'."""
        return self._ball_close

    @ball_close.setter
    def ball_close(self, value):
        if __debug__:
            assert \
                isinstance(value, bool), \
                "The 'ball_close' field must be of type 'bool'"
        self._ball_close = value
