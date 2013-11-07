/**
 *  .file test/mire/ct/find.cpp
 *  .brief Test case for compile-time find meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_find
#include <boost/test/unit_test.hpp>

#include <mire/ct/find.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_find)

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_find_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		find<range<>, range<>>,
		range<>
	>, true>();

	mire_ct_test_bool<equal<
		find<range<bool, char, short>, range<int, long>>,
		range<>
	>, true>();

	mire_ct_test_bool<equal<
		find<range<bool, char, short, int>, range<bool, char, short, int>>,
		range<bool, char, short, int>
	>, true>();

	mire_ct_test_bool<equal<
		find<range<bool, char, short, int, long, bool>, range<bool>>,
		range<bool, char, short, int, long, bool>
	>, true>();

	mire_ct_test_bool<equal<
		find<range<bool, char, short, int, long, bool>, range<bool, char>>,
		range<bool, char, short, int, long, bool>
	>, true>();

	mire_ct_test_bool<equal<
		find<range<bool, char, short, int, long>, range<char, short>>,
		range<char, short, int, long>
	>, true>();

	mire_ct_test_bool<equal<
		find<range<bool, char, short, int, long>, range<int, long>>,
		range<int, long>
	>, true>();

	mire_ct_test_bool<equal<
		find<range<bool, char, short, int, long>, range<long>>,
		range<long>
	>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_find_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		find<string<>, string<>>,
		string<>
	>, true>();

	mire_ct_test_bool<equal<
		find<string<'a','b','c'>, string<'x','y'>>,
		string<>
	>, true>();

	mire_ct_test_bool<equal<
		find<string<'s','t','r','i','n','g','s'>, string<'s'>>,
		string<'s','t','r','i','n','g','s'>
	>, true>();

	mire_ct_test_bool<equal<
		find<string<'s','t','r','i','n','g','s'>, string<'t','r','i'>>,
		string<'t','r','i','n','g','s'>
	>, true>();

	mire_ct_test_bool<equal<
		find<string<'s','t','r','i','n','g','s'>, string<'i','n','g'>>,
		string<'i','n','g','s'>
	>, true>();
}

BOOST_AUTO_TEST_SUITE_END()

