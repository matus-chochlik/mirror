/**
 *  .file test/mire/ct/c_str.cpp
 *  .brief Test case for compile-time c_str meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_c_str
#include <boost/test/unit_test.hpp>

#include <mire/ct/c_str.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_c_str)

BOOST_AUTO_TEST_CASE(mire_ct_string_c_str)
{
	using namespace mire::ct;

	BOOST_CHECK(std::strcmp(
		c_str<empty_string>::value,
		""
	) == 0);

	BOOST_CHECK(std::strcmp(
		c_str<string<'s'>>::value,
		"s"
	) == 0);

	BOOST_CHECK(std::strcmp(
		c_str<string<'a','b','c','d'>>::value,
		"abcd"
	) == 0);

	BOOST_CHECK(std::strcmp(
		c_str<string<'a','b','c','d','e','f','g','h'>>::value,
		"abcdefgh"
	) == 0);

	BOOST_CHECK(std::wcscmp(
		c_str<basic_string<wchar_t, L'S',L't',L'r',L'i',L'n',L'g'>>::value,
		L"String"
	) == 0);
}

BOOST_AUTO_TEST_SUITE_END()

