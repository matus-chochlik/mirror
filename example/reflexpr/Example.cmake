# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
add_custom_target(reflexpr-examples ALL)
set_target_properties(
	reflexpr-examples
	PROPERTIES FOLDER "Example/ReflectionTS"
)

function(reflexpr_install_example TARGET_NAME)
	install(
		TARGETS ${TARGET_NAME}
		DESTINATION share/mirror/example/reflexpr
	)
endfunction()

function(reflexpr_add_simple_example EXAMPLE_NAME)
	add_executable(
		reflexpr-${EXAMPLE_NAME}
		EXCLUDE_FROM_ALL
		"${EXAMPLE_NAME}.cpp"
	)
	add_dependencies(reflexpr-examples reflexpr-${EXAMPLE_NAME})
	target_link_libraries(
		reflexpr-${EXAMPLE_NAME}
		PUBLIC ReflectionTS
	)

	set_target_properties(
		reflexpr-${EXAMPLE_NAME}
		PROPERTIES
			BUILD_RPATH "${MIRROR_LIBCXX_RPATH}"
			FOLDER "Example/ReflectionTS"
	)
	reflexpr_install_example(reflexpr-${EXAMPLE_NAME})
endfunction()
