/**
 *  .file test/mire/mirror/full_name.cpp
 *  .brief Test case for compile-time full_name meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_MIRROR_full_name
#include <boost/test/unit_test.hpp>

#include <mire/mirror/reflection.hpp>
#include <mire/mirror/base_name.hpp>
#include <mire/mirror/full_name.hpp>
#include <mire/ct/c_str.hpp>
#include <mire/reg/native.hpp>
#include <mire/reg/std/pair.hpp>
#include <mire/reg/std/basic_string.hpp>

#include <cctype>

BOOST_AUTO_TEST_SUITE(mire_mirror_full_name)

bool mire_mirror_name_equal(const char* s1, const char* s2)
{
	assert(s1 && s2);
	while(true)
	{
		while(*s1 && std::isspace(*s1)) ++s1;
		while(*s2 && std::isspace(*s2)) ++s2;

		if(!*s1) break;
		if(!*s2) break;

		if(*s1++ != *s2++) return false;
	}
	return (!*s1) && (!*s2);
}

BOOST_AUTO_TEST_CASE(mire_mirror_full_name_test1)
{
	using namespace mire;
	using namespace mire::mirror;

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::string
		>>>::value,
		"std::basic_string<char, std::char_traits<char>, std::allocator<char>>"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<base_name<mirrored_t<
			std::string*
		>>>::value,
		"basic_string<char, char_traits<char>, allocator<char>>*"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::wstring
		>>>::value,
		"std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::pair<std::string, std::wstring>
		>>>::value,
		"std::pair<"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>>,"
		"  std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>"
		">"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			std::pair<std::string * const, std::string const *>
		>>>::value,
		"std::pair<"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> * const,"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> const * "
		">"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			const std::pair<std::string * const *, std::string const * *> * [10][9]
		>>>::value,
		"std::pair<"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> * const *,"
		"  std::basic_string<char, std::char_traits<char>, std::allocator<char>> const * *"
		"> const * [10][9]"
	));

	BOOST_CHECK(mire_mirror_name_equal(
		ct::c_str<full_name<mirrored_t<
			const std::pair<
				std::pair<long volatile, std::string * const *>,
				std::pair<std::string, long double const * volatile *>
			> & (std::pair<std::string, std::wstring> &&)
		>>>::value,
		"std::pair<"
		"  std::pair<"
		"    long int volatile,"
		"    std::basic_string<char, std::char_traits<char>, std::allocator<char>> * const *"
		"  >,"
		"  std::pair<"
		"    std::basic_string<char, std::char_traits<char>, std::allocator<char>>,"
		"    long double const * volatile *"
		"  >"
		"> const & (std::pair<"
		"    std::basic_string<char, std::char_traits<char>, std::allocator<char>>,"
		"    std::basic_string<wchar_t, std::char_traits<wchar_t>, std::allocator<wchar_t>>"
		">&&)"
	));
}

BOOST_AUTO_TEST_SUITE_END()

