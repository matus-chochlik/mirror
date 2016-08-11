/**
 * @example mirror/002_hello_world.cpp
 * @brief Very basic example of Mirror Reflection compile-time utilities.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/string.hpp>
#include <mirror/concat.hpp>
#include <mirror/push_back.hpp>
#include <mirror/c_str.hpp>
#include <iostream>

int main(void)
{
	using namespace mirror;

	using hello = string<'H','e','l','l','o'>;
	using world = string<'W','o','r','l','d'>;

	using hello_world = concat<
		push_back<hello, char_<','>>,
		string<' '>,
		push_back<world, char_<'!'>>
	>;

	std::cout << c_str<hello_world> << std::endl;
	return 0;
}
