"""
This type stub file was generated by pyright.
"""

import sys
import pprint
from . import __version__, auxfuncs

"""

f2py2e - Fortran to Python C/API generator. 2nd Edition.
         See __usage__ below.

Copyright 1999--2011 Pearu Peterson all rights reserved,
Pearu Peterson <pearu@cens.ioc.ee>
Permission to use, modify, and distribute this software is given under the
terms of the NumPy License.

NO WARRANTY IS EXPRESSED OR IMPLIED.  USE AT YOUR OWN RISK.
$Date: 2005/05/06 08:31:19 $
Pearu Peterson

"""
f2py_version = __version__.version
errmess = sys.stderr.write
show = pprint.pprint
outmess = auxfuncs.outmess
__usage__ = """\
Usage:

1) To construct extension module sources:

      f2py [<options>] <fortran files> [[[only:]||[skip:]] \\
                                        <fortran functions> ] \\
                                       [: <fortran files> ...]

2) To compile fortran files and build extension modules:

      f2py -c [<options>, <build_flib options>, <extra options>] <fortran files>

3) To generate signature files:

      f2py -h <filename.pyf> ...< same options as in (1) >

Description: This program generates a Python C/API file (<modulename>module.c)
             that contains wrappers for given fortran functions so that they
             can be called from Python. With the -c option the corresponding
             extension modules are built.

Options:

  --2d-numpy       Use numpy.f2py tool with NumPy support. [DEFAULT]
  --2d-numeric     Use f2py2e tool with Numeric support.
  --2d-numarray    Use f2py2e tool with Numarray support.
  --g3-numpy       Use 3rd generation f2py from the separate f2py package.
                   [NOT AVAILABLE YET]

  -h <filename>    Write signatures of the fortran routines to file <filename>
                   and exit. You can then edit <filename> and use it instead
                   of <fortran files>. If <filename>==stdout then the
                   signatures are printed to stdout.
  <fortran functions>  Names of fortran routines for which Python C/API
                   functions will be generated. Default is all that are found
                   in <fortran files>.
  <fortran files>  Paths to fortran/signature files that will be scanned for
                   <fortran functions> in order to determine their signatures.
  skip:            Ignore fortran functions that follow until `:'.
  only:            Use only fortran functions that follow until `:'.
  :                Get back to <fortran files> mode.

  -m <modulename>  Name of the module; f2py generates a Python/C API
                   file <modulename>module.c or extension module <modulename>.
                   Default is 'untitled'.

  --[no-]lower     Do [not] lower the cases in <fortran files>. By default,
                   --lower is assumed with -h key, and --no-lower without -h key.

  --build-dir <dirname>  All f2py generated files are created in <dirname>.
                   Default is tempfile.mkdtemp().

  --overwrite-signature  Overwrite existing signature file.

  --[no-]latex-doc Create (or not) <modulename>module.tex.
                   Default is --no-latex-doc.
  --short-latex    Create 'incomplete' LaTeX document (without commands
                   \\documentclass, \\tableofcontents, and \\begin{document},
                   \\end{document}).

  --[no-]rest-doc Create (or not) <modulename>module.rst.
                   Default is --no-rest-doc.

  --debug-capi     Create C/API code that reports the state of the wrappers
                   during runtime. Useful for debugging.

  --[no-]wrap-functions    Create Fortran subroutine wrappers to Fortran 77
                   functions. --wrap-functions is default because it ensures
                   maximum portability/compiler independence.

  --include-paths <path1>:<path2>:...   Search include files from the given
                   directories.

  --help-link [..] List system resources found by system_info.py. See also
                   --link-<resource> switch below. [..] is optional list
                   of resources names. E.g. try 'f2py --help-link lapack_opt'.

  --quiet          Run quietly.
  --verbose        Run with extra verbosity.
  -v               Print f2py version ID and exit.


numpy.distutils options (only effective with -c):

  --fcompiler=         Specify Fortran compiler type by vendor
  --compiler=          Specify C compiler type (as defined by distutils)

  --help-fcompiler     List available Fortran compilers and exit
  --f77exec=           Specify the path to F77 compiler
  --f90exec=           Specify the path to F90 compiler
  --f77flags=          Specify F77 compiler flags
  --f90flags=          Specify F90 compiler flags
  --opt=               Specify optimization flags
  --arch=              Specify architecture specific optimization flags
  --noopt              Compile without optimization
  --noarch             Compile without arch-dependent optimization
  --debug              Compile with debugging information

Extra options (only effective with -c):

  --link-<resource>    Link extension module with <resource> as defined
                       by numpy.distutils/system_info.py. E.g. to link
                       with optimized LAPACK libraries (vecLib on MacOSX,
                       ATLAS elsewhere), use --link-lapack_opt.
                       See also --help-link switch.

  -L/path/to/lib/ -l<libname>
  -D<define> -U<name>
  -I/path/to/include/
  <filename>.o <filename>.so <filename>.a

  Using the following macros may be required with non-gcc Fortran
  compilers:
    -DPREPEND_FORTRAN -DNO_APPEND_FORTRAN -DUPPERCASE_FORTRAN
    -DUNDERSCORE_G77

  When using -DF2PY_REPORT_ATEXIT, a performance report of F2PY
  interface is printed out at exit (platforms: Linux).

  When using -DF2PY_REPORT_ON_ARRAY_COPY=<int>, a message is
  sent to stderr whenever F2PY interface makes a copy of an
  array. Integer <int> sets the threshold for array sizes when
  a message should be shown.

Version:     %s
numpy Version: %s
Requires:    Python 2.3 or higher.
License:     NumPy license (see LICENSE.txt in the NumPy source code)
Copyright 1999 - 2011 Pearu Peterson all rights reserved.
http://cens.ioc.ee/projects/f2py2e/""" % (f2py_version, numpy_version)
def scaninputline(inputline):
    ...

def callcrackfortran(files, options):
    ...

def buildmodules(lst):
    ...

def dict_append(d_out, d_in):
    ...

def run_main(comline_list):
    """
    Equivalent to running::

        f2py <args>

    where ``<args>=string.join(<list>,' ')``, but in Python.  Unless
    ``-h`` is used, this function returns a dictionary containing
    information on generated modules and their dependencies on source
    files.  For example, the command ``f2py -m scalar scalar.f`` can be
    executed from Python as follows

    You cannot build extension modules with this function, that is,
    using ``-c`` is not allowed. Use ``compile`` command instead

    Examples
    --------
    .. include:: run_main_session.dat
        :literal:

    """
    ...

def filter_files(prefix, suffix, files, remove_prefix=...):
    """
    Filter files by prefix and suffix.
    """
    ...

def get_prefix(module):
    ...

def run_compile():
    """
    Do it all in one call!
    """
    ...

def main():
    ...

