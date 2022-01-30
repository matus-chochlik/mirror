#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
file(GLOB LIBDIR_ENTRIES LIST_DIRECTORIES true
	RELATIVE "${MIRROR_LLVM_PREFIX}/lib"
	"${MIRROR_LLVM_PREFIX}/lib/*"
)
foreach(ENTRY ${LIBDIR_ENTRIES})
	if(ENTRY MATCHES ${CMAKE_LIBRARY_ARCHITECTURE_REGEX})
		set(MIRROR_LIBCXX_RPATH "${MIRROR_LLVM_PREFIX}/lib/${ENTRY}")
		message(STATUS "Using '${MIRROR_LIBCXX_RPATH}' as libc++ rpath")
	endif()
endforeach()
