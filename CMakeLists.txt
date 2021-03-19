# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 3.10)

include(config/Policies.cmake)
include(config/Defaults.cmake)
include(config/BuildType.cmake)
include(config/Executable.cmake)

project(Mirror)

add_subdirectory(example)
