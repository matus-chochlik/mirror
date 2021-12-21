# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#

install(
	FILES mirror.png
	DESTINATION share/mirror/doc
	COMPONENT doc-logos
	EXCLUDE_FROM_ALL
)

add_custom_command(
	OUTPUT "${CMAKE_INSTALL_PREFIX}/share/mirror/doc/mirror.png"
	COMMAND ${CMAKE_COMMAND}
	ARGS -DCOMPONENT=doc-logos -P cmake_install.cmake
	WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
	MAIN_DEPENDENCY "${CMAKE_CURRENT_SOURCE_DIR}/mirror.png"
	DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/mirror.png"
)

add_custom_target(
	install-doc-logos
	DEPENDS "${CMAKE_INSTALL_PREFIX}/share/mirror/doc/mirror.png"
)

add_dependencies(
	install-doc
	install-doc-logos
)

