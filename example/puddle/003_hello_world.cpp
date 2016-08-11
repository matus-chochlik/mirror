/**
 * @example puddle/003_hello_world.cpp
 * @brief Hello world example
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <puddle/string.hpp>
#include <puddle/metaobject_ops.hpp>
#include <puddle/reflection.hpp>
#include <iostream>

namespace Hello { struct World { }; }

int main(void)
{
	using namespace puddle;

	auto mo = PUDDLED(Hello::World);

	auto hello = get_base_name(get_scope(mo));
	auto world = get_base_name(mo);

	auto hello_world = hello + string<',',' '> + world + string<'!'>;

	std::cout << hello_world << std::endl;
	return 0;
}
