#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
include(CheckIncludeFileCXX)
check_include_file_cxx("string_view" HAS_STRING_VIEW)
if (NOT HAS_STRING_VIEW)
	configure_file(
		"${PROJECT_SOURCE_DIR}/config/include/string_view"
		"${PROJECT_BINARY_DIR}/include/string_view" COPYONLY
	)
endif()

add_definitions(-isystem "${PROJECT_BINARY_DIR}/include")

