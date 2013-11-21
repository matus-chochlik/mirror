#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
enable_testing()
include(CTest)

function(add_mire_test COMPONENT TEST_NAME BUILD_ONLY)

	add_executable(${TEST_NAME} EXCLUDE_FROM_ALL ${TEST_NAME}.cpp)
	target_link_libraries(${TEST_NAME} ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY})
	set_property(TARGET ${TEST_NAME} PROPERTY FOLDER "Test/${COMPONENT}")

	add_test(
		build-test-${COMPONENT}-${TEST_NAME}
		"${CMAKE_COMMAND}"
		--build ${CMAKE_BINARY_DIR}
		--target ${TEST_NAME}
	)
	set_tests_properties(
		build-test-${COMPONENT}-${TEST_NAME}
		PROPERTIES FOLDER
		"Test/${COMPONENT}"
	)

	if(NOT(${BUILD_ONLY}))
		add_test(exec-test-${COMPONENT}-${TEST_NAME} ${TEST_NAME})
		set_tests_properties(
			exec-test-${COMPONENT}-${TEST_NAME}
			PROPERTIES DEPENDS
			build-test-${COMPONENT}-${TEST_NAME}
		)
		set_tests_properties(
			exec-test-${COMPONENT}-${TEST_NAME}
			PROPERTIES FOLDER
			"Test/${COMPONENT}"
		)
	endif()
endfunction()

function(add_mire_build_test COMPONENT TEST_NAME)
	add_mire_test(${COMPONENT} ${TEST_NAME} TRUE)
endfunction()

function(add_mire_exec_test COMPONENT TEST_NAME)
	add_mire_test(${COMPONENT} ${TEST_NAME} FALSE)
endfunction()
