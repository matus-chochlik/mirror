Mirror reflection utilities
===========================

:Author: Matúš Chochlík <chochlik@gmail.com>

Collection of reflection utilities based on top of the current reflection
proposal as described in P2320Rx and implemented by https://github.com/lock3/meta
.

Cloning the repo
================

This repository uses git submodules, so don't forget to use the ``--recursive``
flag while cloning:
::

 git clone --recursive https://github.com/matus-chochlik/mirror.git


Building clang with reflection support
======================================

The updated version of clang, extended with support for reflection can be built
by invoking the ``rebuild-llvm`` script in the ``third_party`` sub-directory:
::

 ./third_party/rebuild-llvm /path/to/writable/build/directory /opt/mirror/llvm

This will build the ``llvm`` executables and libraries, including ``clang++``
and install them to ``/opt/mirror/llvm``.
Both the build directory and the install directory need to be writable by the
current user.

Building mirror
===============

Mirror uses a ``cmake``-generated build system. You can build it by doing
the following:
::

 mkdir /path/to/build/directory
 cd /path/to/build/directory
 cmake /path/to/mirror/repository
 make -j N

License
=======

Copyright 2008-2021 Matus Chochlik. Distributed under the Boost
Software License, Version 1.0. (See accompanying file
LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

