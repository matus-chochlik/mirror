Mirror reflection utilities
===========================

:Author: Matúš Chochlík <chochlik@gmail.com>

Reboot of the Mirror reflection utilities implemented on top
of the C++ reflection TS.

Cloning the Mirror repository
-----------------------------
::

 git clone --recursive https://github.com/matus-chochlik/mirror.git

Getting and building `clang` with reflection
--------------------------------------------

Install the required packages for building `clang`:

::

 apt install cmake clang lld ninja-build

Clone the fork of the llvm-project, with the reflection TS and extensions:

::

 git clone https://github.com/matus-chochlik/llvm-project.git

Configure, build and install `clang++` (consider using `/opt/mirror/llvm` as
the install prefix path, it will simplify the next steps):

::

 mkdir -p "/path/to/clang/build/dir" && \
 cd "/path/to/clang/build/dir" && \
 export CXX=clang++ && \
 cmake \
        -G Ninja \
        -DLLVM_ENABLE_PROJECTS="clang;libc;libcxx;libcxxabi" \
        -DLLVM_USE_LINKER=lld \
        -DCMAKE_INSTALL_PREFIX=/path/to/clang/install/dir \
        -DCMAKE_SHARED_LINKER_FLAGS="-fuse-ld=lld -pthread" \
        -DCMAKE_EXE_LINKER_FLAGS="-fuse-ld=lld -pthread" \
        -DCMAKE_BUILD_TYPE=Release \
        -DLLVM_PARALLEL_LINK_JOBS=2 \
        -DLLVM_PARALLEL_COMPILE_JOBS=4 \
        /path/to/clang/source/dir/llvm && \
 ninja install install-llvmlibc install-libcxx

Setting up the environment
--------------------------

In order for the build system of the `Mirror` library to use `clang` built
and installed in the previous step either set and export an environment variable:

::

 export MIRROR_LLVM_PREFIX=/path/to/clang/install/dir

or create a file named `LLVM_PREFIX` containing the path to the `clang`
install directory, in the root of the cloned `Mirror` repository:

::

 cd /path/to/mirror/src/dir && \
 echo -n "/path/to/clang/install/dir" > LLVM_PREFIX

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

