#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
install(DIRECTORY ${PROJECT_BINARY_DIR}/include/ DESTINATION include)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/implement/ DESTINATION include)
