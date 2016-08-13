/**
 *  .file test/mirror/join_r.cpp
 *  .brief Test case for compile-time join operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_join
#include <boost/test/unit_test.hpp>

#include <mirror/join.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_join)

BOOST_AUTO_TEST_CASE(mirror_join_range)
{
	using namespace mirror;

	using s1 = range<short>;
	using s2 = range<double, double>;
	using er = empty_range;
	using r1 = range<int>;
	using r2 = range<int, long>;
	using r3 = range<int, long, char>;

	BOOST_CHECK(( value<equal<join<s1>, er>>));
	BOOST_CHECK(( value<equal<join<s2>, er>>));
	BOOST_CHECK(( value<equal<join<s1, er>, er>>));
	BOOST_CHECK(( value<equal<join<s1, r1>, r1>>));
	BOOST_CHECK(( value<equal<join<s2, r1>, r1>>));

	BOOST_CHECK(( value<equal<
		join<s1, r1, r1>,
		range<int, short, int>
	>>));

	BOOST_CHECK(( value<equal<
		join<s1, r1, r2>,
		range<int, short, int, long>
	>>));

	BOOST_CHECK(( value<equal<
		join<s2, r1, r1>,
		range<int, double, double, int>
	>>));

	BOOST_CHECK(( value<equal<
		join<s1, r1, r2, r3>,
		range<int, short, int, long, short, int, long, char>
	>>));

	BOOST_CHECK(( value<equal<
		join<s1, r1, r1, r1, r1, r1>,
		range<int, short, int, short, int, short, int, short, int>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_join_string)
{
	using namespace mirror;

	using s1 = string<','>;
	using s2 = string<':',':'>;
	using e = empty_string;
	using a = string<'a'>;
	using b = string<'b'>;
	using ab = string<'a','b'>;
	using abcd = string<'a','b','c','d'>;

	BOOST_CHECK(( value<equal<join<s1>, e>>));
	BOOST_CHECK(( value<equal<join<s2>, e>>));
	BOOST_CHECK(( value<equal<join<s1, e>, e>>));
	BOOST_CHECK(( value<equal<join<s1, a>, a>>));
	BOOST_CHECK(( value<equal<join<s2, a>, a>>));

	BOOST_CHECK(( value<equal<
		join<s1, a, a>,
		string<'a',',','a'>
	>>));

	BOOST_CHECK(( value<equal<
		join<s2, a, b>,
		string<'a',':',':','b'>
	>>));

	BOOST_CHECK(( value<equal<
		join<s1, b, ab>,
		string<'b',',','a','b'>
	>>));

	BOOST_CHECK(( value<equal<
		join<s2, abcd, ab>,
		string<'a','b','c','d',':',':','a','b'>
	>>));

	BOOST_CHECK(( value<equal<
		join<s1, a, b, a, b, a>,
		string<'a',',','b',',','a',',','b',',','a'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

