#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
function(add_mire_example COMPONENT EXAMPLE_NAME)

	add_executable(${EXAMPLE_NAME} EXCLUDE_FROM_ALL ${EXAMPLE_NAME}.cpp)
	add_dependencies(examples-${COMPONENT} ${EXAMPLE_NAME})
	set_property(TARGET ${EXAMPLE_NAME} PROPERTY FOLDER "Examples/${COMPONENT}")

endfunction()

function(add_mire_examples COMPONENT)
	file(GLOB EXAMPLES "${CMAKE_CURRENT_SOURCE_DIR}/[0-9][0-9][0-9]*.cpp")
	foreach(EXAMPLE_PATH ${EXAMPLES})
		get_filename_component(EXAMPLE_NAME ${EXAMPLE_PATH} NAME_WE)
		add_mire_example(${COMPONENT} ${EXAMPLE_NAME})
	endforeach()
endfunction()
