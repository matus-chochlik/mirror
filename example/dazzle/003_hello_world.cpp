/**
 * @example dazzle/003_hello_world.cpp
 * @brief Hello world example
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/string.hpp>
#include <dazzle/metaobject.hpp>
#include <dazzle/reflection.hpp>
#include <iostream>

namespace Hello { struct World { }; }

int main(void)
{
	using namespace dazzle;

	auto mo = DAZZLED(Hello::World);

	auto hello = mo.get_scope().get_base_name();
	auto world = mo.get_base_name();

	auto hello_world = hello + string<',',' '> + world + string<'!'>;

	std::cout << hello_world << std::endl;
	return 0;
}
