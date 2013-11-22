/**
 *  @example mire/ct/001_hello_world.cpp
 *  @brief Very basic example of Mirror Reflection compile-time utilities.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#include <mire/ct/string.hpp>
#include <mire/ct/c_str.hpp>
#include <iostream>

int main(void)
{
	using namespace mire::ct;

	typedef string<'H','e','l','l','o',',',' ','W','o','r','l','d','!'> hello_world;

	std::cout << c_str<hello_world>() << std::endl;

	return 0;
}
