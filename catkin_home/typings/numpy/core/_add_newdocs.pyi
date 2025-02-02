"""
This type stub file was generated by pyright.
"""

import sys

"""
This is only meant to add docs to objects defined in C-extension modules.
The purpose is to allow easier editing of the docstrings without
requiring a re-compile.

NOTE: Many of the methods of ndarray have corresponding functions.
      If you update these docstrings, please keep also the ones in
      core/fromnumeric.py, core/defmatrix.py up-to-date.

"""
if sys.version_info.major < 3:
    ...
tobytesdoc = """
    a.{name}(order='C')

    Construct Python bytes containing the raw data bytes in the array.

    Constructs Python bytes showing a copy of the raw contents of
    data memory. The bytes object can be produced in either 'C' or 'Fortran',
    or 'Any' order (the default is 'C'-order). 'Any' order means C-order
    unless the F_CONTIGUOUS flag in the array is set, in which case it
    means 'Fortran' order.

    {deprecated}

    Parameters
    ----------
    order : {{'C', 'F', None}}, optional
        Order of the data for multidimensional arrays:
        C, Fortran, or the same as for the original array.

    Returns
    -------
    s : bytes
        Python bytes exhibiting a copy of `a`'s raw data.

    Examples
    --------
    >>> x = np.array([[0, 1], [2, 3]])
    >>> x.tobytes()
    b'\\x00\\x00\\x00\\x00\\x01\\x00\\x00\\x00\\x02\\x00\\x00\\x00\\x03\\x00\\x00\\x00'
    >>> x.tobytes('C') == x.tobytes()
    True
    >>> x.tobytes('F')
    b'\\x00\\x00\\x00\\x00\\x02\\x00\\x00\\x00\\x01\\x00\\x00\\x00\\x03\\x00\\x00\\x00'

    """
def numeric_type_aliases(aliases):
    ...

possible_aliases = numeric_type_aliases([('int8', '8-bit signed integer (-128 to 127)'), ('int16', '16-bit signed integer (-32768 to 32767)'), ('int32', '32-bit signed integer (-2147483648 to 2147483647)'), ('int64', '64-bit signed integer (-9223372036854775808 to 9223372036854775807)'), ('intp', 'Signed integer large enough to fit pointer, compatible with C ``intptr_t``'), ('uint8', '8-bit unsigned integer (0 to 255)'), ('uint16', '16-bit unsigned integer (0 to 65535)'), ('uint32', '32-bit unsigned integer (0 to 4294967295)'), ('uint64', '64-bit unsigned integer (0 to 18446744073709551615)'), ('uintp', 'Unsigned integer large enough to fit pointer, compatible with C ``uintptr_t``'), ('float16', '16-bit-precision floating-point number type: sign bit, 5 bits exponent, 10 bits mantissa'), ('float32', '32-bit-precision floating-point number type: sign bit, 8 bits exponent, 23 bits mantissa'), ('float64', '64-bit precision floating-point number type: sign bit, 11 bits exponent, 52 bits mantissa'), ('float96', '96-bit extended-precision floating-point number type'), ('float128', '128-bit extended-precision floating-point number type'), ('complex64', 'Complex number type composed of 2 32-bit-precision floating-point numbers'), ('complex128', 'Complex number type composed of 2 64-bit-precision floating-point numbers'), ('complex192', 'Complex number type composed of 2 96-bit extended-precision floating-point numbers'), ('complex256', 'Complex number type composed of 2 128-bit extended-precision floating-point numbers')])
def add_newdoc_for_scalar_type(obj, fixed_aliases, doc):
    ...

