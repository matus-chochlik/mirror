#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
macro(mirror_add_executable TARGETNAME)
	add_executable(${TARGETNAME} ${ARGN})
	target_compile_options(${TARGETNAME} PRIVATE -std=c++2a;-freflection)
	target_compile_options(${TARGETNAME} PRIVATE -pedantic;-Wall;-Werror)
	target_compile_options(${TARGETNAME} PRIVATE -Weverything)
	target_compile_options(${TARGETNAME} PRIVATE -Wno-language-extension-token)
	target_compile_options(${TARGETNAME} PRIVATE -Wno-c++98-compat;-Wno-c++98-compat-pedantic)
	target_compile_options(${TARGETNAME} PRIVATE -Wno-c++20-compat;-Wno-c++2a-extensions)
	target_compile_options(${TARGETNAME} PRIVATE -Wno-padded)
	target_compile_options(${TARGETNAME} PRIVATE -Wno-weak-vtables)
	target_compile_options(${TARGETNAME} PRIVATE -Wno-documentation-unknown-command)
	target_include_directories(${TARGETNAME} PRIVATE ${PROJECT_SOURCE_DIR}/include)
	target_include_directories(${TARGETNAME} PRIVATE ${MIRROR_LLVM_PREFIX}/include)
endmacro()

