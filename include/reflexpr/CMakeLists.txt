# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
add_library(reflexpr-headers INTERFACE)

target_include_directories(
	reflexpr-headers
	INTERFACE
		$<INSTALL_INTERFACE:include>
		$<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
)

target_compile_options(
	reflexpr-headers
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
	reflexpr-headers
	INTERFACE -std=c++20 -stdlib=libc++
)
