/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[puddle_example_hello_world_1
#include <puddle/reflection.hpp> /*<
This header implements the [^__PUDDLED] reflection operator.
>*/
#include <puddle/metaobject_ops.hpp> /*<
This header implements the metaobject operations, like [^__get_base_name], etc.
>*/
#include <puddle/string.hpp> /*<
This header implements the compile-time string operations, like concatenation,
output to [^std::ostream]s, etc.
>*/
#include <iostream>

namespace Hello { struct World { }; }

int main(void)
{
	using namespace puddle;

	auto mo = __PUDDLED(Hello::World);

	auto hello = __get_base_name(__get_scope(mo));
	auto world = get_base_name(mo);

	auto hello_world = hello + __string<',',' '> + world + string<'!'>;

	std::cout << hello_world << std::endl;
	return 0;
}
//]

