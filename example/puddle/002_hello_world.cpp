/**
 * @example puddle/hello_world.cpp
 * @brief Hellow world example
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <puddle/string.hpp>
#include <iostream>

int main(void)
{
	using namespace puddle;

	auto hello = string<'H','e','l','l','o'>;
	auto world = string<'W','o','r','l','d'>;

	auto hello_world = hello + string<',',' '> + world + string<'!'>;

	std::cout << hello_world << std::endl;
	return 0;
}
