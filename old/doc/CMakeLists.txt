#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

find_package(Doxygen)

if(DOXYGEN_FOUND)
	add_subdirectory(doxygen)
else()
	set(MIRROR_NO_DOCS 1 PARENT_SCOPE)
endif()

