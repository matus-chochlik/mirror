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

BOOST_AUTO_TEST_CASE(mire_ct_head_range)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	BOOST_CHECK((equal<
		head<range<>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		head<range<long>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		head<range<long>, one>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		head<range<long>, three>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		head<range<long>, five>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		head<range<short, int, long>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		head<range<short, int, long>, one>,
		range<short>
	>::value));

	BOOST_CHECK((equal<
		head<range<short, int, long>, two>,
		range<short, int>
	>::value));

	BOOST_CHECK((equal<
		head<range<short, int, long>, three>,
		range<short, int, long>
	>::value));

	BOOST_CHECK((equal<
		head<range<short, int, long>, four>,
		range<short, int, long>
	>::value));

	BOOST_CHECK((equal<
		head<range<bool, char, short, int, long, float>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		head<range<bool, char, short, int, long, float>, one>,
		range<bool>
	>::value));

	BOOST_CHECK((equal<
		head<range<bool, char, short, int, long, float>, three>,
		range<bool, char, short>
	>::value));

	BOOST_CHECK((equal<
		head<range<bool, char, short, int, long, float>, five>,
		range<bool, char, short, int, long>
	>::value));

	BOOST_CHECK((equal<
		head<head<range<bool, char, short, int, long, float>, four>, two>,
		range<bool, char>
	>::value));
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

	BOOST_CHECK((equal<
		head<string<>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a'>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a'>, one>,
		string<'a'>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a','b','c'>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a','b','c'>, one>,
		string<'a'>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a','b','c'>, two>,
		string<'a','b'>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a','b','c'>, three>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a','b','c'>, four>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		head<string<'a','b','c'>, five>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		head<string<'s','t','r','i','n','g'>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		head<string<'s','t','r','i','n','g'>, one>,
		string<'s'>
	>::value));

	BOOST_CHECK((equal<
		head<string<'s','t','r','i','n','g'>, three>,
		string<'s','t','r'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

