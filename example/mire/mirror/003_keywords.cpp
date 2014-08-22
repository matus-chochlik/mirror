/**
 *  @example mire/mirror/003_keywords.cpp
 *  @brief Example showing basic work with specifiers and the keyword metafunction
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{003_keywords}
 */

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/elaborated_type.hpp>
#include <mire/mirror/keyword.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/specifier.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/std/pair.hpp>
#include <iostream>

template <typename MetaSpecifier>
void print_keyword(void)
{
	using mire::ct::c_str;
	using mire::mirror::keyword;

	std::cout << c_str<
		keyword<
			MetaSpecifier
		>
	>() << std::endl;
}

int main(void)
{
	print_keyword<MIRRORED(thread_local)>();
	print_keyword<MIRRORED(volatile)>();
	print_keyword<MIRRORED(virtual)>();
	print_keyword<MIRRORED(static)>();

	using mire::mirror::elaborated_type;
	using mire::mirror::mirrored_t;

	print_keyword<elaborated_type<mirrored_t<int>>>();
	print_keyword<elaborated_type<mirrored_t<std::string>>>();
	print_keyword<elaborated_type<mirrored_t<std::pair<int, float>>>>();

	return 0;
}
