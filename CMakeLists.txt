#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 2.8)

project(Mirror CXX)

option(MIRROR_NO_DOCS "Don't build and install the documentation" Off)

file(WRITE "${PROJECT_BINARY_DIR}/SOURCE_DIR" "${PROJECT_SOURCE_DIR}")
file(WRITE "${PROJECT_SOURCE_DIR}/BINARY_DIR" "${PROJECT_BINARY_DIR}")
include(config/Tools.cmake)

include(config/CppFeature.cmake)
include(config/Warnings.cmake)

include_directories(include)

if(NOT MIRROR_NO_DOCS)
	# TODO
	#add_subdirectory(doc)
endif()
# TODO
#add_subdirectory(example)
add_subdirectory(test)
