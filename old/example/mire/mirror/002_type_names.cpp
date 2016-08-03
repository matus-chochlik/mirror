/**
 *  @example mire/mirror/002_type_names.cpp
 *  @brief Basic example showing type reflection and the base_name metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{002_type_names}
 */

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/full_name.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/native.hpp>
#include <iostream>

template <typename T>
void print_typename(void)
{
	using mire::ct::c_str;
	using mire::mirror::full_name;
	using mire::mirror::mirrored_t;

	std::cout << c_str<
		full_name<
			mirrored_t<T>
		>
	>() << std::endl;
}

int main(void)
{
	print_typename<int>();
	print_typename<decltype(1ull)>();
	print_typename<long [10]>();
	print_typename<double (&) [16]>();
	print_typename<char const>();
	print_typename<int volatile>();
	print_typename<char *>();
	print_typename<char const []>();
	print_typename<double &>();
	print_typename<double &&>();
	print_typename<decltype("mirror")>();
	print_typename<short [9][8][7][6][5][4][3][2][1]>();
	print_typename<long const * volatile &>();
	print_typename<unsigned char *******>();
	print_typename<bool const * const * const * &&>();
	print_typename<long volatile * const [][1234]>();
	print_typename<void(void)>();
	print_typename<long(void)>();
	print_typename<void(long)>();
	print_typename<long*(long)>();
	print_typename<long(*)(long)>();
	print_typename<short*(**)(void)>();
	print_typename<short**(*)(void)>();
	print_typename<long(wchar_t, int, long, float)>();
	print_typename<float(*(*)(unsigned))(long)>();
	print_typename<long const* (*)(const char* [])>();
	print_typename<int volatile& (*)(int volatile&)>();
	print_typename<float(*(*)(int, bool, float))(double, char, int)>();
	print_typename<float(*(*(*(*(*(*(*)(bool))(char))(wchar_t))(short))(int))(float))(long)>();

	return 0;
}
