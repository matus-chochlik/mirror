/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_example_enum_to_string_1
#include <refltool/tie_enumerators.hpp>
#include <refltool/enum_to_string.hpp>
#include <iostream>
//]
//[refltool_example_enum_to_string_2
enum E {
	a = 1 << 0,
	b = 1 << 1,
	c = 1 << 2,
	d = 1 << 3,
	e = 1 << 4,
	f = 1 << 5,
	g = 1 << 6,
	h = 1 << 7
};
//]
//[refltool_example_enum_to_string_3
int main(void)
{
	using namespace refltool;

	for(E e : __tie_enumerators<E>())
	{
		std::cout
			<< __enum_to_string(e)
			<< " = "
			<< int(e)
			<< std::endl;
	}

	return 0;
}
//]
//[refltool_example_enum_to_string_output
a = 1
b = 2
c = 4
d = 8
e = 16
f = 32
g = 64
h = 128
//]
