/**
 *  .file test/mire/ct/tail.cpp
 *  .brief Test case for compile-time tail meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_tail
#include <boost/test/unit_test.hpp>

#include <mire/ct/tail.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_tail)

BOOST_AUTO_TEST_CASE(mire_ct_tail_range)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	BOOST_CHECK((equal<
		tail<range<>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		tail<range<long>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		tail<range<long>, one>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		tail<range<long>, three>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		tail<range<long>, five>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		tail<range<short, int, long>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		tail<range<short, int, long>, one>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		tail<range<short, int, long>, two>,
		range<int, long>
	>::value));

	BOOST_CHECK((equal<
		tail<range<short, int, long>, three>,
		range<short, int, long>
	>::value));

	BOOST_CHECK((equal<
		tail<range<short, int, long>, four>,
		range<short, int, long>
	>::value));

	BOOST_CHECK((equal<
		tail<range<bool, char, short, int, long, float>, zero>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		tail<range<bool, char, short, int, long, float>, one>,
		range<float>
	>::value));

	BOOST_CHECK((equal<
		tail<range<bool, char, short, int, long, float>, three>,
		range<int, long, float>
	>::value));

	BOOST_CHECK((equal<
		tail<range<bool, char, short, int, long, float>, five>,
		range<char, short, int, long, float>
	>::value));

	BOOST_CHECK((equal<
		tail<tail<range<bool, char, short, int, long, float>, four>, two>,
		range<long, float>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_tail_string)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	BOOST_CHECK((equal<
		tail<string<>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a'>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a'>, one>,
		string<'a'>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a','b','c'>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a','b','c'>, one>,
		string<'c'>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a','b','c'>, two>,
		string<'b','c'>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a','b','c'>, three>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a','b','c'>, four>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'a','b','c'>, five>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'s','t','r','i','n','g'>, zero>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'s','t','r','i','n','g'>, one>,
		string<'g'>
	>::value));

	BOOST_CHECK((equal<
		tail<string<'s','t','r','i','n','g'>, three>,
		string<'i','n','g'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

