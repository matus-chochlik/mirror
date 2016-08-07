/**
 * @example mirror/hello_world.cpp
 * @brief Very basic example of Mirror Reflection compile-time utilities.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/string.hpp>
#include <mirror/c_str.hpp>
#include <iostream>

int main(void)
{
	using namespace mirror;

	using hello = string<'H','e','l','l','o',',',' ','W','o','r','l','d','!'>;

	std::cout << c_str<hello> << std::endl;
	return 0;
}
