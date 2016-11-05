#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
option(MIRROR_NO_RAPIDJSON "Don't use the RapidJSON library" On)

add_custom_target(mirror-external-deps)

include(ExternalProject)

if(NOT MIRROR_NO_RAPIDJSON)
	function(mirror_add_rapidjson)
		ExternalProject_Add(
			rapidjson
			GIT_REPOSITORY https://github.com/miloyip/rapidjson.git
			GIT_TAG master
			PREFIX ${CMAKE_CURRENT_BINARY_DIR}/rapidjson
			CMAKE_ARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>
		)

		ExternalProject_Get_Property(rapidjson INSTALL_DIR)
		include_directories("${INSTALL_DIR}/include")

		add_dependencies(mirror-external-deps rapidjson)
	endfunction()

	mirror_add_rapidjson()
endif()
