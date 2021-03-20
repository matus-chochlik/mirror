#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
if(DEFINED ENV{MIRROR_LLVM_PREFIX})
	set(MIRROR_LLVM_PREFIX $ENV{MIRROR_LLVM_PREFIX})
elseif(EXISTS "${PROJECT_SOURCE_DIR}/LLVM_PREFIX")
	file(READ "${PROJECT_SOURCE_DIR}/LLVM_PREFIX" MIRROR_LLVM_PREFIX)
else()
	set(MIRROR_LLVM_PREFIX /opt/llvm)
endif()

set(CMAKE_CXX_COMPILER ${MIRROR_LLVM_PREFIX}/bin/clang++)
message(STATUS "Using '${MIRROR_LLVM_PREFIX}' as LLVM prefix path")

if(NOT EXISTS "${PROJECT_SOURCE_DIR}/LLVM_PREFIX")
	file(WRITE "${PROJECT_SOURCE_DIR}/LLVM_PREFIX" "${MIRROR_LLVM_PREFIX}")
endif()
