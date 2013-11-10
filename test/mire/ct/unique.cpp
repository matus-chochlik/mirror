/**
 *  .file test/mire/ct/unique.cpp
 *  .brief Test case for compile-time unique meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_unique
#include <boost/test/unit_test.hpp>

#include <mire/ct/unique.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_unique)

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_unique_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		unique<range<>>,
		range<>
	>, true>();

	mire_ct_test_bool<equal<
		unique<range<bool, char, int, float, double>>,
		range<bool, char, int, float, double>
	>, true>();

	mire_ct_test_bool<equal<
		unique<range<bool, char, bool, int, int, int, float, double, float>>,
		range<bool, char, int, float, double>
	>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_unique_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		unique<string<>>,
		string<>
	>, true>();

	mire_ct_test_bool<equal<
		unique<string<'s','t','r','i','n','g'>>,
		string<'s','t','r','i','n','g'>
	>, true>();

	mire_ct_test_bool<equal<
		unique<string<'s','t','s','r','i','i','i','n','i','g','n'>>,
		string<'s','t','r','i','n','g'>
	>, true>();
}

BOOST_AUTO_TEST_SUITE_END()

