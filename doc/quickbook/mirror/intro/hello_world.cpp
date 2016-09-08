/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[mirror_example_hello_world_1
#include <mirror/reflection.hpp> /*<
This header implements the [^__MIRRORED] reflection operator.
>*/
#include <mirror/get_base_name.hpp> /*<
The individual metaobject operations are implemented in separate header files.
>*/
#include <mirror/get_scope.hpp>
#include <mirror/concat.hpp>
#include <mirror/push_back.hpp>
#include <mirror/c_str.hpp>
#include <iostream>

namespace Hello { struct World { }; }

int main(void)
{
	using namespace mirror;

	using mo = __MIRRORED(Hello::World);

	using hello = __get_base_name<get_scope<mo>>;
	using world = __get_base_name<mo>;

	using hello_world = __concat<
		__push_back<hello, char_<','>>,
		__string<' '>,
		push_back<world, char_<'!'>>
	>;

	std::cout << __c_str<hello_world> << std::endl;
	return 0;
}
//]

