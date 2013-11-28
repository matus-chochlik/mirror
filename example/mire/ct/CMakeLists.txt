#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

add_custom_target(examples-mire-ct)
add_dependencies(examples examples-mire-ct)
set_property(TARGET examples-mire-ct PROPERTY FOLDER "Examples/mire/ct")

add_mire_examples(mire/ct)
