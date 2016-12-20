/**
 * @example lagoon/001_hello_world.cpp
 * @brief Hello world example
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <lagoon/metaobject_registry.hpp>
#include <lagoon/metaobject.hpp>
#include <puddle/reflection.hpp>
#include <iostream>

namespace Hello { struct World { }; }

int main(void)
{
	using namespace lagoon;

	metaobject_registry reg;

	reg << PUDDLED(Hello);
	auto mo = reg << PUDDLED(Hello::World);

	std::string_view hello = mo.get_scope().get_base_name();
	std::string_view world = mo.get_base_name();

	std::cout << hello << ", " << world << '!' << std::endl;
	return 0;
}
