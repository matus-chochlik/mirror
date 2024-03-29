# Copyright Matus Chochlik.
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at
#  http://www.boost.org/LICENSE_1_0.txt
#
include(Example.cmake)

add_subdirectory(testdecl)

mirror_add_simple_example(amount_of_foo)
mirror_add_simple_example(applicable_ops)
mirror_add_simple_example(are_consecutive)
mirror_add_simple_example(are_sorted_by_name)
mirror_add_simple_example(are_sorted_by_size)
mirror_add_simple_example(chai_on_mirror)
mirror_add_simple_example(ctre_integer_concept)
mirror_add_simple_example(enum_min_max)
mirror_add_simple_example(expression)
mirror_add_simple_example(filter)
mirror_add_simple_example(fake_rest_api)
mirror_add_simple_example(fake_rpc)
mirror_add_simple_example(find_if)
mirror_add_simple_example(find_longest_name)
mirror_add_simple_example(from_rapidjson)
mirror_add_simple_example(gen_puml_diagram)
mirror_add_simple_example(good_example)
mirror_add_simple_example(group_by)
mirror_add_simple_example(has_overloaded_functions)
mirror_add_simple_example(has_overloaded_functions_2)
mirror_add_simple_example(has_padding)
mirror_add_simple_example(hello_enums)
mirror_add_simple_example(hello_world)
mirror_add_simple_example(invoke)
mirror_add_simple_example(integral_data_members)
mirror_add_simple_example(interface_revision)
mirror_add_simple_example(is_bitfield_enum)
mirror_add_simple_example(list_structure)
mirror_add_simple_example(metaobject_concept)
mirror_add_simple_example(next_weekday)
mirror_add_simple_example(overload_arity)
mirror_add_simple_example(print_enumerators)
mirror_add_simple_example(print_full_name)
mirror_add_simple_example(print_months)
mirror_add_simple_example(print_op_results)
mirror_add_simple_example(print_struct)
mirror_add_simple_example(print_traits)
mirror_add_simple_example(remove_if)
mirror_add_simple_example(repeat_message_args)
mirror_add_simple_example(repeat_message_json)
mirror_add_simple_example(row_polymorphism)
mirror_add_simple_example(same_structure)
mirror_add_simple_example(simple_json)
mirror_add_simple_example(sort_by)
mirror_add_simple_example(sql_query_generator)
mirror_add_simple_example(to_json_string)
mirror_add_simple_example(to_rapidjson)


mirror_add_simple_example(puml_class_diagram)
target_link_libraries(mirror-puml_class_diagram PRIVATE mirror-testdecl)

find_program(SQLite3_COMMAND sqlite3)
if(SQLite3_FOUND AND SQLite3_COMMAND)
	add_custom_command(
		OUTPUT people.db
		COMMAND "${SQLite3_COMMAND}"
		ARGS people.db < "${CMAKE_CURRENT_SOURCE_DIR}/people.sql"
		WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}"
		DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/people.sql"
	)
	add_custom_target(mirror-people-db DEPENDS people.db)

	mirror_add_simple_example(fetch_from_sqlite)
	add_dependencies(mirror-fetch_from_sqlite mirror-people-db)
endif()

add_subdirectory(factory)
