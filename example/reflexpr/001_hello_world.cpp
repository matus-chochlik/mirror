/**
 * @example reflexpr/001_hello_world.cpp
 * @brief Very basic example of the usage of reflexpr
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>
#include <cassert>

namespace Hello { struct World { }; }

int main(void)
{
	using namespace std;

	using meta_HW = reflexpr(Hello::World);

	assert(is_metaobject_v<meta_HW>);

	cout << meta::get_base_name_v<meta::get_scope_m<meta_HW>>;
	cout << ", ";
	cout << meta::get_base_name_v<meta_HW>;
	cout << "." << std::endl;

	return 0;
}
