/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[refltool_example_string_to_enum_1
#include <refltool/string_to_enum.hpp>
#include <iostream>
//]
//[refltool_example_string_to_enum_2
enum E {
	a = 1 << 0,
	b = 1 << 1,
	c = 1 << 2,
	d = 1 << 3,
	e = 1 << 4,
	f = 1 << 5,
	g = 1 << 6,
	h = 1 << 7,
	i = 1 << 8
};
//]
//[refltool_example_string_to_enum_3
int main(void)
{
	using namespace refltool;

	const char* names[] = {"a", "b", "c", "d", "e", "f", "g", "h", "i"};

	for(auto n : names)
	{
		std::cout
			<< n
			<< " = "
			<< int(__string_to_enum<E>(n))
			<< std::endl;
	}

	return 0;
}
//]
//[refltool_example_string_to_enum_output
a = 1
b = 2
c = 4
d = 8
e = 16
f = 32
g = 64
h = 128
i = 256
//]
