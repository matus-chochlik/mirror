/**
 *  .file test/puddle/join_r.cpp
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
#define BOOST_TEST_MODULE PUDDLE_join
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_join)

BOOST_AUTO_TEST_CASE(puddle_join_range)
{
	using namespace puddle;

	auto s1 = range<short>;
	auto s2 = range<double, double>;
	auto er = empty_range;
	auto r1 = range<int>;
	auto r2 = range<int, long>;
	auto r3 = range<int, long, char>;

	BOOST_CHECK(( value(join(s1) == er)));
	BOOST_CHECK(( value(join(s2) == er)));
	BOOST_CHECK(( value(join(s1, er) == er)));
	BOOST_CHECK(( value(join(s1, r1) == r1)));
	BOOST_CHECK(( value(join(s2, r1) == r1)));

	BOOST_CHECK(( value(
		join(s1, r1, r1) ==
		range<int, short, int>
	)));

	BOOST_CHECK(( value(
		join(s1, r1, r2) ==
		range<int, short, int, long>
	)));

	BOOST_CHECK(( value(
		join(s2, r1, r1) ==
		range<int, double, double, int>
	)));

	BOOST_CHECK(( value(
		join(s1, r1, r2, r3) ==
		range<int, short, int, long, short, int, long, char>
	)));

	BOOST_CHECK(( value(
		join(s1, r1, r1, r1, r1, r1) ==
		range<int, short, int, short, int, short, int, short, int>
	)));
}

BOOST_AUTO_TEST_CASE(puddle_join_string)
{
	using namespace puddle;

	auto s1 = string<','>;
	auto s2 = string<':',':'>;
	auto e = empty_string;
	auto a = string<'a'>;
	auto b = string<'b'>;
	auto ab = string<'a','b'>;
	auto abcd = string<'a','b','c','d'>;

	BOOST_CHECK(( value(join(s1) == e)));
	BOOST_CHECK(( value(join(s2) == e)));
	BOOST_CHECK(( value(join(s1, e) == e)));
	BOOST_CHECK(( value(join(s1, a) == a)));
	BOOST_CHECK(( value(join(s2, a) == a)));

	BOOST_CHECK(( value(
		join(s1, a, a) ==
		string<'a',',','a'>
	)));

	BOOST_CHECK(( value(
		join(s2, a, b) ==
		string<'a',':',':','b'>
	)));

	BOOST_CHECK(( value(
		join(s1, b, ab) ==
		string<'b',',','a','b'>
	)));

	BOOST_CHECK(( value(
		join(s2, abcd, ab) ==
		string<'a','b','c','d',':',':','a','b'>
	)));

	BOOST_CHECK(( value(
		join(s1, a, b, a, b, a) ==
		string<'a',',','b',',','a',',','b',',','a'>
	)));
}

BOOST_AUTO_TEST_SUITE_END()

