#  Copyright 2010-2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

macro(mire_doxy_doc_common LIBRARY)

	string(REGEX REPLACE "/" "-" LIB_PREFIX ${LIBRARY})
	# doxygen working directory
	set(DOXYGEN_WD ${CMAKE_CURRENT_SOURCE_DIR})

	# get the version string
	file(READ ${PROJECT_SOURCE_DIR}/VERSION VERSION_STR)

	# doxyfile for building html docs
	set(DOXYFILE ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-html)
	file(WRITE ${DOXYFILE}  "@INCLUDE = ${DOXYGEN_WD}/Doxyfile\n")
	file(APPEND ${DOXYFILE} "INPUT += ${PROJECT_SOURCE_DIR}/doc/include/${LIBRARY}\n")
	file(APPEND ${DOXYFILE} "INPUT += ${PROJECT_SOURCE_DIR}/doc/tutorial/${LIBRARY}\n")
	file(APPEND ${DOXYFILE} "INPUT += ${PROJECT_SOURCE_DIR}/include/${LIBRARY}\n")
	file(APPEND ${DOXYFILE} "INPUT += ${PROJECT_SOURCE_DIR}/example/${LIBRARY}\n")
	file(APPEND ${DOXYFILE} "INPUT += ${PROJECT_BINARY_DIR}/example/${LIBRARY}\n")
	file(APPEND ${DOXYFILE} "INCLUDE_PATH += ${PROJECT_SOURCE_DIR}/include\n")
	file(APPEND ${DOXYFILE} "INCLUDE_PATH += ${PROJECT_SOURCE_DIR}/example\n")
	file(APPEND ${DOXYFILE} "EXAMPLE_PATH += ${PROJECT_SOURCE_DIR}/doc/tutorial\n")
	file(APPEND ${DOXYFILE} "EXAMPLE_PATH += ${PROJECT_SOURCE_DIR}/example/${LIBRARY}\n")
	file(APPEND ${DOXYFILE} "EXAMPLE_PATH += ${PROJECT_BINARY_DIR}/example/${LIBRARY}\n")
	file(APPEND ${DOXYFILE} "IMAGE_PATH += ${PROJECT_SOURCE_DIR}/logo/\n")
	file(APPEND ${DOXYFILE} "OUTPUT_DIRECTORY = ${CMAKE_CURRENT_BINARY_DIR}\n")

	foreach(COMPONENT mire mire/ct)
		if("${LIBRARY}" STREQUAL "${COMPONENT}")
			file(APPEND ${DOXYFILE} "GENERATE_TAGFILE = ${CMAKE_CURRENT_BINARY_DIR}/doxygen.tags\n")
		else()
			file(APPEND ${DOXYFILE} "TAGFILES += ${PROJECT_BINARY_DIR}/doc/doxygen/${COMPONENT}/doxygen.tags\n")
		endif()
	endforeach()

	file(APPEND ${DOXYFILE} "PROJECT_NUMBER = ${VERSION_STR}\n")
	file(APPEND ${DOXYFILE} "QUIET = YES\n")

	add_custom_command(
		OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		COMMENT "Generating HTML documentation for '${LIBRARY}' (phase 1)"
	)

	add_custom_target(
		${LIB_PREFIX}-prebuild-doc
		DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/html/index.html
	)
	set_property(TARGET ${LIB_PREFIX}-prebuild-doc PROPERTY FOLDER "Documentation/${LIBRARY}")

	add_custom_target(
		${LIB_PREFIX}-doc
		COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYFILE}
		WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
		DEPENDS ${LIB_PREFIX}-prebuild-doc
		COMMENT "Generating HTML documentation for '${LIBRARY}' (phase 2)"
	)
	set_property(TARGET ${LIB_PREFIX}-doc PROPERTY FOLDER "Documentation/${LIBRARY}")

	set(COPIED_FILES tab_a.png tab_b.png tab_h.png tab_s.png tabs.css)

	foreach(COPIED_FILE ${COPIED_FILES})
		if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/${COPIED_FILE}")
			add_custom_command(
				TARGET ${LIB_PREFIX}-doc
				POST_BUILD
				COMMAND ${CMAKE_COMMAND} -E copy
					"${CMAKE_CURRENT_SOURCE_DIR}/${COPIED_FILE}"
					"${CMAKE_CURRENT_BINARY_DIR}/html/${COPIED_FILE}"
				COMMENT "Copying file ${COPIED_FILE}"
			)
		endif()
	endforeach()

	unset(DOXYFILE)

	unset(DOC_DEPENDS)
endmacro()
