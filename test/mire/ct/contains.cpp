/**
 *  .file test/mire/ct/contains.cpp
 *  .brief Test case for compile-time contains meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_contains
#include <boost/test/unit_test.hpp>

#include <mire/ct/contains.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_contains)

BOOST_AUTO_TEST_CASE(mire_ct_contains_range)
{
	using namespace mire::ct;

	BOOST_CHECK((contains<
		range<char, float, double>,
		range<>
	>::value));

	BOOST_CHECK((contains<
		range<char, float, double>,
		range<char>
	>::value));

	BOOST_CHECK((contains<
		range<char, float, double>,
		range<char, float>
	>::value));

	BOOST_CHECK((contains<
		range<char, float, double>,
		range<float, double>
	>::value));

	BOOST_CHECK((!contains<
		range<char>,
		range<char, float, double>
	>::value));

	BOOST_CHECK((contains<
		range<bool, char, short, int, float, double>,
		range<bool, char, short>
	>::value));

	BOOST_CHECK((contains<
		range<bool, char, short, int, float, double>,
		range<char, short, int>
	>::value));

	BOOST_CHECK((contains<
		range<bool, char, short, int, float, double>,
		range<short, int, float, double>
	>::value));

	BOOST_CHECK((contains<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double>
	>::value));

	BOOST_CHECK((!contains<
		range<bool, char, short, int, float, double>,
		range<long, bool, char, short, int, float, double>
	>::value));

	BOOST_CHECK((!contains<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double, long>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_contains_string)
{
	using namespace mire::ct;

	BOOST_CHECK((contains<
		string<'c'>,
		string<>
	>::value));

	BOOST_CHECK((!contains<
		string<>,
		string<'c'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r'>,
		string<'t'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r'>,
		string<'s','t'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r'>,
		string<'t','r'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r'>,
		string<'s','t','r'>
	>::value));

	BOOST_CHECK((!contains<
		string<'s','t','r'>,
		string<'s','t','r','i','n','g'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r','i','n','g'>,
		string<'s','t','r'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r','i','n','g'>,
		string<'t','r','i'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r','i','n','g'>,
		string<'r','i','n'>
	>::value));

	BOOST_CHECK((contains<
		string<'s','t','r','i','n','g'>,
		string<'i','n','g'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

