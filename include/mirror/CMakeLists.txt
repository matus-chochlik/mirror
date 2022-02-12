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
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/submodules/rapidjson/include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/submodules/ctre/include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/submodules/ChaiScript/include>
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
		-Wno-weak-vtables
		-Wno-documentation-unknown-command
)

target_link_options(
	mirror-headers
	INTERFACE -std=c++2b -stdlib=libc++
)

target_link_libraries(
	mirror-headers
	INTERFACE
		Threads::Threads
		Mirror::Deps::System
		Mirror::Deps::SQLite3
)

file(GLOB_RECURSE HEADERS RELATIVE "${CMAKE_CURRENT_SOURCE_DIR}" *.hpp)

foreach(FILENAME ${HEADERS})
	set_property(
		TARGET mirror-headers
		APPEND PROPERTY PUBLIC_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/${FILENAME}
	)
endforeach()
