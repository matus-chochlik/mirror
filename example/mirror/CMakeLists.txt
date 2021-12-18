# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
include(Example.cmake)

mirror_add_simple_example(find_if)
mirror_add_simple_example(print_enumerators)
mirror_add_simple_example(print_struct)
mirror_add_simple_example(next_weekday)
mirror_add_simple_example(print_months)
mirror_add_simple_example(has_padding)
mirror_add_simple_example(invoke)
mirror_add_simple_example(gen_puml_diagram)
mirror_add_simple_example(print_full_name)

add_subdirectory(factory)
