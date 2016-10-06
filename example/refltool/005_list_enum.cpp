/**
 * @example refltool/005_list_enum.cpp
 * @brief Shows how to list all enum names and values
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <refltool/tie_enumerators.hpp>
#include <refltool/enum_to_string.hpp>
#include <iostream>

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

int main(void)
{
	using namespace refltool;

	for(E e : tie_enumerators<E>())
	{
		std::cout
			<< enum_to_string(e)
			<< " = "
			<< int(e)
			<< std::endl;
	}

	return 0;
}

