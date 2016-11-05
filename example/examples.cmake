#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
function(add_example LIBRARY EXAMPLE_NAME)

	string(REGEX REPLACE "/" "-" LIB_PREFIX ${LIBRARY})
	add_executable(${LIBRARY}-${EXAMPLE_NAME} EXCLUDE_FROM_ALL ${EXAMPLE_NAME}.cpp)
	add_dependencies(examples-${LIB_PREFIX} ${LIBRARY}-${EXAMPLE_NAME})
	set_property(TARGET ${LIBRARY}-${EXAMPLE_NAME} PROPERTY FOLDER "Examples/${LIBRARY}")

	if(NOT MIRROR_NO_DOCS)
		add_custom_command(
			OUTPUT ${LIBRARY}-${EXAMPLE_NAME}.out.txt
			COMMAND ${LIBRARY}-${EXAMPLE_NAME} > ${LIBRARY}-${EXAMPLE_NAME}.out.txt
			DEPENDS ${LIBRARY}-${EXAMPLE_NAME}
		)
		add_dependencies(${LIBRARY}-${EXAMPLE_NAME} mirror-external-deps)
		add_custom_target(
			${LIBRARY}-${EXAMPLE_NAME}-output
			DEPENDS ${LIBRARY}-${EXAMPLE_NAME}.out.txt
		)
		add_dependencies(examples-${LIB_PREFIX} ${LIBRARY}-${EXAMPLE_NAME}-output)
	endif()

endfunction()

function(add_examples LIBRARY)
	file(GLOB EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/[0-9][0-9][0-9]*.cpp")
	foreach(EXAMPLE_PATH ${EXAMPLES})
		get_filename_component(EXAMPLE_NAME ${EXAMPLE_PATH} NAME_WE)
		add_example(${LIBRARY} ${EXAMPLE_NAME})
	endforeach()
endfunction()
