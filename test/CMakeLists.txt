#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 2.8)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

if(Boost_FOUND)
	enable_testing()
	add_subdirectory("reflexpr")
	add_subdirectory("mirror")
	add_subdirectory("puddle")
	add_subdirectory("lagoon")
	add_subdirectory("refltool")
else()
	message(WARNING "Boost.Test required for testing but not found")
endif()
