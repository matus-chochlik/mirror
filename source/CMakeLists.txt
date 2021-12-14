# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
add_library(ReflectionTS INTERFACE IMPORTED GLOBAL)
target_link_libraries(ReflectionTS INTERFACE reflexpr-headers)

add_library(Mirror INTERFACE IMPORTED GLOBAL)
target_link_libraries(Mirror INTERFACE mirror-headers)

set(
	MIRROR_EXPORT_TARGETS
		mirror-headers
)

install(
	TARGETS ${MIRROR_EXPORT_TARGETS}
	EXPORT Reflection
	LIBRARY DESTINATION lib
	ARCHIVE DESTINATION lib
	RUNTIME DESTINATION bin
	INCLUDES DESTINATION include
	PUBLIC_HEADER DESTINATION include
)

install(
	EXPORT Reflection
	NAMESPACE Mirror::
	FILE Reflection.cmake
	DESTINATION lib/cmake/Mirror
)
