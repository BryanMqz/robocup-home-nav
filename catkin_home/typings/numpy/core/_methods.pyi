"""
This type stub file was generated by pyright.
"""

from numpy.core import umath as um

"""
Array methods which are called by both the C-code for the method
and the Python code for the NumPy-namespace function

"""
umr_maximum = um.maximum.reduce
umr_minimum = um.minimum.reduce
umr_sum = um.add.reduce
umr_prod = um.multiply.reduce
umr_any = um.logical_or.reduce
umr_all = um.logical_and.reduce
