/**
 *  .file test/mire/ct/starts_with.cpp
 *  .brief Test case for compile-time starts_with meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_starts_with
#include <boost/test/unit_test.hpp>

#include <mire/ct/starts_with.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_starts_with)

BOOST_AUTO_TEST_CASE(mire_ct_starts_with_range)
{
	using namespace mire::ct;

	BOOST_CHECK((starts_with<
		range<>,
		range<>
	>::value));

	BOOST_CHECK((starts_with<
		range<char, float, double>,
		range<>
	>::value));

	BOOST_CHECK((starts_with<
		range<char, float, double>,
		range<char>
	>::value));

	BOOST_CHECK((!starts_with<
		range<char>,
		range<char, float, double>
	>::value));

	BOOST_CHECK((starts_with<
		range<bool, char, short, int, float, double>,
		range<bool, char, short>
	>::value));

	BOOST_CHECK((!starts_with<
		range<bool, char, short, int, float, double>,
		range<char, short, int>
	>::value));

	BOOST_CHECK((!starts_with<
		range<char, wchar_t, short, int, long, long long, double>,
		range<unsigned, float>
	>::value));

	BOOST_CHECK((starts_with<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double>
	>::value));

	BOOST_CHECK((!starts_with<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double, long double>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_starts_with_string)
{
	using namespace mire::ct;

	BOOST_CHECK((starts_with<
		string<>,
		string<>
	>::value));

	BOOST_CHECK((starts_with<
		string<'c'>,
		string<>
	>::value));

	BOOST_CHECK((!starts_with<
		string<>,
		string<'c'>
	>::value));

	BOOST_CHECK((starts_with<
		string<'s','t','r'>,
		string<'s'>
	>::value));

	BOOST_CHECK((starts_with<
		string<'s','t','r'>,
		string<'s','t','r'>
	>::value));

	BOOST_CHECK((!starts_with<
		string<'s','t','r'>,
		string<'s','t','r','i','n','g'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

