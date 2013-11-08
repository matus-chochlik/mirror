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

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_starts_with_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<starts_with<
		range<>,
		range<>
	>, true>();

	mire_ct_test_bool<starts_with<
		range<char, float, double>,
		range<>
	>, true>();

	mire_ct_test_bool<starts_with<
		range<char, float, double>,
		range<char>
	>, true>();

	mire_ct_test_bool<starts_with<
		range<char>,
		range<char, float, double>
	>,false>();

	mire_ct_test_bool<starts_with<
		range<bool, char, short, int, float, double>,
		range<bool, char, short>
	>, true>();

	mire_ct_test_bool<starts_with<
		range<bool, char, short, int, float, double>,
		range<char, short, int>
	>,false>();

	mire_ct_test_bool<starts_with<
		range<char, wchar_t, short, int, long, long long, double>,
		range<unsigned, float>
	>,false>();

	mire_ct_test_bool<starts_with<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double>
	>, true>();

	mire_ct_test_bool<starts_with<
		range<bool, char, short, int, float, double>,
		range<bool, char, short, int, float, double, long double>
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_starts_with_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<starts_with<
		string<>,
		string<>
	>, true>();

	mire_ct_test_bool<starts_with<
		string<'c'>,
		string<>
	>, true>();

	mire_ct_test_bool<starts_with<
		string<>,
		string<'c'>
	>,false>();

	mire_ct_test_bool<starts_with<
		string<'s','t','r'>,
		string<'s'>
	>, true>();

	mire_ct_test_bool<starts_with<
		string<'s','t','r'>,
		string<'s','t','r'>
	>, true>();

	mire_ct_test_bool<starts_with<
		string<'s','t','r'>,
		string<'s','t','r','i','n','g'>
	>,false>();
}

BOOST_AUTO_TEST_SUITE_END()

