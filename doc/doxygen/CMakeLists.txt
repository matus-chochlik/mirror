# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#

configure_file(Doxyfile-common.in Doxyfile-common @ONLY)
configure_file(Doxyfile-html.in Doxyfile-html @ONLY)
configure_file(Doxyfile-xml.in Doxyfile-xml @ONLY)

file(
	GLOB_RECURSE DOC_INPUT_SOURCES
	LIST_DIRECTORIES FALSE
	${CMAKE_CURRENT_SOURCE_DIR}/*.hpp
	${PROJECT_SOURCE_DIR}/include/*.hpp
	${PROJECT_SOURCE_DIR}/example/*.hpp
	${PROJECT_SOURCE_DIR}/example/*.cpp
)

add_custom_command(
	OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml"
	COMMAND ${DOXYGEN_EXECUTABLE} 
	ARGS Doxyfile-xml
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	MAIN_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-xml"
	DEPENDS doc-fixed-headers ${DOC_INPUT_SOURCES}
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-xml.in"
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-xml"
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-common.in"
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-common"
	COMMENT "Generating Doxygen XML output"
)

add_custom_command(
	OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/doxygen/index.html"
	COMMAND ${DOXYGEN_EXECUTABLE} 
	ARGS Doxyfile-html
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	MAIN_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile-html"
	DEPENDS doc-fixed-headers ${DOC_INPUT_SOURCES}
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-html.in"
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-html"
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-common.in"
		"${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile-common"
		"${CMAKE_CURRENT_SOURCE_DIR}/header.html"
		"${CMAKE_CURRENT_SOURCE_DIR}/footer.html"
		"${CMAKE_CURRENT_SOURCE_DIR}/mirror.css"
	COMMENT "Generating Doxygen HTML documentation"
)

add_custom_target(
	doc-doxygen-xml
	DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/xml/index.xml"
)

set_target_properties(
	doc-doxygen-xml
	PROPERTIES FOLDER "Documentation"
)

add_custom_target(
	doc-doxygen-html
	DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/doxygen/index.html"
)

set_target_properties(
	doc-doxygen-html
	PROPERTIES FOLDER "Documentation"
)

add_dependencies(
	doc
	doc-doxygen-html
)

install(
	DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/doxygen
	DESTINATION share/mirror/doc
	USE_SOURCE_PERMISSIONS
	COMPONENT doc-doxygen-html
	EXCLUDE_FROM_ALL
)

add_custom_command(
	OUTPUT "${CMAKE_INSTALL_PREFIX}/share/mirror/doc/doxygen/index.html"
	COMMAND ${CMAKE_COMMAND}
	ARGS -DCOMPONENT=doc-doxygen-html -P cmake_install.cmake
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	MAIN_DEPENDENCY "${CMAKE_CURRENT_BINARY_DIR}/doxygen/index.html"
	DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/doxygen/index.html"
)

add_custom_target(
	install-doc-doxygen-html
	DEPENDS "${CMAKE_INSTALL_PREFIX}/share/mirror/doc/doxygen/index.html"
)

add_dependencies(
	install-doc
	install-doc-doxygen-html
)

