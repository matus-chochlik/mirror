/**
 *  .file test/mire/ct/head.cpp
 *  .brief Test case for compile-time head meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_head
#include <boost/test/unit_test.hpp>

#include <mire/ct/head.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_head)

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_head_range)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	mire_ct_test_bool<equal<
		head<range<>, zero>,
		range<>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<long>, zero>,
		range<>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<long>, one>,
		range<long>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<long>, three>,
		range<long>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<long>, five>,
		range<long>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<short, int, long>, zero>,
		range<>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<short, int, long>, one>,
		range<short>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<short, int, long>, two>,
		range<short, int>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<short, int, long>, three>,
		range<short, int, long>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<short, int, long>, four>,
		range<short, int, long>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<bool, char, short, int, long, float>, zero>,
		range<>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<bool, char, short, int, long, float>, one>,
		range<bool>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<bool, char, short, int, long, float>, three>,
		range<bool, char, short>
	>, true>();

	mire_ct_test_bool<equal<
		head<range<bool, char, short, int, long, float>, five>,
		range<bool, char, short, int, long>
	>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_head_string)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	mire_ct_test_bool<equal<
		head<string<>, zero>,
		string<>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a'>, zero>,
		string<>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a'>, one>,
		string<'a'>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a','b','c'>, zero>,
		string<>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a','b','c'>, one>,
		string<'a'>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a','b','c'>, two>,
		string<'a','b'>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a','b','c'>, three>,
		string<'a','b','c'>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a','b','c'>, four>,
		string<'a','b','c'>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'a','b','c'>, five>,
		string<'a','b','c'>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'s','t','r','i','n','g'>, zero>,
		string<>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'s','t','r','i','n','g'>, one>,
		string<'s'>
	>, true>();

	mire_ct_test_bool<equal<
		head<string<'s','t','r','i','n','g'>, three>,
		string<'s','t','r'>
	>, true>();
}

BOOST_AUTO_TEST_SUITE_END()

