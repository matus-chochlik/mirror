/**
 *  @example mire/mirror/003_type_names.cpp
 *  @brief Basic example showing type reflection and the full_name metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{003_type_names}
 */

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/full_name.hpp>
#include <mire/mirror/typedef_type.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/std/wstring.hpp>
#include <mire/reg/std/pair.hpp>
#include <iostream>

template <typename MetaType>
void print_name(void)
{
	using mire::ct::c_str;
	using mire::mirror::full_name;

	std::cout << c_str<
		full_name<MetaType>
	>() << std::endl;
}

int main(void)
{
	using mire::mirror::mirrored_t;
	using mire::mirror::typedef_type;

	print_name<mirrored_t<std::string>>();
	print_name<typedef_type<mirrored_t<std::string>>>();

	print_name<mirrored_t<std::wstring>>();
	print_name<typedef_type<mirrored_t<std::wstring>>>();

	print_name<mirrored_t<std::pair<std::pair<bool, char>, std::pair<int, float>>>>();

	print_name<mirrored_t<const std::pair<long, std::string const * volatile> [123]>>();
	print_name<mirrored_t<std::pair<double, std::string * const *>* (*)(std::wstring&&)>>();

	return 0;
}
