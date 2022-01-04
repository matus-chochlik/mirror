# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#

add_library(
	mirror-testdecl STATIC
	register_month
	register_weekday
	register_tetrahedron
)

target_link_libraries(
	mirror-testdecl
	PUBLIC Mirror
)

set_target_properties(
	mirror-testdecl
	PROPERTIES
		FOLDER "Example/Mirror"
)

