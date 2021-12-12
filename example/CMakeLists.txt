# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
add_custom_target(mirror-examples ALL)
set_target_properties(
	mirror-examples
	PROPERTIES FOLDER "Example/Mirror"
)

function(mirror_install_example TARGET_NAME)
	install(
		TARGETS ${TARGET_NAME}
		DESTINATION share/mirror/example/mirror
	)
endfunction()

function(mirror_add_simple_example EXAMPLE_NAME)
	add_executable(
		mirror-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
		${ARGN}
	)
	add_dependencies(mirror-examples mirror-${EXAMPLE_NAME})
	target_link_libraries(
		mirror-${EXAMPLE_NAME}
		PUBLIC Mirror
		PRIVATE ${ARGN}
	)

	set_target_properties(
		mirror-${EXAMPLE_NAME}
		PROPERTIES
			BUILD_RPATH "${MIRROR_LIBCXX_RPATH}"
			FOLDER "Example/Mirror"
	)
	mirror_install_example(mirror-${EXAMPLE_NAME})
endfunction()

mirror_add_simple_example(next_weekday)
mirror_add_simple_example(gen_puml_diagram)
