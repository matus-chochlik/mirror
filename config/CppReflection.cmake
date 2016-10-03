#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
# we need C++14 + reflection
if(NOT(EXISTS "${REFLEXPR_INCLUDE_DIR}"))
	message(FATAL_ERROR
		"The reflexpr header directory `${REFLEXPR_INCLUDE_DIR}` does not exist!"
	)
endif()

if(NOT(EXISTS "${REFLEXPR_INCLUDE_DIR}/reflexpr"))
	message(FATAL_ERROR "the reflexpr header file does not exist!")
endif()


if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
	set(CPP_COMPILER_OPTIONS
		-std=c++1z
		-isystem "${REFLEXPR_INCLUDE_DIR}"
		-Xclang -freflection
	)
else()
	message(FATAL_ERROR "Only clang is supported at the moment!")
endif()

add_definitions(${CPP_COMPILER_OPTIONS})

message(STATUS "Testing reflection support")
configure_file(
	${PROJECT_SOURCE_DIR}/config/cpp/reflection.cpp
	${PROJECT_BINARY_DIR}/cpp/reflection.cpp
)
try_compile(
	SUPPORTED_COMPILER
	${PROJECT_BINARY_DIR}/cpp
	${PROJECT_BINARY_DIR}/cpp/reflection.cpp
	COMPILE_DEFINITIONS ${CPP_COMPILER_OPTIONS}
)
if(NOT ${SUPPORTED_COMPILER})
	message(FATAL_ERROR
	"Your compiler does not support all required C++ features."
	)
endif()
