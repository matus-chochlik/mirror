#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
function(add_mire_example LIBRARY EXAMPLE_NAME)

	string(REGEX REPLACE "/" "-" LIB_PREFIX ${LIBRARY})
	add_executable(${EXAMPLE_NAME} EXCLUDE_FROM_ALL ${EXAMPLE_NAME}.cpp)
	add_dependencies(examples-${LIB_PREFIX} ${EXAMPLE_NAME})
	set_property(TARGET ${EXAMPLE_NAME} PROPERTY FOLDER "Examples/${LIBRARY}")

	if(NOT MIRROR_NO_DOCS)
		add_custom_command(
			OUTPUT ${EXAMPLE_NAME}.out.txt
			COMMAND ${EXAMPLE_NAME} > ${EXAMPLE_NAME}.out.txt
			DEPENDS ${EXAMPLE_NAME}
		)
		add_custom_target(
			${EXAMPLE_NAME}-output
			DEPENDS ${EXAMPLE_NAME}.out.txt
		)
		add_dependencies(examples-${LIB_PREFIX} ${EXAMPLE_NAME}-output)
		add_dependencies(doc-prebuild-${LIB_PREFIX} ${EXAMPLE_NAME}-output)
	endif()

endfunction()

function(add_mire_examples LIBRARY)
	file(GLOB EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/[0-9][0-9][0-9]*.cpp")
	foreach(EXAMPLE_PATH ${EXAMPLES})
		get_filename_component(EXAMPLE_NAME ${EXAMPLE_PATH} NAME_WE)
		add_mire_example(${LIBRARY} ${EXAMPLE_NAME})
	endforeach()
endfunction()
