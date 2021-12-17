# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
add_library(mirror-headers INTERFACE)

target_include_directories(
	mirror-headers
	INTERFACE
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_options(
	mirror-headers
	INTERFACE
		-std=c++2b -stdlib=libc++
		-freflection-ts -freflection-ext
		-pedantic -Wall -Werror -Weverything
		-Wno-language-extension-token
		-Wno-c++98-compat -Wno-c++98-compat-pedantic
		-Wno-c++20-compat -Wno-c++2a-extensions
		-Wno-padded
		-Wno-documentation-unknown-command
)

target_link_options(
	mirror-headers
	INTERFACE -std=c++2b -stdlib=libc++
)

file(GLOB_RECURSE HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.hpp)

foreach(FILENAME ${HEADERS})
	set_property(
		TARGET mirror-headers
		APPEND PROPERTY PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
	)
endforeach()

find_program(SED_COMMAND sed)
if(SED_COMMAND)
	unset(DOC_FIXED_HEADERS)
	foreach(FILENAME ${HEADERS})
		get_filename_component(
			DST_DIR "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}"
			DIRECTORY
		)
		make_directory("${DST_DIR}")
		add_custom_command(
			OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}"
			COMMAND "${SED_COMMAND}"
			ARGS	-f "${CMAKE_CURRENT_SOURCE_DIR}/fix_for_doc.sed"
					<  "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}"
					>  "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}"
					DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}"
					"${CMAKE_CURRENT_SOURCE_DIR}/fix_for_doc.sed"
		)
		list(APPEND DOC_FIXED_HEADERS "${CMAKE_CURRENT_BINARY_DIR}/${FILENAME}")
	endforeach()
	add_custom_target(doc-fixed-headers-mirror DEPENDS ${DOC_FIXED_HEADERS})
	add_dependencies(doc-fixed-headers doc-fixed-headers-mirror)
endif()
