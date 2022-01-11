#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
add_library(Mirror::Deps::System INTERFACE IMPORTED)

if(UNIX AND NOT APPLE)
	add_library(Mirror::Deps::RunTime INTERFACE IMPORTED)
	set_target_properties(
		Mirror::Deps::RunTime PROPERTIES
		INTERFACE_LINK_LIBRARIES rt
	)

add_library(Mirror::Deps::DynLink INTERFACE IMPORTED)
	set_target_properties(
		Mirror::Deps::DynLink PROPERTIES
		INTERFACE_LINK_LIBRARIES dl
	)

	set_target_properties(
		Mirror::Deps::System PROPERTIES
		INTERFACE_LINK_LIBRARIES
		"Mirror::Deps::RunTime;Mirror::Deps::DynLink"
	)
endif()
