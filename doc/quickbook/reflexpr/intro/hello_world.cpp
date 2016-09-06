/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[reflexpr_example_hello_world_1
#include <__reflexpr__> /*<
This header implements the metaobject operation templates.
>*/
#include <iostream>

namespace Hello {

struct World { };

} // namespace Hello

int main(void)
{
	using namespace std;

	using meta_HW = __reflexpr(Hello::World); /*<
	Reflect the [^Hello::World] [^struct], the [^meta_HW] type is
	a ['[link reflexpr.intro.metaobjects metaobject]].
	>*/

	cout << __meta_get_base_name_v<__meta_get_scope_m<meta_HW>>;
	cout << ", ";
	cout << __meta_get_base_name_v<meta_HW>;
	cout << "." << std::endl;

	return 0;
}
//]

