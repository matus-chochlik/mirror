#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
configure_file(
	"${PROJECT_SOURCE_DIR}/config/tools/complete-run_test"
	"${PROJECT_BINARY_DIR}/" COPYONLY
)
configure_file(
	"${PROJECT_SOURCE_DIR}/config/tools/run_test-mirror"
	"${PROJECT_BINARY_DIR}/" COPYONLY
)
configure_file(
	"${PROJECT_SOURCE_DIR}/config/tools/reconfig-mirror"
	"${PROJECT_BINARY_DIR}/" COPYONLY
)
