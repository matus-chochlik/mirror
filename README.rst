Mirror reflection utilities
===========================

:Author: Matúš Chochlík <chochlik@gmail.com>

Reboot of the Mirror reflection utilities implemented on top
of the C++ reflection TS.

Cloning the Mirror repository
-----------------------------
::

 git clone --recursive https://github.com/matus-chochlik/mirror.git

Building `clang` with reflection support
----------------------------------------

Install the required packages for building `clang`:

::

 apt install cmake clang lld ninja-build libgmp-dev libmpfr-dev

Build and install `clang` and `libc++`:
::

 cd /path/to/mirror/src/dir && \
 ./tools/build_llvm.sh \
    -b /path/to/llvm/build/dir \
    -i /path/to/llvm/install/dir

Setting up the environment
--------------------------

In order for the build system of the `Mirror` library to use `clang` built
and installed in the previous step either set and export an environment variable:

::

 export MIRROR_LLVM_PREFIX=/path/to/llvm/install/dir

or create a file named `LLVM_PREFIX` containing the path to the `clang`
install directory, in the root of the cloned `Mirror` repository:

::

 echo -n "/path/to/llvm/install/dir" > /path/to/mirror/src/dir/LLVM_PREFIX

Building Mirror
---------------

In order to build the `Mirror` library and its examples you can do:

::

 mkdir -p /path/to/mirror/build/dir && \
 cd /path/to/mirror/build/dir && \
 cmake /path/to/mirror/src/dir && \
 make -j N

or

::

 mkdir -p /path/to/mirror/build/dir && \
 cd /path/to/mirror/build/dir && \
 cmake -G Ninja /path/to/mirror/src/dir && \
 ninja

License
=======

Copyright 2008-2021 Matus Chochlik. Distributed under the Boost
Software License, Version 1.0. (See accompanying file
LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

The applications using Qt5 are distributed under
the GNU GENERAL PUBLIC LICENSE version 3.
See http://www.gnu.org/licenses/gpl-3.0.txt

