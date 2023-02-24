r"""Wrapper for UIAnimation.h

Generated with:
/home/john/.local/bin/ctypesgen -lpanosui /usr/local/include/UIAnimation.h /usr/local/include/UIApplication.h /usr/local/include/UIColor.h /usr/local/include/UIEvent.h /usr/local/include/UIEventResponder.h /usr/local/include/UIGeometry.h /usr/local/include/UILabel.h /usr/local/include/UILayer.h /usr/local/include/UIView.h /usr/local/include/UIWindowController.h /usr/local/include/UIWindow.h -o panosui.py

Do not modify this file.
"""

__docformat__ = "restructuredtext"

# Begin preamble for Python

import ctypes
import sys
from ctypes import *  # noqa: F401, F403

_int_types = (ctypes.c_int16, ctypes.c_int32)
if hasattr(ctypes, "c_int64"):
    # Some builds of ctypes apparently do not have ctypes.c_int64
    # defined; it's a pretty good bet that these builds do not
    # have 64-bit pointers.
    _int_types += (ctypes.c_int64,)
for t in _int_types:
    if ctypes.sizeof(t) == ctypes.sizeof(ctypes.c_size_t):
        c_ptrdiff_t = t
del t
del _int_types



class UserString:
    def __init__(self, seq):
        if isinstance(seq, bytes):
            self.data = seq
        elif isinstance(seq, UserString):
            self.data = seq.data[:]
        else:
            self.data = str(seq).encode()

    def __bytes__(self):
        return self.data

    def __str__(self):
        return self.data.decode()

    def __repr__(self):
        return repr(self.data)

    def __int__(self):
        return int(self.data.decode())

    def __long__(self):
        return int(self.data.decode())

    def __float__(self):
        return float(self.data.decode())

    def __complex__(self):
        return complex(self.data.decode())

    def __hash__(self):
        return hash(self.data)

    def __le__(self, string):
        if isinstance(string, UserString):
            return self.data <= string.data
        else:
            return self.data <= string

    def __lt__(self, string):
        if isinstance(string, UserString):
            return self.data < string.data
        else:
            return self.data < string

    def __ge__(self, string):
        if isinstance(string, UserString):
            return self.data >= string.data
        else:
            return self.data >= string

    def __gt__(self, string):
        if isinstance(string, UserString):
            return self.data > string.data
        else:
            return self.data > string

    def __eq__(self, string):
        if isinstance(string, UserString):
            return self.data == string.data
        else:
            return self.data == string

    def __ne__(self, string):
        if isinstance(string, UserString):
            return self.data != string.data
        else:
            return self.data != string

    def __contains__(self, char):
        return char in self.data

    def __len__(self):
        return len(self.data)

    def __getitem__(self, index):
        return self.__class__(self.data[index])

    def __getslice__(self, start, end):
        start = max(start, 0)
        end = max(end, 0)
        return self.__class__(self.data[start:end])

    def __add__(self, other):
        if isinstance(other, UserString):
            return self.__class__(self.data + other.data)
        elif isinstance(other, bytes):
            return self.__class__(self.data + other)
        else:
            return self.__class__(self.data + str(other).encode())

    def __radd__(self, other):
        if isinstance(other, bytes):
            return self.__class__(other + self.data)
        else:
            return self.__class__(str(other).encode() + self.data)

    def __mul__(self, n):
        return self.__class__(self.data * n)

    __rmul__ = __mul__

    def __mod__(self, args):
        return self.__class__(self.data % args)

    # the following methods are defined in alphabetical order:
    def capitalize(self):
        return self.__class__(self.data.capitalize())

    def center(self, width, *args):
        return self.__class__(self.data.center(width, *args))

    def count(self, sub, start=0, end=sys.maxsize):
        return self.data.count(sub, start, end)

    def decode(self, encoding=None, errors=None):  # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.decode(encoding, errors))
            else:
                return self.__class__(self.data.decode(encoding))
        else:
            return self.__class__(self.data.decode())

    def encode(self, encoding=None, errors=None):  # XXX improve this?
        if encoding:
            if errors:
                return self.__class__(self.data.encode(encoding, errors))
            else:
                return self.__class__(self.data.encode(encoding))
        else:
            return self.__class__(self.data.encode())

    def endswith(self, suffix, start=0, end=sys.maxsize):
        return self.data.endswith(suffix, start, end)

    def expandtabs(self, tabsize=8):
        return self.__class__(self.data.expandtabs(tabsize))

    def find(self, sub, start=0, end=sys.maxsize):
        return self.data.find(sub, start, end)

    def index(self, sub, start=0, end=sys.maxsize):
        return self.data.index(sub, start, end)

    def isalpha(self):
        return self.data.isalpha()

    def isalnum(self):
        return self.data.isalnum()

    def isdecimal(self):
        return self.data.isdecimal()

    def isdigit(self):
        return self.data.isdigit()

    def islower(self):
        return self.data.islower()

    def isnumeric(self):
        return self.data.isnumeric()

    def isspace(self):
        return self.data.isspace()

    def istitle(self):
        return self.data.istitle()

    def isupper(self):
        return self.data.isupper()

    def join(self, seq):
        return self.data.join(seq)

    def ljust(self, width, *args):
        return self.__class__(self.data.ljust(width, *args))

    def lower(self):
        return self.__class__(self.data.lower())

    def lstrip(self, chars=None):
        return self.__class__(self.data.lstrip(chars))

    def partition(self, sep):
        return self.data.partition(sep)

    def replace(self, old, new, maxsplit=-1):
        return self.__class__(self.data.replace(old, new, maxsplit))

    def rfind(self, sub, start=0, end=sys.maxsize):
        return self.data.rfind(sub, start, end)

    def rindex(self, sub, start=0, end=sys.maxsize):
        return self.data.rindex(sub, start, end)

    def rjust(self, width, *args):
        return self.__class__(self.data.rjust(width, *args))

    def rpartition(self, sep):
        return self.data.rpartition(sep)

    def rstrip(self, chars=None):
        return self.__class__(self.data.rstrip(chars))

    def split(self, sep=None, maxsplit=-1):
        return self.data.split(sep, maxsplit)

    def rsplit(self, sep=None, maxsplit=-1):
        return self.data.rsplit(sep, maxsplit)

    def splitlines(self, keepends=0):
        return self.data.splitlines(keepends)

    def startswith(self, prefix, start=0, end=sys.maxsize):
        return self.data.startswith(prefix, start, end)

    def strip(self, chars=None):
        return self.__class__(self.data.strip(chars))

    def swapcase(self):
        return self.__class__(self.data.swapcase())

    def title(self):
        return self.__class__(self.data.title())

    def translate(self, *args):
        return self.__class__(self.data.translate(*args))

    def upper(self):
        return self.__class__(self.data.upper())

    def zfill(self, width):
        return self.__class__(self.data.zfill(width))


class MutableString(UserString):
    """mutable string objects

    Python strings are immutable objects.  This has the advantage, that
    strings may be used as dictionary keys.  If this property isn't needed
    and you insist on changing string values in place instead, you may cheat
    and use MutableString.

    But the purpose of this class is an educational one: to prevent
    people from inventing their own mutable string class derived
    from UserString and than forget thereby to remove (override) the
    __hash__ method inherited from UserString.  This would lead to
    errors that would be very hard to track down.

    A faster and better solution is to rewrite your program using lists."""

    def __init__(self, string=""):
        self.data = string

    def __hash__(self):
        raise TypeError("unhashable type (it is mutable)")

    def __setitem__(self, index, sub):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data):
            raise IndexError
        self.data = self.data[:index] + sub + self.data[index + 1 :]

    def __delitem__(self, index):
        if index < 0:
            index += len(self.data)
        if index < 0 or index >= len(self.data):
            raise IndexError
        self.data = self.data[:index] + self.data[index + 1 :]

    def __setslice__(self, start, end, sub):
        start = max(start, 0)
        end = max(end, 0)
        if isinstance(sub, UserString):
            self.data = self.data[:start] + sub.data + self.data[end:]
        elif isinstance(sub, bytes):
            self.data = self.data[:start] + sub + self.data[end:]
        else:
            self.data = self.data[:start] + str(sub).encode() + self.data[end:]

    def __delslice__(self, start, end):
        start = max(start, 0)
        end = max(end, 0)
        self.data = self.data[:start] + self.data[end:]

    def immutable(self):
        return UserString(self.data)

    def __iadd__(self, other):
        if isinstance(other, UserString):
            self.data += other.data
        elif isinstance(other, bytes):
            self.data += other
        else:
            self.data += str(other).encode()
        return self

    def __imul__(self, n):
        self.data *= n
        return self


class String(MutableString, ctypes.Union):

    _fields_ = [("raw", ctypes.POINTER(ctypes.c_char)), ("data", ctypes.c_char_p)]

    def __init__(self, obj=b""):
        if isinstance(obj, (bytes, UserString)):
            self.data = bytes(obj)
        else:
            self.raw = obj

    def __len__(self):
        return self.data and len(self.data) or 0

    def from_param(cls, obj):
        # Convert None or 0
        if obj is None or obj == 0:
            return cls(ctypes.POINTER(ctypes.c_char)())

        # Convert from String
        elif isinstance(obj, String):
            return obj

        # Convert from bytes
        elif isinstance(obj, bytes):
            return cls(obj)

        # Convert from str
        elif isinstance(obj, str):
            return cls(obj.encode())

        # Convert from c_char_p
        elif isinstance(obj, ctypes.c_char_p):
            return obj

        # Convert from POINTER(ctypes.c_char)
        elif isinstance(obj, ctypes.POINTER(ctypes.c_char)):
            return obj

        # Convert from raw pointer
        elif isinstance(obj, int):
            return cls(ctypes.cast(obj, ctypes.POINTER(ctypes.c_char)))

        # Convert from ctypes.c_char array
        elif isinstance(obj, ctypes.c_char * len(obj)):
            return obj

        # Convert from object
        else:
            return String.from_param(obj._as_parameter_)

    from_param = classmethod(from_param)


def ReturnString(obj, func=None, arguments=None):
    return String.from_param(obj)


# As of ctypes 1.0, ctypes does not support custom error-checking
# functions on callbacks, nor does it support custom datatypes on
# callbacks, so we must ensure that all callbacks return
# primitive datatypes.
#
# Non-primitive return values wrapped with UNCHECKED won't be
# typechecked, and will be converted to ctypes.c_void_p.
def UNCHECKED(type):
    if hasattr(type, "_type_") and isinstance(type._type_, str) and type._type_ != "P":
        return type
    else:
        return ctypes.c_void_p


# ctypes doesn't have direct support for variadic functions, so we have to write
# our own wrapper class
class _variadic_function(object):
    def __init__(self, func, restype, argtypes, errcheck):
        self.func = func
        self.func.restype = restype
        self.argtypes = argtypes
        if errcheck:
            self.func.errcheck = errcheck

    def _as_parameter_(self):
        # So we can pass this variadic function as a function pointer
        return self.func

    def __call__(self, *args):
        fixed_args = []
        i = 0
        for argtype in self.argtypes:
            # Typecheck what we can
            fixed_args.append(argtype.from_param(args[i]))
            i += 1
        return self.func(*fixed_args + list(args[i:]))


def ord_if_char(value):
    """
    Simple helper used for casts to simple builtin types:  if the argument is a
    string type, it will be converted to it's ordinal value.

    This function will raise an exception if the argument is string with more
    than one characters.
    """
    return ord(value) if (isinstance(value, bytes) or isinstance(value, str)) else value

# End preamble

_libs = {}
_libdirs = []

# Begin loader

"""
Load libraries - appropriately for all our supported platforms
"""
# ----------------------------------------------------------------------------
# Copyright (c) 2008 David James
# Copyright (c) 2006-2008 Alex Holkner
# All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
#
#  * Redistributions of source code must retain the above copyright
#    notice, this list of conditions and the following disclaimer.
#  * Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in
#    the documentation and/or other materials provided with the
#    distribution.
#  * Neither the name of pyglet nor the names of its
#    contributors may be used to endorse or promote products
#    derived from this software without specific prior written
#    permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
# "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
# LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
# FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
# COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
# INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
# BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
# CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
# LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
# ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# ----------------------------------------------------------------------------

import ctypes
import ctypes.util
import glob
import os.path
import platform
import re
import sys


def _environ_path(name):
    """Split an environment variable into a path-like list elements"""
    if name in os.environ:
        return os.environ[name].split(":")
    return []


class LibraryLoader:
    """
    A base class For loading of libraries ;-)
    Subclasses load libraries for specific platforms.
    """

    # library names formatted specifically for platforms
    name_formats = ["%s"]

    class Lookup:
        """Looking up calling conventions for a platform"""

        mode = ctypes.DEFAULT_MODE

        def __init__(self, path):
            super(LibraryLoader.Lookup, self).__init__()
            self.access = dict(cdecl=ctypes.CDLL(path, self.mode))

        def get(self, name, calling_convention="cdecl"):
            """Return the given name according to the selected calling convention"""
            if calling_convention not in self.access:
                raise LookupError(
                    "Unknown calling convention '{}' for function '{}'".format(
                        calling_convention, name
                    )
                )
            return getattr(self.access[calling_convention], name)

        def has(self, name, calling_convention="cdecl"):
            """Return True if this given calling convention finds the given 'name'"""
            if calling_convention not in self.access:
                return False
            return hasattr(self.access[calling_convention], name)

        def __getattr__(self, name):
            return getattr(self.access["cdecl"], name)

    def __init__(self):
        self.other_dirs = []

    def __call__(self, libname):
        """Given the name of a library, load it."""
        paths = self.getpaths(libname)

        for path in paths:
            # noinspection PyBroadException
            try:
                return self.Lookup(path)
            except Exception:  # pylint: disable=broad-except
                pass

        raise ImportError("Could not load %s." % libname)

    def getpaths(self, libname):
        """Return a list of paths where the library might be found."""
        if os.path.isabs(libname):
            yield libname
        else:
            # search through a prioritized series of locations for the library

            # we first search any specific directories identified by user
            for dir_i in self.other_dirs:
                for fmt in self.name_formats:
                    # dir_i should be absolute already
                    yield os.path.join(dir_i, fmt % libname)

            # check if this code is even stored in a physical file
            try:
                this_file = __file__
            except NameError:
                this_file = None

            # then we search the directory where the generated python interface is stored
            if this_file is not None:
                for fmt in self.name_formats:
                    yield os.path.abspath(os.path.join(os.path.dirname(__file__), fmt % libname))

            # now, use the ctypes tools to try to find the library
            for fmt in self.name_formats:
                path = ctypes.util.find_library(fmt % libname)
                if path:
                    yield path

            # then we search all paths identified as platform-specific lib paths
            for path in self.getplatformpaths(libname):
                yield path

            # Finally, we'll try the users current working directory
            for fmt in self.name_formats:
                yield os.path.abspath(os.path.join(os.path.curdir, fmt % libname))

    def getplatformpaths(self, _libname):  # pylint: disable=no-self-use
        """Return all the library paths available in this platform"""
        return []


# Darwin (Mac OS X)


class DarwinLibraryLoader(LibraryLoader):
    """Library loader for MacOS"""

    name_formats = [
        "lib%s.dylib",
        "lib%s.so",
        "lib%s.bundle",
        "%s.dylib",
        "%s.so",
        "%s.bundle",
        "%s",
    ]

    class Lookup(LibraryLoader.Lookup):
        """
        Looking up library files for this platform (Darwin aka MacOS)
        """

        # Darwin requires dlopen to be called with mode RTLD_GLOBAL instead
        # of the default RTLD_LOCAL.  Without this, you end up with
        # libraries not being loadable, resulting in "Symbol not found"
        # errors
        mode = ctypes.RTLD_GLOBAL

    def getplatformpaths(self, libname):
        if os.path.pathsep in libname:
            names = [libname]
        else:
            names = [fmt % libname for fmt in self.name_formats]

        for directory in self.getdirs(libname):
            for name in names:
                yield os.path.join(directory, name)

    @staticmethod
    def getdirs(libname):
        """Implements the dylib search as specified in Apple documentation:

        http://developer.apple.com/documentation/DeveloperTools/Conceptual/
            DynamicLibraries/Articles/DynamicLibraryUsageGuidelines.html

        Before commencing the standard search, the method first checks
        the bundle's ``Frameworks`` directory if the application is running
        within a bundle (OS X .app).
        """

        dyld_fallback_library_path = _environ_path("DYLD_FALLBACK_LIBRARY_PATH")
        if not dyld_fallback_library_path:
            dyld_fallback_library_path = [
                os.path.expanduser("~/lib"),
                "/usr/local/lib",
                "/usr/lib",
            ]

        dirs = []

        if "/" in libname:
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))
        else:
            dirs.extend(_environ_path("LD_LIBRARY_PATH"))
            dirs.extend(_environ_path("DYLD_LIBRARY_PATH"))
            dirs.extend(_environ_path("LD_RUN_PATH"))

        if hasattr(sys, "frozen") and getattr(sys, "frozen") == "macosx_app":
            dirs.append(os.path.join(os.environ["RESOURCEPATH"], "..", "Frameworks"))

        dirs.extend(dyld_fallback_library_path)

        return dirs


# Posix


class PosixLibraryLoader(LibraryLoader):
    """Library loader for POSIX-like systems (including Linux)"""

    _ld_so_cache = None

    _include = re.compile(r"^\s*include\s+(?P<pattern>.*)")

    name_formats = ["lib%s.so", "%s.so", "%s"]

    class _Directories(dict):
        """Deal with directories"""

        def __init__(self):
            dict.__init__(self)
            self.order = 0

        def add(self, directory):
            """Add a directory to our current set of directories"""
            if len(directory) > 1:
                directory = directory.rstrip(os.path.sep)
            # only adds and updates order if exists and not already in set
            if not os.path.exists(directory):
                return
            order = self.setdefault(directory, self.order)
            if order == self.order:
                self.order += 1

        def extend(self, directories):
            """Add a list of directories to our set"""
            for a_dir in directories:
                self.add(a_dir)

        def ordered(self):
            """Sort the list of directories"""
            return (i[0] for i in sorted(self.items(), key=lambda d: d[1]))

    def _get_ld_so_conf_dirs(self, conf, dirs):
        """
        Recursive function to help parse all ld.so.conf files, including proper
        handling of the `include` directive.
        """

        try:
            with open(conf) as fileobj:
                for dirname in fileobj:
                    dirname = dirname.strip()
                    if not dirname:
                        continue

                    match = self._include.match(dirname)
                    if not match:
                        dirs.add(dirname)
                    else:
                        for dir2 in glob.glob(match.group("pattern")):
                            self._get_ld_so_conf_dirs(dir2, dirs)
        except IOError:
            pass

    def _create_ld_so_cache(self):
        # Recreate search path followed by ld.so.  This is going to be
        # slow to build, and incorrect (ld.so uses ld.so.cache, which may
        # not be up-to-date).  Used only as fallback for distros without
        # /sbin/ldconfig.
        #
        # We assume the DT_RPATH and DT_RUNPATH binary sections are omitted.

        directories = self._Directories()
        for name in (
            "LD_LIBRARY_PATH",
            "SHLIB_PATH",  # HP-UX
            "LIBPATH",  # OS/2, AIX
            "LIBRARY_PATH",  # BE/OS
        ):
            if name in os.environ:
                directories.extend(os.environ[name].split(os.pathsep))

        self._get_ld_so_conf_dirs("/etc/ld.so.conf", directories)

        bitage = platform.architecture()[0]

        unix_lib_dirs_list = []
        if bitage.startswith("64"):
            # prefer 64 bit if that is our arch
            unix_lib_dirs_list += ["/lib64", "/usr/lib64"]

        # must include standard libs, since those paths are also used by 64 bit
        # installs
        unix_lib_dirs_list += ["/lib", "/usr/lib"]
        if sys.platform.startswith("linux"):
            # Try and support multiarch work in Ubuntu
            # https://wiki.ubuntu.com/MultiarchSpec
            if bitage.startswith("32"):
                # Assume Intel/AMD x86 compat
                unix_lib_dirs_list += ["/lib/i386-linux-gnu", "/usr/lib/i386-linux-gnu"]
            elif bitage.startswith("64"):
                # Assume Intel/AMD x86 compatible
                unix_lib_dirs_list += [
                    "/lib/x86_64-linux-gnu",
                    "/usr/lib/x86_64-linux-gnu",
                ]
            else:
                # guess...
                unix_lib_dirs_list += glob.glob("/lib/*linux-gnu")
        directories.extend(unix_lib_dirs_list)

        cache = {}
        lib_re = re.compile(r"lib(.*)\.s[ol]")
        # ext_re = re.compile(r"\.s[ol]$")
        for our_dir in directories.ordered():
            try:
                for path in glob.glob("%s/*.s[ol]*" % our_dir):
                    file = os.path.basename(path)

                    # Index by filename
                    cache_i = cache.setdefault(file, set())
                    cache_i.add(path)

                    # Index by library name
                    match = lib_re.match(file)
                    if match:
                        library = match.group(1)
                        cache_i = cache.setdefault(library, set())
                        cache_i.add(path)
            except OSError:
                pass

        self._ld_so_cache = cache

    def getplatformpaths(self, libname):
        if self._ld_so_cache is None:
            self._create_ld_so_cache()

        result = self._ld_so_cache.get(libname, set())
        for i in result:
            # we iterate through all found paths for library, since we may have
            # actually found multiple architectures or other library types that
            # may not load
            yield i


# Windows


class WindowsLibraryLoader(LibraryLoader):
    """Library loader for Microsoft Windows"""

    name_formats = ["%s.dll", "lib%s.dll", "%slib.dll", "%s"]

    class Lookup(LibraryLoader.Lookup):
        """Lookup class for Windows libraries..."""

        def __init__(self, path):
            super(WindowsLibraryLoader.Lookup, self).__init__(path)
            self.access["stdcall"] = ctypes.windll.LoadLibrary(path)


# Platform switching

# If your value of sys.platform does not appear in this dict, please contact
# the Ctypesgen maintainers.

loaderclass = {
    "darwin": DarwinLibraryLoader,
    "cygwin": WindowsLibraryLoader,
    "win32": WindowsLibraryLoader,
    "msys": WindowsLibraryLoader,
}

load_library = loaderclass.get(sys.platform, PosixLibraryLoader)()


def add_library_search_dirs(other_dirs):
    """
    Add libraries to search paths.
    If library paths are relative, convert them to absolute with respect to this
    file's directory
    """
    for path in other_dirs:
        if not os.path.isabs(path):
            path = os.path.abspath(path)
        load_library.other_dirs.append(path)


del loaderclass

# End loader

add_library_search_dirs([])

# Begin libraries
_libs["panosui"] = load_library("panosui")

# 1 libraries
# End libraries

# No modules

UIFloat = c_float# /usr/local/include/UIGeometry.h: 5

# /usr/local/include/UIGeometry.h: 10
class struct__UIPoint(Structure):
    pass

struct__UIPoint.__slots__ = [
    'x',
    'y',
]
struct__UIPoint._fields_ = [
    ('x', UIFloat),
    ('y', UIFloat),
]

UIPoint = struct__UIPoint# /usr/local/include/UIGeometry.h: 10

# /usr/local/include/UIGeometry.h: 15
class struct__UISize(Structure):
    pass

struct__UISize.__slots__ = [
    'width',
    'height',
]
struct__UISize._fields_ = [
    ('width', UIFloat),
    ('height', UIFloat),
]

UISize = struct__UISize# /usr/local/include/UIGeometry.h: 15

# /usr/local/include/UIGeometry.h: 21
class struct__UIRect(Structure):
    pass

struct__UIRect.__slots__ = [
    'origin',
    'size',
]
struct__UIRect._fields_ = [
    ('origin', UIPoint),
    ('size', UISize),
]

UIRect = struct__UIRect# /usr/local/include/UIGeometry.h: 21

# /usr/local/include/UIGeometry.h: 24
if _libs["panosui"].has("UIRectCreate", "cdecl"):
    UIRectCreate = _libs["panosui"].get("UIRectCreate", "cdecl")
    UIRectCreate.argtypes = [UIFloat, UIFloat, UIFloat, UIFloat]
    UIRectCreate.restype = UIRect

# /usr/local/include/UIGeometry.h: 25
if _libs["panosui"].has("UIRectGetWidth", "cdecl"):
    UIRectGetWidth = _libs["panosui"].get("UIRectGetWidth", "cdecl")
    UIRectGetWidth.argtypes = [UIRect]
    UIRectGetWidth.restype = UIFloat

# /usr/local/include/UIGeometry.h: 26
if _libs["panosui"].has("UIRectGetHeight", "cdecl"):
    UIRectGetHeight = _libs["panosui"].get("UIRectGetHeight", "cdecl")
    UIRectGetHeight.argtypes = [UIRect]
    UIRectGetHeight.restype = UIFloat

# /usr/local/include/UIGeometry.h: 27
if _libs["panosui"].has("UIRectGetMinX", "cdecl"):
    UIRectGetMinX = _libs["panosui"].get("UIRectGetMinX", "cdecl")
    UIRectGetMinX.argtypes = [UIRect]
    UIRectGetMinX.restype = UIFloat

# /usr/local/include/UIGeometry.h: 28
if _libs["panosui"].has("UIRectGetMinY", "cdecl"):
    UIRectGetMinY = _libs["panosui"].get("UIRectGetMinY", "cdecl")
    UIRectGetMinY.argtypes = [UIRect]
    UIRectGetMinY.restype = UIFloat

# /usr/local/include/UIGeometry.h: 29
if _libs["panosui"].has("UIRectGetMaxX", "cdecl"):
    UIRectGetMaxX = _libs["panosui"].get("UIRectGetMaxX", "cdecl")
    UIRectGetMaxX.argtypes = [UIRect]
    UIRectGetMaxX.restype = UIFloat

# /usr/local/include/UIGeometry.h: 30
if _libs["panosui"].has("UIRectGetMaxY", "cdecl"):
    UIRectGetMaxY = _libs["panosui"].get("UIRectGetMaxY", "cdecl")
    UIRectGetMaxY.argtypes = [UIRect]
    UIRectGetMaxY.restype = UIFloat

# /usr/local/include/UIGeometry.h: 31
if _libs["panosui"].has("UIRectGetMidX", "cdecl"):
    UIRectGetMidX = _libs["panosui"].get("UIRectGetMidX", "cdecl")
    UIRectGetMidX.argtypes = [UIRect]
    UIRectGetMidX.restype = UIFloat

# /usr/local/include/UIGeometry.h: 32
if _libs["panosui"].has("UIRectGetMidY", "cdecl"):
    UIRectGetMidY = _libs["panosui"].get("UIRectGetMidY", "cdecl")
    UIRectGetMidY.argtypes = [UIRect]
    UIRectGetMidY.restype = UIFloat

# /usr/local/include/UIGeometry.h: 33
if _libs["panosui"].has("UIRectInset", "cdecl"):
    UIRectInset = _libs["panosui"].get("UIRectInset", "cdecl")
    UIRectInset.argtypes = [UIRect, UIFloat, UIFloat]
    UIRectInset.restype = UIRect

# /usr/local/include/UIGeometry.h: 34
if _libs["panosui"].has("UIRectOutset", "cdecl"):
    UIRectOutset = _libs["panosui"].get("UIRectOutset", "cdecl")
    UIRectOutset.argtypes = [UIRect, UIFloat, UIFloat]
    UIRectOutset.restype = UIRect

# /usr/local/include/UIGeometry.h: 37
if _libs["panosui"].has("UIPointCreate", "cdecl"):
    UIPointCreate = _libs["panosui"].get("UIPointCreate", "cdecl")
    UIPointCreate.argtypes = [UIFloat, UIFloat]
    UIPointCreate.restype = UIPoint

# /usr/local/include/UIGeometry.h: 38
if _libs["panosui"].has("UIPointOffset", "cdecl"):
    UIPointOffset = _libs["panosui"].get("UIPointOffset", "cdecl")
    UIPointOffset.argtypes = [UIPoint, UIFloat, UIFloat]
    UIPointOffset.restype = UIPoint

# /usr/local/include/UIGeometry.h: 39
if _libs["panosui"].has("UIPointInRect", "cdecl"):
    UIPointInRect = _libs["panosui"].get("UIPointInRect", "cdecl")
    UIPointInRect.argtypes = [UIPoint, UIRect]
    UIPointInRect.restype = c_bool

__uint64_t = c_ulong# /usr/include/bits/types.h: 45

uint64_t = __uint64_t# /usr/include/bits/stdint-uintn.h: 27

# /usr/local/include/UIAnimation.h: 20
class struct__UIAnimation(Structure):
    pass

struct__UIAnimation.__slots__ = [
    'finished',
    'forKey',
    'duration',
    'timingFunction',
    'startValue',
    'endValue',
    '_valueSize',
    'startTime',
    'endTime',
]
struct__UIAnimation._fields_ = [
    ('finished', c_int),
    ('forKey', String),
    ('duration', c_int),
    ('timingFunction', CFUNCTYPE(UNCHECKED(UIFloat), UIFloat)),
    ('startValue', POINTER(None)),
    ('endValue', POINTER(None)),
    ('_valueSize', c_size_t),
    ('startTime', uint64_t),
    ('endTime', uint64_t),
]

UIAnimation = struct__UIAnimation# /usr/local/include/UIAnimation.h: 20

# /usr/local/include/UIAnimation.h: 27
class struct__UITransaction(Structure):
    pass

struct__UITransaction.__slots__ = [
    'duration',
    'timingFunction',
]
struct__UITransaction._fields_ = [
    ('duration', uint64_t),
    ('timingFunction', CFUNCTYPE(UNCHECKED(UIFloat), UIFloat)),
]

UITransaction = struct__UITransaction# /usr/local/include/UIAnimation.h: 27

# /usr/local/include/UIAnimation.h: 29
if _libs["panosui"].has("UIAnimationGetCurrentTime", "cdecl"):
    UIAnimationGetCurrentTime = _libs["panosui"].get("UIAnimationGetCurrentTime", "cdecl")
    UIAnimationGetCurrentTime.argtypes = []
    UIAnimationGetCurrentTime.restype = uint64_t

# /usr/local/include/UIAnimation.h: 31
if _libs["panosui"].has("UIAnimationCopy", "cdecl"):
    UIAnimationCopy = _libs["panosui"].get("UIAnimationCopy", "cdecl")
    UIAnimationCopy.argtypes = [UIAnimation]
    UIAnimationCopy.restype = UIAnimation

# /usr/local/include/UIAnimation.h: 32
if _libs["panosui"].has("UIAnimationDestroy", "cdecl"):
    UIAnimationDestroy = _libs["panosui"].get("UIAnimationDestroy", "cdecl")
    UIAnimationDestroy.argtypes = [UIAnimation]
    UIAnimationDestroy.restype = None

# /usr/local/include/UIAnimation.h: 34
if _libs["panosui"].has("UIAnimationTransactionBegin", "cdecl"):
    UIAnimationTransactionBegin = _libs["panosui"].get("UIAnimationTransactionBegin", "cdecl")
    UIAnimationTransactionBegin.argtypes = []
    UIAnimationTransactionBegin.restype = None

# /usr/local/include/UIAnimation.h: 35
if _libs["panosui"].has("UIAnimationTransactionSetDuration", "cdecl"):
    UIAnimationTransactionSetDuration = _libs["panosui"].get("UIAnimationTransactionSetDuration", "cdecl")
    UIAnimationTransactionSetDuration.argtypes = [uint64_t]
    UIAnimationTransactionSetDuration.restype = None

# /usr/local/include/UIAnimation.h: 36
if _libs["panosui"].has("UIAnimationTransactionEnd", "cdecl"):
    UIAnimationTransactionEnd = _libs["panosui"].get("UIAnimationTransactionEnd", "cdecl")
    UIAnimationTransactionEnd.argtypes = []
    UIAnimationTransactionEnd.restype = None

# /usr/local/include/UIAnimation.h: 37
if _libs["panosui"].has("UIAnimationTransactionFlush", "cdecl"):
    UIAnimationTransactionFlush = _libs["panosui"].get("UIAnimationTransactionFlush", "cdecl")
    UIAnimationTransactionFlush.argtypes = []
    UIAnimationTransactionFlush.restype = None

# /usr/local/include/UIAnimation.h: 39
for _lib in _libs.values():
    if not _lib.has("UIAnimationCoreTick", "cdecl"):
        continue
    UIAnimationCoreTick = _lib.get("UIAnimationCoreTick", "cdecl")
    UIAnimationCoreTick.argtypes = []
    UIAnimationCoreTick.restype = None
    break

# /usr/local/include/UIAnimation.h: 42
if _libs["panosui"].has("UIAnimationTimingFunctionLinear", "cdecl"):
    UIAnimationTimingFunctionLinear = _libs["panosui"].get("UIAnimationTimingFunctionLinear", "cdecl")
    UIAnimationTimingFunctionLinear.argtypes = [UIFloat]
    UIAnimationTimingFunctionLinear.restype = UIFloat

# /usr/local/include/UIAnimation.h: 43
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInSine", "cdecl"):
    UIAnimationTimingFunctionEaseInSine = _libs["panosui"].get("UIAnimationTimingFunctionEaseInSine", "cdecl")
    UIAnimationTimingFunctionEaseInSine.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInSine.restype = UIFloat

# /usr/local/include/UIAnimation.h: 44
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutSine", "cdecl"):
    UIAnimationTimingFunctionEaseOutSine = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutSine", "cdecl")
    UIAnimationTimingFunctionEaseOutSine.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutSine.restype = UIFloat

# /usr/local/include/UIAnimation.h: 45
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutSine", "cdecl"):
    UIAnimationTimingFunctionEaseInOutSine = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutSine", "cdecl")
    UIAnimationTimingFunctionEaseInOutSine.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutSine.restype = UIFloat

# /usr/local/include/UIAnimation.h: 46
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInQuad", "cdecl"):
    UIAnimationTimingFunctionEaseInQuad = _libs["panosui"].get("UIAnimationTimingFunctionEaseInQuad", "cdecl")
    UIAnimationTimingFunctionEaseInQuad.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInQuad.restype = UIFloat

# /usr/local/include/UIAnimation.h: 47
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutQuad", "cdecl"):
    UIAnimationTimingFunctionEaseOutQuad = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutQuad", "cdecl")
    UIAnimationTimingFunctionEaseOutQuad.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutQuad.restype = UIFloat

# /usr/local/include/UIAnimation.h: 48
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutQuad", "cdecl"):
    UIAnimationTimingFunctionEaseInOutQuad = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutQuad", "cdecl")
    UIAnimationTimingFunctionEaseInOutQuad.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutQuad.restype = UIFloat

# /usr/local/include/UIAnimation.h: 49
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInCubic", "cdecl"):
    UIAnimationTimingFunctionEaseInCubic = _libs["panosui"].get("UIAnimationTimingFunctionEaseInCubic", "cdecl")
    UIAnimationTimingFunctionEaseInCubic.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInCubic.restype = UIFloat

# /usr/local/include/UIAnimation.h: 50
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutCubic", "cdecl"):
    UIAnimationTimingFunctionEaseOutCubic = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutCubic", "cdecl")
    UIAnimationTimingFunctionEaseOutCubic.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutCubic.restype = UIFloat

# /usr/local/include/UIAnimation.h: 51
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutCubic", "cdecl"):
    UIAnimationTimingFunctionEaseInOutCubic = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutCubic", "cdecl")
    UIAnimationTimingFunctionEaseInOutCubic.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutCubic.restype = UIFloat

# /usr/local/include/UIAnimation.h: 52
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInQuart", "cdecl"):
    UIAnimationTimingFunctionEaseInQuart = _libs["panosui"].get("UIAnimationTimingFunctionEaseInQuart", "cdecl")
    UIAnimationTimingFunctionEaseInQuart.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInQuart.restype = UIFloat

# /usr/local/include/UIAnimation.h: 53
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutQuart", "cdecl"):
    UIAnimationTimingFunctionEaseOutQuart = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutQuart", "cdecl")
    UIAnimationTimingFunctionEaseOutQuart.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutQuart.restype = UIFloat

# /usr/local/include/UIAnimation.h: 54
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutQuart", "cdecl"):
    UIAnimationTimingFunctionEaseInOutQuart = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutQuart", "cdecl")
    UIAnimationTimingFunctionEaseInOutQuart.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutQuart.restype = UIFloat

# /usr/local/include/UIAnimation.h: 55
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInQuint", "cdecl"):
    UIAnimationTimingFunctionEaseInQuint = _libs["panosui"].get("UIAnimationTimingFunctionEaseInQuint", "cdecl")
    UIAnimationTimingFunctionEaseInQuint.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInQuint.restype = UIFloat

# /usr/local/include/UIAnimation.h: 56
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutQuint", "cdecl"):
    UIAnimationTimingFunctionEaseOutQuint = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutQuint", "cdecl")
    UIAnimationTimingFunctionEaseOutQuint.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutQuint.restype = UIFloat

# /usr/local/include/UIAnimation.h: 57
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutQuint", "cdecl"):
    UIAnimationTimingFunctionEaseInOutQuint = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutQuint", "cdecl")
    UIAnimationTimingFunctionEaseInOutQuint.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutQuint.restype = UIFloat

# /usr/local/include/UIAnimation.h: 58
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInExpo", "cdecl"):
    UIAnimationTimingFunctionEaseInExpo = _libs["panosui"].get("UIAnimationTimingFunctionEaseInExpo", "cdecl")
    UIAnimationTimingFunctionEaseInExpo.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInExpo.restype = UIFloat

# /usr/local/include/UIAnimation.h: 59
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutExpo", "cdecl"):
    UIAnimationTimingFunctionEaseOutExpo = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutExpo", "cdecl")
    UIAnimationTimingFunctionEaseOutExpo.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutExpo.restype = UIFloat

# /usr/local/include/UIAnimation.h: 60
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutExpo", "cdecl"):
    UIAnimationTimingFunctionEaseInOutExpo = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutExpo", "cdecl")
    UIAnimationTimingFunctionEaseInOutExpo.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutExpo.restype = UIFloat

# /usr/local/include/UIAnimation.h: 61
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInCirc", "cdecl"):
    UIAnimationTimingFunctionEaseInCirc = _libs["panosui"].get("UIAnimationTimingFunctionEaseInCirc", "cdecl")
    UIAnimationTimingFunctionEaseInCirc.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInCirc.restype = UIFloat

# /usr/local/include/UIAnimation.h: 62
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutCirc", "cdecl"):
    UIAnimationTimingFunctionEaseOutCirc = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutCirc", "cdecl")
    UIAnimationTimingFunctionEaseOutCirc.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutCirc.restype = UIFloat

# /usr/local/include/UIAnimation.h: 63
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutCirc", "cdecl"):
    UIAnimationTimingFunctionEaseInOutCirc = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutCirc", "cdecl")
    UIAnimationTimingFunctionEaseInOutCirc.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutCirc.restype = UIFloat

# /usr/local/include/UIAnimation.h: 64
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInBack", "cdecl"):
    UIAnimationTimingFunctionEaseInBack = _libs["panosui"].get("UIAnimationTimingFunctionEaseInBack", "cdecl")
    UIAnimationTimingFunctionEaseInBack.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInBack.restype = UIFloat

# /usr/local/include/UIAnimation.h: 65
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutBack", "cdecl"):
    UIAnimationTimingFunctionEaseOutBack = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutBack", "cdecl")
    UIAnimationTimingFunctionEaseOutBack.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutBack.restype = UIFloat

# /usr/local/include/UIAnimation.h: 66
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutBack", "cdecl"):
    UIAnimationTimingFunctionEaseInOutBack = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutBack", "cdecl")
    UIAnimationTimingFunctionEaseInOutBack.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutBack.restype = UIFloat

# /usr/local/include/UIAnimation.h: 67
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInElastic", "cdecl"):
    UIAnimationTimingFunctionEaseInElastic = _libs["panosui"].get("UIAnimationTimingFunctionEaseInElastic", "cdecl")
    UIAnimationTimingFunctionEaseInElastic.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInElastic.restype = UIFloat

# /usr/local/include/UIAnimation.h: 68
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutElastic", "cdecl"):
    UIAnimationTimingFunctionEaseOutElastic = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutElastic", "cdecl")
    UIAnimationTimingFunctionEaseOutElastic.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutElastic.restype = UIFloat

# /usr/local/include/UIAnimation.h: 69
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutElastic", "cdecl"):
    UIAnimationTimingFunctionEaseInOutElastic = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutElastic", "cdecl")
    UIAnimationTimingFunctionEaseInOutElastic.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutElastic.restype = UIFloat

# /usr/local/include/UIAnimation.h: 70
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInBounce", "cdecl"):
    UIAnimationTimingFunctionEaseInBounce = _libs["panosui"].get("UIAnimationTimingFunctionEaseInBounce", "cdecl")
    UIAnimationTimingFunctionEaseInBounce.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInBounce.restype = UIFloat

# /usr/local/include/UIAnimation.h: 71
if _libs["panosui"].has("UIAnimationTimingFunctionEaseOutBounce", "cdecl"):
    UIAnimationTimingFunctionEaseOutBounce = _libs["panosui"].get("UIAnimationTimingFunctionEaseOutBounce", "cdecl")
    UIAnimationTimingFunctionEaseOutBounce.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseOutBounce.restype = UIFloat

# /usr/local/include/UIAnimation.h: 72
if _libs["panosui"].has("UIAnimationTimingFunctionEaseInOutBounce", "cdecl"):
    UIAnimationTimingFunctionEaseInOutBounce = _libs["panosui"].get("UIAnimationTimingFunctionEaseInOutBounce", "cdecl")
    UIAnimationTimingFunctionEaseInOutBounce.argtypes = [UIFloat]
    UIAnimationTimingFunctionEaseInOutBounce.restype = UIFloat

# /usr/local/include/UIApplication.h: 7
class struct__UIApplication(Structure):
    pass

struct__UIApplication.__slots__ = [
    'running',
]
struct__UIApplication._fields_ = [
    ('running', c_int),
]

UIApplication = struct__UIApplication# /usr/local/include/UIApplication.h: 7

# /usr/local/include/UIApplication.h: 12
class struct__UIApplicationDelegate(Structure):
    pass

struct__UIApplicationDelegate.__slots__ = [
    'didFinishLaunching',
]
struct__UIApplicationDelegate._fields_ = [
    ('didFinishLaunching', CFUNCTYPE(UNCHECKED(None), POINTER(UIApplication))),
]

UIApplicationDelegate = struct__UIApplicationDelegate# /usr/local/include/UIApplication.h: 12

# /usr/local/include/UIApplication.h: 14
if _libs["panosui"].has("UIApplicationMain", "cdecl"):
    UIApplicationMain = _libs["panosui"].get("UIApplicationMain", "cdecl")
    UIApplicationMain.argtypes = [POINTER(UIApplicationDelegate)]
    UIApplicationMain.restype = None

# /usr/local/include/UIApplication.h: 15
if _libs["panosui"].has("UIApplicationShared", "cdecl"):
    UIApplicationShared = _libs["panosui"].get("UIApplicationShared", "cdecl")
    UIApplicationShared.argtypes = []
    UIApplicationShared.restype = POINTER(UIApplication)

# /usr/local/include/UIColor.h: 3
class struct__UIColor(Structure):
    pass

UIColor = struct__UIColor# /usr/local/include/UIColor.h: 3

# /usr/local/include/UIColor.h: 5
if _libs["panosui"].has("UIColorCreateRGBA", "cdecl"):
    UIColorCreateRGBA = _libs["panosui"].get("UIColorCreateRGBA", "cdecl")
    UIColorCreateRGBA.argtypes = [c_int, c_int, c_int, c_int]
    UIColorCreateRGBA.restype = POINTER(UIColor)

# /usr/local/include/UIColor.h: 6
if _libs["panosui"].has("UIColorDestroy", "cdecl"):
    UIColorDestroy = _libs["panosui"].get("UIColorDestroy", "cdecl")
    UIColorDestroy.argtypes = [POINTER(UIColor)]
    UIColorDestroy.restype = None

# /usr/local/include/UILayer.h: 7
try:
    kUILayerKeyPositionX = (String).in_dll(_libs["panosui"], "kUILayerKeyPositionX")
except:
    pass

# /usr/local/include/UILayer.h: 8
try:
    kUILayerKeyPositionY = (String).in_dll(_libs["panosui"], "kUILayerKeyPositionY")
except:
    pass

# /usr/local/include/UILayer.h: 10
try:
    kUILayerKeyBoundsWidth = (String).in_dll(_libs["panosui"], "kUILayerKeyBoundsWidth")
except:
    pass

# /usr/local/include/UILayer.h: 11
try:
    kUILayerKeyBoundsHeight = (String).in_dll(_libs["panosui"], "kUILayerKeyBoundsHeight")
except:
    pass

# /usr/local/include/UILayer.h: 13
try:
    kUILayerKeyBackgroundColor = (String).in_dll(_libs["panosui"], "kUILayerKeyBackgroundColor")
except:
    pass

# /usr/local/include/UILayer.h: 15
try:
    kUILayerKeyBorderWidth = (String).in_dll(_libs["panosui"], "kUILayerKeyBorderWidth")
except:
    pass

# /usr/local/include/UILayer.h: 16
try:
    kUILayerKeyBorderColor = (String).in_dll(_libs["panosui"], "kUILayerKeyBorderColor")
except:
    pass

# /usr/local/include/UILayer.h: 18
try:
    kUILayerKeyShadowOffset = (String).in_dll(_libs["panosui"], "kUILayerKeyShadowOffset")
except:
    pass

# /usr/local/include/UILayer.h: 19
try:
    kUILayerKeyShadowColor = (String).in_dll(_libs["panosui"], "kUILayerKeyShadowColor")
except:
    pass

# /usr/local/include/UILayer.h: 20
try:
    kUILayerKeyShadowRadius = (String).in_dll(_libs["panosui"], "kUILayerKeyShadowRadius")
except:
    pass

# /usr/local/include/UILayer.h: 22
try:
    kUILayerKeyCornerRadius = (String).in_dll(_libs["panosui"], "kUILayerKeyCornerRadius")
except:
    pass

# /usr/local/include/UILayer.h: 23
try:
    kUILayerKeyOpacity = (String).in_dll(_libs["panosui"], "kUILayerKeyOpacity")
except:
    pass

# /usr/local/include/UILayer.h: 25
class struct__UILayer(Structure):
    pass

UILayer = struct__UILayer# /usr/local/include/UILayer.h: 25

# /usr/local/include/UILayer.h: 27
if _libs["panosui"].has("UILayerCreate", "cdecl"):
    UILayerCreate = _libs["panosui"].get("UILayerCreate", "cdecl")
    UILayerCreate.argtypes = [UIRect, UIRect]
    UILayerCreate.restype = POINTER(UILayer)

# /usr/local/include/UILayer.h: 28
for _lib in _libs.values():
    if not _lib.has("UILayerDestroy", "cdecl"):
        continue
    UILayerDestroy = _lib.get("UILayerDestroy", "cdecl")
    UILayerDestroy.argtypes = [POINTER(UILayer)]
    UILayerDestroy.restype = None
    break

# /usr/local/include/UILayer.h: 31
if _libs["panosui"].has("UILayerSetBounds", "cdecl"):
    UILayerSetBounds = _libs["panosui"].get("UILayerSetBounds", "cdecl")
    UILayerSetBounds.argtypes = [POINTER(UILayer), UIRect]
    UILayerSetBounds.restype = None

# /usr/local/include/UILayer.h: 32
if _libs["panosui"].has("UILayerSetPosition", "cdecl"):
    UILayerSetPosition = _libs["panosui"].get("UILayerSetPosition", "cdecl")
    UILayerSetPosition.argtypes = [POINTER(UILayer), UIPoint]
    UILayerSetPosition.restype = None

# /usr/local/include/UILayer.h: 33
if _libs["panosui"].has("UILayerSetAnchorPoint", "cdecl"):
    UILayerSetAnchorPoint = _libs["panosui"].get("UILayerSetAnchorPoint", "cdecl")
    UILayerSetAnchorPoint.argtypes = [POINTER(UILayer), UIPoint]
    UILayerSetAnchorPoint.restype = None

# /usr/local/include/UILayer.h: 36
if _libs["panosui"].has("UILayerGetFrame", "cdecl"):
    UILayerGetFrame = _libs["panosui"].get("UILayerGetFrame", "cdecl")
    UILayerGetFrame.argtypes = [POINTER(UILayer)]
    UILayerGetFrame.restype = UIRect

# /usr/local/include/UILayer.h: 37
if _libs["panosui"].has("UILayerGetBounds", "cdecl"):
    UILayerGetBounds = _libs["panosui"].get("UILayerGetBounds", "cdecl")
    UILayerGetBounds.argtypes = [POINTER(UILayer)]
    UILayerGetBounds.restype = UIRect

# /usr/local/include/UILayer.h: 38
if _libs["panosui"].has("UILayerGetPosition", "cdecl"):
    UILayerGetPosition = _libs["panosui"].get("UILayerGetPosition", "cdecl")
    UILayerGetPosition.argtypes = [POINTER(UILayer)]
    UILayerGetPosition.restype = UIPoint

# /usr/local/include/UILayer.h: 39
if _libs["panosui"].has("UILayerGetAnchorPoint", "cdecl"):
    UILayerGetAnchorPoint = _libs["panosui"].get("UILayerGetAnchorPoint", "cdecl")
    UILayerGetAnchorPoint.argtypes = [POINTER(UILayer)]
    UILayerGetAnchorPoint.restype = UIPoint

# /usr/local/include/UILayer.h: 42
if _libs["panosui"].has("UILayerAddAnimation", "cdecl"):
    UILayerAddAnimation = _libs["panosui"].get("UILayerAddAnimation", "cdecl")
    UILayerAddAnimation.argtypes = [POINTER(UILayer), UIAnimation]
    UILayerAddAnimation.restype = None

# /usr/local/include/UILayer.h: 43
if _libs["panosui"].has("UILayerGetAnimationFor", "cdecl"):
    UILayerGetAnimationFor = _libs["panosui"].get("UILayerGetAnimationFor", "cdecl")
    UILayerGetAnimationFor.argtypes = [POINTER(UILayer), String, c_size_t, POINTER(None), POINTER(None)]
    UILayerGetAnimationFor.restype = UIAnimation

# /usr/local/include/UILayer.h: 46
if _libs["panosui"].has("UILayerAddSublayer", "cdecl"):
    UILayerAddSublayer = _libs["panosui"].get("UILayerAddSublayer", "cdecl")
    UILayerAddSublayer.argtypes = [POINTER(UILayer), POINTER(UILayer)]
    UILayerAddSublayer.restype = None

# /usr/local/include/UILayer.h: 47
if _libs["panosui"].has("UILayerRemoveSublayer", "cdecl"):
    UILayerRemoveSublayer = _libs["panosui"].get("UILayerRemoveSublayer", "cdecl")
    UILayerRemoveSublayer.argtypes = [POINTER(UILayer), POINTER(UILayer)]
    UILayerRemoveSublayer.restype = None

enum_UIEventResponderCallback = c_int# /usr/local/include/UIEventResponder.h: 3

UIEventResponderLeftMouseDown = 0# /usr/local/include/UIEventResponder.h: 3

UIEventResponderLeftMouseUp = (UIEventResponderLeftMouseDown + 1)# /usr/local/include/UIEventResponder.h: 3

UIEventResponderRightMouseDown = (UIEventResponderLeftMouseUp + 1)# /usr/local/include/UIEventResponder.h: 3

UIEventResponderRightMouseUp = (UIEventResponderRightMouseDown + 1)# /usr/local/include/UIEventResponder.h: 3

UIEventResponderMouseMove = (UIEventResponderRightMouseUp + 1)# /usr/local/include/UIEventResponder.h: 3

UIEventResponderMouseScroll = (UIEventResponderMouseMove + 1)# /usr/local/include/UIEventResponder.h: 3

# /usr/local/include/UIEventResponder.h: 13
class struct__UIEventResponder(Structure):
    pass

UIEventResponder = struct__UIEventResponder# /usr/local/include/UIEventResponder.h: 13

# /usr/local/include/UIEventResponder.h: 15
if _libs["panosui"].has("UIEventResponderCreate", "cdecl"):
    UIEventResponderCreate = _libs["panosui"].get("UIEventResponderCreate", "cdecl")
    UIEventResponderCreate.argtypes = []
    UIEventResponderCreate.restype = POINTER(UIEventResponder)

# /usr/local/include/UIEventResponder.h: 16
if _libs["panosui"].has("UIEventResponderDestroy", "cdecl"):
    UIEventResponderDestroy = _libs["panosui"].get("UIEventResponderDestroy", "cdecl")
    UIEventResponderDestroy.argtypes = [POINTER(UIEventResponder)]
    UIEventResponderDestroy.restype = None

# /usr/local/include/UIView.h: 12
class struct__UIView(Structure):
    pass

UIView = struct__UIView# /usr/local/include/UIView.h: 12

# /usr/local/include/UIView.h: 21
if _libs["panosui"].has("UIViewCreate", "cdecl"):
    UIViewCreate = _libs["panosui"].get("UIViewCreate", "cdecl")
    UIViewCreate.argtypes = [UIRect, UIRect]
    UIViewCreate.restype = POINTER(UIView)

# /usr/local/include/UIView.h: 27
if _libs["panosui"].has("UIViewDestroy", "cdecl"):
    UIViewDestroy = _libs["panosui"].get("UIViewDestroy", "cdecl")
    UIViewDestroy.argtypes = [POINTER(UIView)]
    UIViewDestroy.restype = None

# /usr/local/include/UIView.h: 35
if _libs["panosui"].has("UIViewAddSubview", "cdecl"):
    UIViewAddSubview = _libs["panosui"].get("UIViewAddSubview", "cdecl")
    UIViewAddSubview.argtypes = [POINTER(UIView), POINTER(UIView)]
    UIViewAddSubview.restype = None

# /usr/local/include/UIView.h: 42
if _libs["panosui"].has("UIViewRemoveSubview", "cdecl"):
    UIViewRemoveSubview = _libs["panosui"].get("UIViewRemoveSubview", "cdecl")
    UIViewRemoveSubview.argtypes = [POINTER(UIView), POINTER(UIView)]
    UIViewRemoveSubview.restype = None

# /usr/local/include/UIView.h: 44
if _libs["panosui"].has("UIViewConvertPoint", "cdecl"):
    UIViewConvertPoint = _libs["panosui"].get("UIViewConvertPoint", "cdecl")
    UIViewConvertPoint.argtypes = [POINTER(UIView), POINTER(UIView), UIPoint]
    UIViewConvertPoint.restype = UIPoint

# /usr/local/include/UIView.h: 45
if _libs["panosui"].has("UIViewHitTest", "cdecl"):
    UIViewHitTest = _libs["panosui"].get("UIViewHitTest", "cdecl")
    UIViewHitTest.argtypes = [POINTER(UIView), UIPoint]
    UIViewHitTest.restype = POINTER(UIView)

# /usr/local/include/UIView.h: 48
if _libs["panosui"].has("UIViewGetLayer", "cdecl"):
    UIViewGetLayer = _libs["panosui"].get("UIViewGetLayer", "cdecl")
    UIViewGetLayer.argtypes = [POINTER(UIView)]
    UIViewGetLayer.restype = POINTER(UILayer)

# /usr/local/include/UIView.h: 49
if _libs["panosui"].has("UIViewSetLayer", "cdecl"):
    UIViewSetLayer = _libs["panosui"].get("UIViewSetLayer", "cdecl")
    UIViewSetLayer.argtypes = [POINTER(UIView), POINTER(UILayer)]
    UIViewSetLayer.restype = None

# /usr/local/include/UIView.h: 52
for _lib in _libs.values():
    if not _lib.has("UIViewGetResponder", "cdecl"):
        continue
    UIViewGetResponder = _lib.get("UIViewGetResponder", "cdecl")
    UIViewGetResponder.argtypes = [POINTER(UIView)]
    UIViewGetResponder.restype = POINTER(UIEventResponder)
    break

# /usr/local/include/UIView.h: 53
for _lib in _libs.values():
    if not _lib.has("UIViewSetResponder", "cdecl"):
        continue
    UIViewSetResponder = _lib.get("UIViewSetResponder", "cdecl")
    UIViewSetResponder.argtypes = [POINTER(UIView), POINTER(UIEventResponder)]
    UIViewSetResponder.restype = None
    break

# /usr/local/include/UIView.h: 56
if _libs["panosui"].has("UIViewGetFrame", "cdecl"):
    UIViewGetFrame = _libs["panosui"].get("UIViewGetFrame", "cdecl")
    UIViewGetFrame.argtypes = [POINTER(UIView)]
    UIViewGetFrame.restype = UIRect

# /usr/local/include/UIView.h: 57
if _libs["panosui"].has("UIViewSetFrame", "cdecl"):
    UIViewSetFrame = _libs["panosui"].get("UIViewSetFrame", "cdecl")
    UIViewSetFrame.argtypes = [POINTER(UIView), UIRect]
    UIViewSetFrame.restype = None

# /usr/local/include/UIView.h: 60
if _libs["panosui"].has("UIViewGetBounds", "cdecl"):
    UIViewGetBounds = _libs["panosui"].get("UIViewGetBounds", "cdecl")
    UIViewGetBounds.argtypes = [POINTER(UIView)]
    UIViewGetBounds.restype = UIRect

# /usr/local/include/UIView.h: 61
if _libs["panosui"].has("UIViewSetBounds", "cdecl"):
    UIViewSetBounds = _libs["panosui"].get("UIViewSetBounds", "cdecl")
    UIViewSetBounds.argtypes = [POINTER(UIView), UIRect]
    UIViewSetBounds.restype = None

# /usr/local/include/UIView.h: 64
for _lib in _libs.values():
    if not _lib.has("UIViewGetParentView", "cdecl"):
        continue
    UIViewGetParentView = _lib.get("UIViewGetParentView", "cdecl")
    UIViewGetParentView.argtypes = [POINTER(UIView)]
    UIViewGetParentView.restype = POINTER(UIView)
    break

# /usr/local/include/UIView.h: 65
for _lib in _libs.values():
    if not _lib.has("UIViewSetParentView", "cdecl"):
        continue
    UIViewSetParentView = _lib.get("UIViewSetParentView", "cdecl")
    UIViewSetParentView.argtypes = [POINTER(UIView), POINTER(UIView)]
    UIViewSetParentView.restype = None
    break

# /usr/local/include/UIView.h: 68
for _lib in _libs.values():
    if not _lib.has("UIViewGetNeedsDisplay", "cdecl"):
        continue
    UIViewGetNeedsDisplay = _lib.get("UIViewGetNeedsDisplay", "cdecl")
    UIViewGetNeedsDisplay.argtypes = [POINTER(UIView)]
    UIViewGetNeedsDisplay.restype = c_bool
    break

# /usr/local/include/UIView.h: 69
if _libs["panosui"].has("UIViewSetNeedsDisplay", "cdecl"):
    UIViewSetNeedsDisplay = _libs["panosui"].get("UIViewSetNeedsDisplay", "cdecl")
    UIViewSetNeedsDisplay.argtypes = [POINTER(UIView)]
    UIViewSetNeedsDisplay.restype = None

# /usr/local/include/UIView.h: 72
for _lib in _libs.values():
    if not _lib.has("UIViewGetNeedsLayout", "cdecl"):
        continue
    UIViewGetNeedsLayout = _lib.get("UIViewGetNeedsLayout", "cdecl")
    UIViewGetNeedsLayout.argtypes = [POINTER(UIView)]
    UIViewGetNeedsLayout.restype = c_bool
    break

# /usr/local/include/UIView.h: 73
for _lib in _libs.values():
    if not _lib.has("UIViewSetNeedsLayout", "cdecl"):
        continue
    UIViewSetNeedsLayout = _lib.get("UIViewSetNeedsLayout", "cdecl")
    UIViewSetNeedsLayout.argtypes = [POINTER(UIView)]
    UIViewSetNeedsLayout.restype = None
    break

# /usr/local/include/UIView.h: 76
for _lib in _libs.values():
    if not _lib.has("UIViewGetClipToBounds", "cdecl"):
        continue
    UIViewGetClipToBounds = _lib.get("UIViewGetClipToBounds", "cdecl")
    UIViewGetClipToBounds.argtypes = [POINTER(UIView)]
    UIViewGetClipToBounds.restype = c_bool
    break

# /usr/local/include/UIView.h: 77
for _lib in _libs.values():
    if not _lib.has("UIViewSetClipToBounds", "cdecl"):
        continue
    UIViewSetClipToBounds = _lib.get("UIViewSetClipToBounds", "cdecl")
    UIViewSetClipToBounds.argtypes = [POINTER(UIView), c_bool]
    UIViewSetClipToBounds.restype = None
    break

# /usr/local/include/UIView.h: 80
for _lib in _libs.values():
    if not _lib.has("UIViewSetLayoutSubviews", "cdecl"):
        continue
    UIViewSetLayoutSubviews = _lib.get("UIViewSetLayoutSubviews", "cdecl")
    UIViewSetLayoutSubviews.argtypes = [POINTER(UIView), CFUNCTYPE(UNCHECKED(None), POINTER(UIView))]
    UIViewSetLayoutSubviews.restype = None
    break

# /usr/local/include/UIView.h: 83
if _libs["panosui"].has("UIViewGetBackgroundColor", "cdecl"):
    UIViewGetBackgroundColor = _libs["panosui"].get("UIViewGetBackgroundColor", "cdecl")
    UIViewGetBackgroundColor.argtypes = [POINTER(UIView)]
    UIViewGetBackgroundColor.restype = POINTER(UIColor)

# /usr/local/include/UIView.h: 84
if _libs["panosui"].has("UIViewSetBackgroundColor", "cdecl"):
    UIViewSetBackgroundColor = _libs["panosui"].get("UIViewSetBackgroundColor", "cdecl")
    UIViewSetBackgroundColor.argtypes = [POINTER(UIView), POINTER(UIColor)]
    UIViewSetBackgroundColor.restype = None

# /usr/local/include/UIView.h: 87
if _libs["panosui"].has("UIViewGetCornerRadius", "cdecl"):
    UIViewGetCornerRadius = _libs["panosui"].get("UIViewGetCornerRadius", "cdecl")
    UIViewGetCornerRadius.argtypes = [POINTER(UIView)]
    UIViewGetCornerRadius.restype = UIFloat

# /usr/local/include/UIView.h: 88
if _libs["panosui"].has("UIViewSetCornerRadius", "cdecl"):
    UIViewSetCornerRadius = _libs["panosui"].get("UIViewSetCornerRadius", "cdecl")
    UIViewSetCornerRadius.argtypes = [POINTER(UIView), UIFloat]
    UIViewSetCornerRadius.restype = None

# /usr/local/include/UIView.h: 91
if _libs["panosui"].has("UIViewGetBorderColor", "cdecl"):
    UIViewGetBorderColor = _libs["panosui"].get("UIViewGetBorderColor", "cdecl")
    UIViewGetBorderColor.argtypes = [POINTER(UIView)]
    UIViewGetBorderColor.restype = POINTER(UIColor)

# /usr/local/include/UIView.h: 92
if _libs["panosui"].has("UIViewSetBorderColor", "cdecl"):
    UIViewSetBorderColor = _libs["panosui"].get("UIViewSetBorderColor", "cdecl")
    UIViewSetBorderColor.argtypes = [POINTER(UIView), POINTER(UIColor)]
    UIViewSetBorderColor.restype = None

# /usr/local/include/UIView.h: 95
if _libs["panosui"].has("UIViewGetBorderWidth", "cdecl"):
    UIViewGetBorderWidth = _libs["panosui"].get("UIViewGetBorderWidth", "cdecl")
    UIViewGetBorderWidth.argtypes = [POINTER(UIView)]
    UIViewGetBorderWidth.restype = UIFloat

# /usr/local/include/UIView.h: 96
if _libs["panosui"].has("UIViewSetBorderWidth", "cdecl"):
    UIViewSetBorderWidth = _libs["panosui"].get("UIViewSetBorderWidth", "cdecl")
    UIViewSetBorderWidth.argtypes = [POINTER(UIView), UIFloat]
    UIViewSetBorderWidth.restype = None

# /usr/local/include/UIView.h: 99
if _libs["panosui"].has("UIViewGetShadowOffset", "cdecl"):
    UIViewGetShadowOffset = _libs["panosui"].get("UIViewGetShadowOffset", "cdecl")
    UIViewGetShadowOffset.argtypes = [POINTER(UIView)]
    UIViewGetShadowOffset.restype = UIPoint

# /usr/local/include/UIView.h: 100
if _libs["panosui"].has("UIViewSetShadowOffset", "cdecl"):
    UIViewSetShadowOffset = _libs["panosui"].get("UIViewSetShadowOffset", "cdecl")
    UIViewSetShadowOffset.argtypes = [POINTER(UIView), UIPoint]
    UIViewSetShadowOffset.restype = None

# /usr/local/include/UIView.h: 103
if _libs["panosui"].has("UIViewGetShadowColor", "cdecl"):
    UIViewGetShadowColor = _libs["panosui"].get("UIViewGetShadowColor", "cdecl")
    UIViewGetShadowColor.argtypes = [POINTER(UIView)]
    UIViewGetShadowColor.restype = POINTER(UIColor)

# /usr/local/include/UIView.h: 104
if _libs["panosui"].has("UIViewSetShadowColor", "cdecl"):
    UIViewSetShadowColor = _libs["panosui"].get("UIViewSetShadowColor", "cdecl")
    UIViewSetShadowColor.argtypes = [POINTER(UIView), POINTER(UIColor)]
    UIViewSetShadowColor.restype = None

# /usr/local/include/UIView.h: 107
if _libs["panosui"].has("UIViewGetShadowRadius", "cdecl"):
    UIViewGetShadowRadius = _libs["panosui"].get("UIViewGetShadowRadius", "cdecl")
    UIViewGetShadowRadius.argtypes = [POINTER(UIView)]
    UIViewGetShadowRadius.restype = UIFloat

# /usr/local/include/UIView.h: 108
if _libs["panosui"].has("UIViewSetShadowRadius", "cdecl"):
    UIViewSetShadowRadius = _libs["panosui"].get("UIViewSetShadowRadius", "cdecl")
    UIViewSetShadowRadius.argtypes = [POINTER(UIView), UIFloat]
    UIViewSetShadowRadius.restype = None

# /usr/local/include/UIWindowController.h: 5
class struct__UIWindow(Structure):
    pass

UIWindow = struct__UIWindow# /usr/local/include/UIWindowController.h: 5

# /usr/local/include/UIWindowController.h: 15
class struct__UIWindowController(Structure):
    pass

struct__UIWindowController.__slots__ = [
    '_self',
    'windowWillResize',
    'windowDidResize',
    'windowWillLoad',
    'windowDidLoad',
    '_window',
]
struct__UIWindowController._fields_ = [
    ('_self', POINTER(None)),
    ('windowWillResize', CFUNCTYPE(UNCHECKED(UIRect), POINTER(None), POINTER(UIWindow), UIRect)),
    ('windowDidResize', CFUNCTYPE(UNCHECKED(None), POINTER(None), POINTER(UIWindow))),
    ('windowWillLoad', CFUNCTYPE(UNCHECKED(None), POINTER(None), POINTER(UIWindow))),
    ('windowDidLoad', CFUNCTYPE(UNCHECKED(None), POINTER(None), POINTER(UIWindow))),
    ('_window', POINTER(UIWindow)),
]

UIWindowController = struct__UIWindowController# /usr/local/include/UIWindowController.h: 15

# /usr/local/include/UIWindowController.h: 17
if _libs["panosui"].has("UIWindowControllerCreate", "cdecl"):
    UIWindowControllerCreate = _libs["panosui"].get("UIWindowControllerCreate", "cdecl")
    UIWindowControllerCreate.argtypes = []
    UIWindowControllerCreate.restype = POINTER(UIWindowController)

# /usr/local/include/UIWindowController.h: 18
if _libs["panosui"].has("UIWindowControllerDestroy", "cdecl"):
    UIWindowControllerDestroy = _libs["panosui"].get("UIWindowControllerDestroy", "cdecl")
    UIWindowControllerDestroy.argtypes = [POINTER(UIWindowController)]
    UIWindowControllerDestroy.restype = None

enum_UIWindowType = c_int# /usr/local/include/UIWindow.h: 8

UIWindowTypeBorderless = (1 << 0)# /usr/local/include/UIWindow.h: 8

UIWindowTypeTitlebar = (1 << 1)# /usr/local/include/UIWindow.h: 8

UIWindowTypeHasClose = (1 << 2)# /usr/local/include/UIWindow.h: 8

UIWindowTypeHasHide = (1 << 3)# /usr/local/include/UIWindow.h: 8

UIWindowTypeHasResize = (1 << 4)# /usr/local/include/UIWindow.h: 8

UIWindowTypeShell = (1 << 5)# /usr/local/include/UIWindow.h: 8

# /usr/local/include/UIWindow.h: 18
class struct__UIEvent(Structure):
    pass

UIEvent = struct__UIEvent# /usr/local/include/UIWindow.h: 18

# /usr/local/include/UIWindow.h: 27
if _libs["panosui"].has("UIWindowCreate", "cdecl"):
    UIWindowCreate = _libs["panosui"].get("UIWindowCreate", "cdecl")
    UIWindowCreate.argtypes = [UIRect]
    UIWindowCreate.restype = POINTER(UIWindow)

# /usr/local/include/UIWindow.h: 35
if _libs["panosui"].has("UIWindowCreateWithFlags", "cdecl"):
    UIWindowCreateWithFlags = _libs["panosui"].get("UIWindowCreateWithFlags", "cdecl")
    UIWindowCreateWithFlags.argtypes = [UIRect, c_uint]
    UIWindowCreateWithFlags.restype = POINTER(UIWindow)

# /usr/local/include/UIWindow.h: 41
if _libs["panosui"].has("UIWindowDestroy", "cdecl"):
    UIWindowDestroy = _libs["panosui"].get("UIWindowDestroy", "cdecl")
    UIWindowDestroy.argtypes = [POINTER(UIWindow)]
    UIWindowDestroy.restype = None

# /usr/local/include/UIWindow.h: 48
if _libs["panosui"].has("UIWindowShow", "cdecl"):
    UIWindowShow = _libs["panosui"].get("UIWindowShow", "cdecl")
    UIWindowShow.argtypes = [POINTER(UIWindow)]
    UIWindowShow.restype = None

# /usr/local/include/UIWindow.h: 55
if _libs["panosui"].has("UIWindowSetController", "cdecl"):
    UIWindowSetController = _libs["panosui"].get("UIWindowSetController", "cdecl")
    UIWindowSetController.argtypes = [POINTER(UIWindow), POINTER(UIWindowController)]
    UIWindowSetController.restype = None

# /usr/local/include/UIWindow.h: 62
if _libs["panosui"].has("UIWindowSetTitle", "cdecl"):
    UIWindowSetTitle = _libs["panosui"].get("UIWindowSetTitle", "cdecl")
    UIWindowSetTitle.argtypes = [POINTER(UIWindow), String]
    UIWindowSetTitle.restype = None

# /usr/local/include/UIWindow.h: 64
if _libs["panosui"].has("UIWindowGetMainView", "cdecl"):
    UIWindowGetMainView = _libs["panosui"].get("UIWindowGetMainView", "cdecl")
    UIWindowGetMainView.argtypes = [POINTER(UIWindow)]
    UIWindowGetMainView.restype = POINTER(UIView)

# /usr/local/include/UIWindow.h: 72
if _libs["panosui"].has("UIWindowSendEvent", "cdecl"):
    UIWindowSendEvent = _libs["panosui"].get("UIWindowSendEvent", "cdecl")
    UIWindowSendEvent.argtypes = [POINTER(UIWindow), UIEvent]
    UIWindowSendEvent.restype = None

enum__UIEventType = c_int# /usr/local/include/UIEvent.h: 14

UIEventTypeMouseDown = 1# /usr/local/include/UIEvent.h: 14

UIEventTypeMouseUp = 2# /usr/local/include/UIEvent.h: 14

UIEventTypeMouseMotion = 3# /usr/local/include/UIEvent.h: 14

UIEventTypeMouseDrag = 4# /usr/local/include/UIEvent.h: 14

UIEventTypeMouseEntered = 5# /usr/local/include/UIEvent.h: 14

UIEventTypeMouseScroll = 6# /usr/local/include/UIEvent.h: 14

UIEventTypeKeyboardDown = 7# /usr/local/include/UIEvent.h: 14

UIEventTypeKeyboardUp = 8# /usr/local/include/UIEvent.h: 14

UIEventType = enum__UIEventType# /usr/local/include/UIEvent.h: 14

enum_UIEventMouseButtonType = c_int# /usr/local/include/UIEvent.h: 16

UIEventMouseButtonTypeLeft = 0# /usr/local/include/UIEvent.h: 16

UIEventMouseButtonTypeRight = 1# /usr/local/include/UIEvent.h: 16

enum_UIEventMouseButtonState = c_int# /usr/local/include/UIEvent.h: 22

UIEventMouseButtonUp = 0# /usr/local/include/UIEvent.h: 22

UIEventMouseButtonDown = 1# /usr/local/include/UIEvent.h: 22

enum_UIEventMouseScrollType = c_int# /usr/local/include/UIEvent.h: 28

UIEventMouseScrollTypeDiscrete = 0# /usr/local/include/UIEvent.h: 28

UIEventMouseScrollTypeContinuous = 1# /usr/local/include/UIEvent.h: 28

enum_UIEventMouseScrollDirection = c_int# /usr/local/include/UIEvent.h: 34

UIEventMouseScrollDirectionVertical = 0# /usr/local/include/UIEvent.h: 34

UIEventMouseScrollDirectionHorizontal = 1# /usr/local/include/UIEvent.h: 34

UIEventMouseScrollDirectionBoth = 2# /usr/local/include/UIEvent.h: 34

# /usr/local/include/UIEvent.h: 72
for _lib in _libs.values():
    try:
        reserved = (c_int).in_dll(_lib, "reserved")
        break
    except:
        pass

# /usr/local/include/UILabel.h: 6
class struct__UILabel(Structure):
    pass

UILabel = struct__UILabel# /usr/local/include/UILabel.h: 6

# /usr/local/include/UILabel.h: 8
if _libs["panosui"].has("UILabelCreate", "cdecl"):
    UILabelCreate = _libs["panosui"].get("UILabelCreate", "cdecl")
    UILabelCreate.argtypes = [UIRect]
    UILabelCreate.restype = POINTER(UILabel)

# /usr/local/include/UILabel.h: 10
if _libs["panosui"].has("UILabelSetContents", "cdecl"):
    UILabelSetContents = _libs["panosui"].get("UILabelSetContents", "cdecl")
    UILabelSetContents.argtypes = [POINTER(UILabel), String]
    UILabelSetContents.restype = None

# /usr/local/include/UILabel.h: 11
if _libs["panosui"].has("UILabelSetFontSize", "cdecl"):
    UILabelSetFontSize = _libs["panosui"].get("UILabelSetFontSize", "cdecl")
    UILabelSetFontSize.argtypes = [POINTER(UILabel), UIFloat]
    UILabelSetFontSize.restype = None

# /usr/local/include/UILabel.h: 12
if _libs["panosui"].has("UILabelSetFontColor", "cdecl"):
    UILabelSetFontColor = _libs["panosui"].get("UILabelSetFontColor", "cdecl")
    UILabelSetFontColor.argtypes = [POINTER(UILabel), UIColor]
    UILabelSetFontColor.restype = None

# /usr/local/include/UILabel.h: 13
if _libs["panosui"].has("UILabelSizeToFit", "cdecl"):
    UILabelSizeToFit = _libs["panosui"].get("UILabelSizeToFit", "cdecl")
    UILabelSizeToFit.argtypes = [POINTER(UILabel)]
    UILabelSizeToFit.restype = None

# /usr/local/include/UILabel.h: 15
if _libs["panosui"].has("UILabelGetContents", "cdecl"):
    UILabelGetContents = _libs["panosui"].get("UILabelGetContents", "cdecl")
    UILabelGetContents.argtypes = [POINTER(UILabel)]
    UILabelGetContents.restype = c_char_p

# /usr/local/include/UILabel.h: 16
if _libs["panosui"].has("UILabelGetFontSize", "cdecl"):
    UILabelGetFontSize = _libs["panosui"].get("UILabelGetFontSize", "cdecl")
    UILabelGetFontSize.argtypes = [POINTER(UILabel)]
    UILabelGetFontSize.restype = UIFloat

# /usr/local/include/UILabel.h: 17
if _libs["panosui"].has("UILabelGetFontColor", "cdecl"):
    UILabelGetFontColor = _libs["panosui"].get("UILabelGetFontColor", "cdecl")
    UILabelGetFontColor.argtypes = [POINTER(UILabel)]
    UILabelGetFontColor.restype = UIColor

_UIPoint = struct__UIPoint# /usr/local/include/UIGeometry.h: 10

_UISize = struct__UISize# /usr/local/include/UIGeometry.h: 15

_UIRect = struct__UIRect# /usr/local/include/UIGeometry.h: 21

_UIAnimation = struct__UIAnimation# /usr/local/include/UIAnimation.h: 20

_UITransaction = struct__UITransaction# /usr/local/include/UIAnimation.h: 27

_UIApplication = struct__UIApplication# /usr/local/include/UIApplication.h: 7

_UIApplicationDelegate = struct__UIApplicationDelegate# /usr/local/include/UIApplication.h: 12

_UIColor = struct__UIColor# /usr/local/include/UIColor.h: 3

_UILayer = struct__UILayer# /usr/local/include/UILayer.h: 25

_UIEventResponder = struct__UIEventResponder# /usr/local/include/UIEventResponder.h: 13

_UIView = struct__UIView# /usr/local/include/UIView.h: 12

_UIWindow = struct__UIWindow# /usr/local/include/UIWindowController.h: 5

_UIWindowController = struct__UIWindowController# /usr/local/include/UIWindowController.h: 15

_UIEvent = struct__UIEvent# /usr/local/include/UIWindow.h: 18

_UILabel = struct__UILabel# /usr/local/include/UILabel.h: 6

# No inserted files

# No prefix-stripping

