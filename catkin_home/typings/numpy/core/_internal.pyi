"""
This type stub file was generated by pyright.
"""

import re
import sys
import platform
from numpy.core.overrides import set_module

"""
A place for internal code

Some things are more easily handled Python.

"""
IS_PYPY = platform.python_implementation() == 'PyPy'
if sys.byteorder == 'little':
    _nbo = b'<'
else:
    _nbo = b'>'
format_re = re.compile(rb'(?P<order1>[<>|=]?)' rb'(?P<repeats> *[(]?[ ,0-9L]*[)]? *)' rb'(?P<order2>[<>|=]?)' rb'(?P<dtype>[A-Za-z0-9.?]*(?:\[[a-zA-Z0-9,.]+\])?)')
sep_re = re.compile(rb'\s*,\s*')
space_re = re.compile(rb'\s+$')
_convorder = { b'=': _nbo }
class dummy_ctype(object):
    def __init__(self, cls) -> None:
        ...
    
    def __mul__(self, other):
        ...
    
    def __call__(self, *other):
        ...
    
    def __eq__(self, other) -> bool:
        ...
    
    def __ne__(self, other) -> bool:
        ...
    


class _missing_ctypes(object):
    def cast(self, num, obj):
        ...
    
    class c_void_p(object):
        def __init__(self, ptr) -> None:
            ...
        
    
    


class _ctypes(object):
    def __init__(self, array, ptr=...) -> None:
        ...
    
    def data_as(self, obj):
        """
        Return the data pointer cast to a particular c-types object.
        For example, calling ``self._as_parameter_`` is equivalent to
        ``self.data_as(ctypes.c_void_p)``. Perhaps you want to use the data as a
        pointer to a ctypes array of floating-point data:
        ``self.data_as(ctypes.POINTER(ctypes.c_double))``.

        The returned pointer will keep a reference to the array.
        """
        ...
    
    def shape_as(self, obj):
        """
        Return the shape tuple as an array of some other c-types
        type. For example: ``self.shape_as(ctypes.c_short)``.
        """
        ...
    
    def strides_as(self, obj):
        """
        Return the strides tuple as an array of some other
        c-types type. For example: ``self.strides_as(ctypes.c_longlong)``.
        """
        ...
    
    @property
    def data(self):
        """
        A pointer to the memory area of the array as a Python integer.
        This memory area may contain data that is not aligned, or not in correct
        byte-order. The memory area may not even be writeable. The array
        flags and data-type of this array should be respected when passing this
        attribute to arbitrary C-code to avoid trouble that can include Python
        crashing. User Beware! The value of this attribute is exactly the same
        as ``self._array_interface_['data'][0]``.

        Note that unlike `data_as`, a reference will not be kept to the array:
        code like ``ctypes.c_void_p((a + b).ctypes.data)`` will result in a
        pointer to a deallocated array, and should be spelt
        ``(a + b).ctypes.data_as(ctypes.c_void_p)``
        """
        ...
    
    @property
    def shape(self):
        """
        (c_intp*self.ndim): A ctypes array of length self.ndim where
        the basetype is the C-integer corresponding to ``dtype('p')`` on this
        platform. This base-type could be `ctypes.c_int`, `ctypes.c_long`, or
        `ctypes.c_longlong` depending on the platform.
        The c_intp type is defined accordingly in `numpy.ctypeslib`.
        The ctypes array contains the shape of the underlying array.
        """
        ...
    
    @property
    def strides(self):
        """
        (c_intp*self.ndim): A ctypes array of length self.ndim where
        the basetype is the same as for the shape attribute. This ctypes array
        contains the strides information from the underlying array. This strides
        information is important for showing how many bytes must be jumped to
        get to the next element in the array.
        """
        ...
    
    get_data = ...
    get_shape = ...
    get_strides = ...
    get_as_parameter = ...


_pep3118_native_map = { '?': '?','c': 'S1','b': 'b','B': 'B','h': 'h','H': 'H','i': 'i','I': 'I','l': 'l','L': 'L','q': 'q','Q': 'Q','e': 'e','f': 'f','d': 'd','g': 'g','Zf': 'F','Zd': 'D','Zg': 'G','s': 'S','w': 'U','O': 'O','x': 'V' }
_pep3118_native_typechars = ''.join(_pep3118_native_map.keys())
_pep3118_standard_map = { '?': '?','c': 'S1','b': 'b','B': 'B','h': 'i2','H': 'u2','i': 'i4','I': 'u4','l': 'i4','L': 'u4','q': 'i8','Q': 'u8','e': 'f2','f': 'f','d': 'd','Zf': 'F','Zd': 'D','s': 'S','w': 'U','O': 'O','x': 'V' }
_pep3118_standard_typechars = ''.join(_pep3118_standard_map.keys())
_pep3118_unsupported_map = { 'u': 'UCS-2 strings','&': 'pointers','t': 'bitfields','X': 'function pointers' }
class _Stream(object):
    def __init__(self, s) -> None:
        ...
    
    def advance(self, n):
        ...
    
    def consume(self, c):
        ...
    
    def consume_until(self, c):
        ...
    
    @property
    def next(self):
        ...
    
    def __bool__(self):
        ...
    
    __nonzero__ = ...


@set_module('numpy')
class TooHardError(RuntimeError):
    ...


@set_module('numpy')
class AxisError(ValueError, IndexError):
    """ Axis supplied was invalid. """
    def __init__(self, axis, ndim=..., msg_prefix=...) -> None:
        ...
    


def array_ufunc_errmsg_formatter(dummy, ufunc, method, *inputs, **kwargs):
    """ Format the error message for when __array_ufunc__ gives up. """
    ...

def array_function_errmsg_formatter(public_api, types):
    """ Format the error message for when __array_ufunc__ gives up. """
    ...

def npy_ctypes_check(cls):
    ...

class recursive(object):
    '''
    A decorator class for recursive nested functions.
    Naive recursive nested functions hold a reference to themselves:

    def outer(*args):
        def stringify_leaky(arg0, *arg1):
            if len(arg1) > 0:
                return stringify_leaky(*arg1)  # <- HERE
            return str(arg0)
        stringify_leaky(*args)

    This design pattern creates a reference cycle that is difficult for a
    garbage collector to resolve. The decorator class prevents the
    cycle by passing the nested function in as an argument `self`:

    def outer(*args):
        @recursive
        def stringify(self, arg0, *arg1):
            if len(arg1) > 0:
                return self(*arg1)
            return str(arg0)
        stringify(*args)

    '''
    def __init__(self, func) -> None:
        ...
    
    def __call__(self, *args, **kwargs):
        ...
    


