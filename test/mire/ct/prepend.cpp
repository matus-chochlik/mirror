/**
 *  .file test/mire/ct/prepend.cpp
 *  .brief Test case for compile-time prepend meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_empty
#include <boost/test/unit_test.hpp>

#include <mire/ct/prepend.hpp>
#include <mire/ct/compare.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_prepend)

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_prepend_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		prepend_c<string<'a','b','c'>, char>,
		string<'a','b','c'>
	>, true>();

	mire_ct_test_bool<equal<
		prepend_c<string<'b','c','d'>, char,'a'>,
		string<'a','b','c','d'>
	>, true>();

	mire_ct_test_bool<equal<
		prepend_c<string<'d','e','f'>, char, 'a','b','c'>,
		string<'a','b','c','d','e','f'>
	>, true>();

	mire_ct_test_bool<equal<
		prepend_c<string<'e','f','g','h','i'>, char,'a','b','c','d'>,
		string<'a','b','c','d','e','f','g','h','i'>
	>, true>();

	mire_ct_test_bool<equal<
		prepend_c<string<'g','h','i','j','k','l'>, char,'a','b','c','d','e','f'>,
		string<'a','b','c','d','e','f','g','h','i','j','k','l'>
	>, true>();

	mire_ct_test_bool<equal<
		prepend_c<prepend_c<string<'g','h','i'>, char,'d','e','f'>, char,'a','b','c'>,
		string<'a','b','c','d','e','f','g','h','i'>
	>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_prepend_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		prepend<range<short, int, long>>,
		range<short, int, long>
	>, true>();

	mire_ct_test_bool<equal<
		prepend<range<int, long, float>, short>,
		range<short, int, long, float>
	>, true>();

	mire_ct_test_bool<equal<
		prepend<range<short, int, long double>, bool, char, wchar_t>,
		range<bool, char, wchar_t, short, int, long double>
	>, true>();

	mire_ct_test_bool<equal<
		prepend<range<long, unsigned, float, double>, bool, char, wchar_t, short, int>,
		range<bool, char, wchar_t, short, int, long, unsigned, float, double>
	>, true>();

	mire_ct_test_bool<equal<
		prepend<prepend<range<int, long double>, wchar_t, short>, bool, char>,
		range<bool, char, wchar_t, short, int, long double>
	>, true>();
}

BOOST_AUTO_TEST_SUITE_END()

