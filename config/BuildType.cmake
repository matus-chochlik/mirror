#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
	message(STATUS "No build type selected, default to Debug")
	set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Build type (default Debug)")
endif()

if("${CMAKE_BUILD_TYPE}" STREQUAL "Release")
	set(MIRROR_DEBUG 0)
else()
	set(MIRROR_DEBUG 1)
endif()
