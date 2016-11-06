/**
 *  .file test/puddle/concat_r.cpp
 *  .brief Test case for compile-time concat operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_concat
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_concat)

BOOST_AUTO_TEST_CASE(puddle_concat_range)
{
	using namespace puddle;

	auto er = empty_range;
	auto r1 = range<int, long, char>;
	auto r2 = range<bool, float, void>;
	auto r3 = range<char, bool, float>;
	auto r4 = range<int, long>;
	auto r5 = range<void>;

	BOOST_CHECK(( value(concat(er) == er)));
	BOOST_CHECK(( value(concat(r1) == r1)));
	BOOST_CHECK(( value(concat(er, er) == er)));
	BOOST_CHECK(( value(concat(r1, er) == r1)));
	BOOST_CHECK(( value(concat(er, r1) == r1)));
	BOOST_CHECK((!value(concat(r1, r2) == r3)));
	BOOST_CHECK(( value(concat(r1, r2) == concat(r4, r3, r5))));
	BOOST_CHECK((!value(concat(r1, r2) == concat(r3, r4, r5))));
	BOOST_CHECK((!value(concat(r1, r2) == r4)));
}

BOOST_AUTO_TEST_CASE(puddle_concat_string)
{
	using namespace puddle;

	auto e = empty_string;
	auto a = string<'a'>;
	auto b = string<'b'>;
	auto ab = string<'a','b'>;
	auto cd = string<'c','d'>;
	auto abcd = string<'a','b','c','d'>;

	BOOST_CHECK(( value(concat(e) == e)));
	BOOST_CHECK(( value(concat(a) == a)));
	BOOST_CHECK(( value(concat(e, e) == e)));
	BOOST_CHECK(( value(concat(a, e) == a)));
	BOOST_CHECK(( value(concat(e, b) == b)));
	BOOST_CHECK(( value(concat(a, b) == ab)));
	BOOST_CHECK((!value(concat(a, a) == ab)));
	BOOST_CHECK((!value(concat(b, a) == ab)));
	BOOST_CHECK(( value(concat(ab, cd) == abcd)));
	BOOST_CHECK((!value(concat(cd, ab) == abcd)));
	BOOST_CHECK(( value(concat(a, b, cd) == concat(ab, cd))));
	BOOST_CHECK(( value(concat(concat(a, b), cd) == abcd)));
}

BOOST_AUTO_TEST_SUITE_END()

