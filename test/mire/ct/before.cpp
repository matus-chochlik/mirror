/**
 *  .file test/mire/ct/before.cpp
 *  .brief Test case for compile-time before meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_before
#include <boost/test/unit_test.hpp>

#include <mire/ct/before.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_before)

BOOST_AUTO_TEST_CASE(mire_ct_before_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		before<range<>, range<>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		before<range<bool, char, short>, range<int, long>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		before<range<bool, char, short, int>, range<bool, char, short, int>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		before<range<bool, char, short, int, long, bool>, range<bool>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		before<range<bool, char, short, int, long, bool>, range<long, bool>>,
		range<bool, char, short, int>
	>::value));

	BOOST_CHECK((equal<
		before<range<bool, char, short, int, long, double>, range<double>>,
		range<bool, char, short, int, long>
	>::value));

	BOOST_CHECK((equal<
		before<range<bool, char, short, int, long>, range<>>,
		range<>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_before_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		before<string<>, string<>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		before<string<'a','b','c'>, string<'x','y'>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		before<string<'s','t','r'>, string<'s','t','r'>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		before<string<'s','t','r'>, string<'s'>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		before<string<'s','t','r','i','n','g'>, string<'i','n','g'>>,
		string<'s','t','r'>
	>::value));

	BOOST_CHECK((equal<
		before<string<'s','t','r','i','n','g'>, string<'g'>>,
		string<'s','t','r','i','n'>
	>::value));

	BOOST_CHECK((equal<
		before<string<'s','t','r','i','n','g'>, string<>>,
		string<>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

