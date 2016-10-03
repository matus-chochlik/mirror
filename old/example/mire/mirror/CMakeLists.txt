#  Copyright 2013 Matus Chochlik. Distributed under the Boost
#  Software License, Version 1.0. (See accompanying file
#  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
#
cmake_minimum_required(VERSION 2.8)

add_custom_target(examples-mire-mirror)
add_dependencies(examples examples-mire-mirror)
set_property(TARGET examples-mire-mirror PROPERTY FOLDER "Examples/mire/mirror")

add_mire_examples(mire/mirror)
