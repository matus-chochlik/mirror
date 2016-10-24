#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 2.8)

project(Mirror CXX)

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "No build type selected, default to Release")
	set(CMAKE_BUILD_TYPE "Release" CACHE STRING "Build type (default Release)")
endif()

option(MIRROR_NO_DOCS "Don't build and install the documentation" Off)

include(config/Tools.cmake)

include(config/CppReflection.cmake)
include(config/StdFixes.cmake)
include(config/Warnings.cmake)

include(config/Install.cmake)

include_directories(include)
include_directories(implement)
include_directories(${PROJECT_BINARY_DIR}/include)

if(NOT MIRROR_NO_DOCS)
	# TODO
	#add_subdirectory(doc)
endif()

add_subdirectory(example)
add_subdirectory(test)
