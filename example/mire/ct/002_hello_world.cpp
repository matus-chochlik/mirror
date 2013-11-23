/**
 *  @example mire/ct/002_hello_world.cpp
 *  @brief Basic example of Mirror Reflection compile-time utilities.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{002_hello_world}
 */

#include <mire/ct/string.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/ct/append.hpp>
#include <mire/ct/concat.hpp>
#include <iostream>

int main(void)
{
	using namespace mire::ct;

	typedef string<'H','e','l','l','o'> hello;
	typedef string<'W','o','r','l','d'> world;

	std::cout << c_str<
		concat<
			append_c<hello, char, ',',' '>,
			append_c<world, char, '!'>
		>
	>() << std::endl;

	return 0;
}
