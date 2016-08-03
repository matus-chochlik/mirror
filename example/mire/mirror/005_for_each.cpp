/**
 *  @example mire/mirror/005_for_each.cpp
 *  @brief Shows the for_each function, reflection and the base_name metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @mire_example_output{005_for_each}
 */

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/full_name.hpp>
#include <mire/mirror/keyword.hpp>
#include <mire/mirror/elaborated_type.hpp>
#include <mire/ct/if.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/ct/range.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/empty.hpp>
#include <mire/ct/concat.hpp>
#include <mire/ct/for_each.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/string.hpp>
#include <mire/reg/std/vector.hpp>
#include <mire/reg/std/pair.hpp>
#include <iostream>

struct print_typename
{
	template <typename IterInfo>
	void operator()(IterInfo) const
	{
		using mire::ct::if_;
		using mire::ct::c_str;
		using mire::ct::concat;
		using mire::ct::empty;
		using mire::ct::string;
		using mire::mirror::full_name;
		using mire::mirror::keyword;
		using mire::mirror::elaborated_type;
		using mire::mirror::mirrored_t;

		typedef typename IterInfo::type T;
		typedef mirrored_t<T> meta_T;

		std::cout << c_str<
			concat<
				if_<
					empty<
						keyword<
							elaborated_type<meta_T>
						>
					>,
					string<'t','y','p','e',':',' '>,
					concat<
						keyword<
							elaborated_type<meta_T>
						>,
						string<':',' '>
					>
				>,
				full_name<meta_T>
			>
		>() << std::endl;
	}
};

int main(void)
{
	using mire::ct::range;
	using mire::ct::for_each;

	for_each<range<
		int,
		std::string,
		std::string*,
		std::pair<std::string, std::vector<long>>,
		unsigned long long [10],
		std::string (&) [16],
		std::vector<char> const,
		int volatile,
		char *,
		char const [],
		const std::vector<double> &,
		std::vector<double> &&,
		short [9][8][7][6][5][4][3][2][1],
		long const * volatile &,
		std::pair<unsigned, char> *******,
		bool const * const * const * &&,
		long volatile * const [][1234],
		void(void),
		long(void),
		void(long),
		long*(long),
		long(*)(long),
		short*(**)(void),
		short**(*)(void),
		long(wchar_t, int, long, float),
		float(*(*)(std::pair<unsigned, double>*))(long),
		long const* (*)(const char* []),
		int volatile& (*)(int volatile&),
		std::string (*(*)(int, bool, std::string))(double, char, int),
		float(*(*(*(*(*(*(*)(bool))(char))(wchar_t))(short))(int))(float))(long)
	>>(print_typename());

	return 0;
}
