#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
file(WRITE "${PROJECT_SOURCE_DIR}/BINARY_DIR" "${PROJECT_BINARY_DIR}")
file(WRITE "${PROJECT_BINARY_DIR}/SOURCE_DIR" "${PROJECT_SOURCE_DIR}")
file(WRITE "${PROJECT_BINARY_DIR}/REFLEXPR_DIR" "${REFLEXPR_INCLUDE_DIR}")

configure_file(
	"${PROJECT_SOURCE_DIR}/config/tools/bash-complete-mirror"
	"${PROJECT_BINARY_DIR}/" COPYONLY
)
configure_file(
	"${PROJECT_SOURCE_DIR}/config/tools/run_test-mirror"
	"${PROJECT_BINARY_DIR}/" COPYONLY
)
configure_file(
	"${PROJECT_SOURCE_DIR}/config/tools/run_example-mirror"
	"${PROJECT_BINARY_DIR}/" COPYONLY
)
configure_file(
	"${PROJECT_SOURCE_DIR}/config/tools/reconfig-mirror"
	"${PROJECT_BINARY_DIR}/" COPYONLY
)
