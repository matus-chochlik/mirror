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

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_contains_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<contains<
		range<char, float, double>,
		range<>
	>, true>();

	mire_ct_test_bool<contains<
		range<char, float, double>,
		range<char>
	>, true>();

	mire_ct_test_bool<contains<
		range<char, float, double>,
		range<char, float>
	>, true>();

	mire_ct_test_bool<contains<
		range<char, float, double>,
		range<float, double>
	>, true>();

	mire_ct_test_bool<contains<
		range<char>,
		range<char, float, double>
	>,false>();

	mire_ct_test_bool<contains<
		range<bool, char, short, int, float, double>,
		range<bool, char, short>
	>, true>();

	mire_ct_test_bool<contains<
		range<bool, char, short, int, float, double>,
		range<char, short, int>
	>, true>();

	mire_ct_test_bool<contains<
		range<bool, char, short, int, float, double>,
		range<short, int, float, double>
	>, true>();

	mire_ct_test_bool<contains<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double>
	>, true>();

	mire_ct_test_bool<contains<
		range<bool, char, short, int, float, double>,
		range<long, bool, char, short, int, float, double>
	>,false>();

	mire_ct_test_bool<contains<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double, long>
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_contains_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<contains<
		string<'c'>,
		string<>
	>, true>();

	mire_ct_test_bool<contains<
		string<>,
		string<'c'>
	>,false>();

	mire_ct_test_bool<contains<
		string<'s','t','r'>,
		string<'t'>
	>, true>();

	mire_ct_test_bool<contains<
		string<'s','t','r'>,
		string<'s','t'>
	>, true>();

	mire_ct_test_bool<contains<
		string<'s','t','r'>,
		string<'t','r'>
	>, true>();

	mire_ct_test_bool<contains<
		string<'s','t','r'>,
		string<'s','t','r'>
	>, true>();

	mire_ct_test_bool<contains<
		string<'s','t','r'>,
		string<'s','t','r','i','n','g'>
	>,false>();

	mire_ct_test_bool<contains<
		string<'s','t','r','i','n','g'>,
		string<'s','t','r'>
	>, true>();

	mire_ct_test_bool<contains<
		string<'s','t','r','i','n','g'>,
		string<'t','r','i'>
	>, true>();

	mire_ct_test_bool<contains<
		string<'s','t','r','i','n','g'>,
		string<'r','i','n'>
	>, true>();

	mire_ct_test_bool<contains<
		string<'s','t','r','i','n','g'>,
		string<'i','n','g'>
	>, true>();
}

BOOST_AUTO_TEST_SUITE_END()

