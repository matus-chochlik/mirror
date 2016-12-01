/**
 *  .file test/dazzle/join_r.cpp
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
#define BOOST_TEST_MODULE DAZZLE_join
#include <boost/test/unit_test.hpp>

#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_join)

BOOST_AUTO_TEST_CASE(dazzle_join_range)
{
	using namespace dazzle;

	auto s1 = range<short>;
	auto s2 = range<double, double>;
	auto er = empty_range;
	auto r1 = range<int>;
	auto r2 = range<int, long>;
	auto r3 = range<int, long, char>;

	BOOST_CHECK(( (s1.join() == er)));
	BOOST_CHECK(( (s2.join() == er)));
	BOOST_CHECK(( (s1.join(er) == er)));
	BOOST_CHECK(( (s1.join(r1) == r1)));
	BOOST_CHECK(( (s2.join(r1) == r1)));

	BOOST_CHECK(( (
		s1.join(r1, r1) ==
		range<int, short, int>
	)));

	BOOST_CHECK(( (
		s1.join(r1, r2) ==
		range<int, short, int, long>
	)));

	BOOST_CHECK(( (
		s2.join(r1, r1) ==
		range<int, double, double, int>
	)));

	BOOST_CHECK(( (
		s1.join(r1, r2, r3) ==
		range<int, short, int, long, short, int, long, char>
	)));

	BOOST_CHECK(( (
		s1.join(r1, r1, r1, r1, r1) ==
		range<int, short, int, short, int, short, int, short, int>
	)));
}

BOOST_AUTO_TEST_CASE(dazzle_join_string)
{
	using namespace dazzle;

	auto s1 = string<','>;
	auto s2 = string<':',':'>;
	auto e = empty_string;
	auto a = string<'a'>;
	auto b = string<'b'>;
	auto ab = string<'a','b'>;
	auto abcd = string<'a','b','c','d'>;

	BOOST_CHECK(( (s1.join() == e)));
	BOOST_CHECK(( (s2.join() == e)));
	BOOST_CHECK(( (s1.join(e) == e)));
	BOOST_CHECK(( (s1.join(a) == a)));
	BOOST_CHECK(( (s2.join(a) == a)));

	BOOST_CHECK(( (
		s1.join(a, a) ==
		string<'a',',','a'>
	)));

	BOOST_CHECK(( (
		s2.join(a, b) ==
		string<'a',':',':','b'>
	)));

	BOOST_CHECK(( (
		s1.join(b, ab) ==
		string<'b',',','a','b'>
	)));

	BOOST_CHECK(( (
		s2.join(abcd, ab) ==
		string<'a','b','c','d',':',':','a','b'>
	)));

	BOOST_CHECK(( (
		s1.join(a, b, a, b, a) ==
		string<'a',',','b',',','a',',','b',',','a'>
	)));
}

BOOST_AUTO_TEST_SUITE_END()

