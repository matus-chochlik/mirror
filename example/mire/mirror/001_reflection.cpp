/**
 *  @example mire/mirror/001_reflection.cpp
 *  @brief Basic example showing the reflection expressions.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{001_reflection}
 */

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/base_name.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/pair.hpp>
#include <iostream>

int main(void)
{
	typedef MIRRORED_GLOBAL_SCOPE() meta_gs;
	typedef MIRRORED(std) meta_std;
	typedef MIRRORED(std::pair) meta_std_pair;

	using namespace mire::ct;
	using namespace mire::mirror;

	typedef mirrored_t<int> meta_int;
	typedef mirrored_t<std::pair<int, float>> meta_std_pair_int_float;

	std::cout << c_str<base_name<meta_gs>>() << std::endl;
	std::cout << c_str<base_name<meta_std>>() << std::endl;
	std::cout << c_str<base_name<meta_std_pair>>() << std::endl;
	std::cout << c_str<base_name<meta_int>>() << std::endl;
	std::cout << c_str<base_name<meta_std_pair_int_float>>() << std::endl;

	return 0;
}
