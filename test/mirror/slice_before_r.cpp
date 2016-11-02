/**
 *  .file test/mirror/slice_before_r.cpp
 *  .brief Test case for compile-time slice_before operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_slice_before
#include <boost/test/unit_test.hpp>

#include <mirror/slice_before.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_slice_before)

BOOST_AUTO_TEST_CASE(mirror_slice_before_range)
{
	using namespace mirror;

	using r1 = range<double, float, long, int, short, char, bool>;

	BOOST_CHECK(( value<equal<
		slice_before<r1, empty_range>,
		empty_range
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, identity<void>>,
		r1
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<void>>,
		r1
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<double>>,
		empty_range
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<double, float>>,
		empty_range
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<double, float, unsigned>>,
		r1
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, identity<long>>,
		range<double, float>
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<int, short, char>>,
		range<double, float, long>
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<int, short, bool>>,
		r1
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, identity<char>>,
		range<double, float, long, int, short>
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<char>>,
		range<double, float, long, int, short>
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<r1, range<bool>>,
		range<double, float, long, int, short, char>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_slice_before_string)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h','i'>;

	BOOST_CHECK(( value<equal<
		slice_before<s1, empty_string>,
		empty_string
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'j'>>,
		s1
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'a'>>,
		empty_string
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'a','b','c'>>,
		empty_string
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'a','b','x'>>,
		s1
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'e'>>,
		string<'a','b','c','d'>
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'d','e','f','g'>>,
		string<'a','b','c'>
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'g','h','i'>>,
		string<'a','b','c','d','e','f'>
	>>));

	BOOST_CHECK(( value<equal<
		slice_before<s1, string<'i'>>,
		string<'a','b','c','d','e','f','g','h'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

