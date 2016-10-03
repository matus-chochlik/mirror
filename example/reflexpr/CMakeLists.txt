#  Copyright Matus Chochlik.
#  Distributed under the Boost Software License, Version 1.0.
#  See accompanying file LICENSE_1_0.txt or copy at
#   http://www.boost.org/LICENSE_1_0.txt
#
cmake_minimum_required(VERSION 2.8)

add_custom_target(examples-reflexpr)
add_dependencies(examples examples-reflexpr)
set_property(TARGET examples-reflexpr PROPERTY FOLDER "Examples/reflexpr")

add_examples(reflexpr)
