# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 3.16)

if(NOT EXISTS "${CMAKE_TOOLCHAIN_FILE}")
	if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/toolchain.cmake")
		set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/toolchain.cmake")
	endif()
endif()

project(Mirror CXX)

file(STRINGS VERSION MIRROR_VERSION)

include(config/Policies.cmake)
include(config/Defaults.cmake)
include(config/BuildType.cmake)
include(config/CommonLibs.cmake)

find_package(Threads REQUIRED)

add_subdirectory(include)
add_subdirectory(source)
add_subdirectory(example)
add_subdirectory(doc)
