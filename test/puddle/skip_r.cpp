/**
 *  .file test/puddle/skip_r.cpp
 *  .brief Test case for compile-time skip operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_skip
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_skip)

BOOST_AUTO_TEST_CASE(puddle_skip_range)
{
	using namespace puddle;

	auto er = empty_range;
	auto r1 = range<char>;
	auto r2 = range<long, char>;
	auto r3 = range<int, long, char>;

	auto s0 = size_c<0>;
	auto s1 = size_c<1>;
	auto s2 = size_c<2>;
	auto s3 = size_c<3>;
	auto s4 = size_c<4>;

	BOOST_CHECK(( value(skip(er, s0) == er)));
	BOOST_CHECK(( value(skip(er, s1) == er)));
	BOOST_CHECK(( value(skip(er, s2) == er)));
	BOOST_CHECK(( value(skip(er, s3) == er)));
	BOOST_CHECK(( value(skip(r1, s0) == r1)));
	BOOST_CHECK(( value(skip(r1, s1) == er)));
	BOOST_CHECK(( value(skip(r1, s2) == er)));
	BOOST_CHECK(( value(skip(r2, s0) == r2)));
	BOOST_CHECK(( value(skip(r2, s1) == r1)));
	BOOST_CHECK(( value(skip(r2, s2) == er)));
	BOOST_CHECK(( value(skip(r2, s3) == er)));
	BOOST_CHECK(( value(skip(r3, s0) == r3)));
	BOOST_CHECK(( value(skip(r3, s1) == r2)));
	BOOST_CHECK(( value(skip(r3, s2) == r1)));
	BOOST_CHECK(( value(skip(r3, s3) == er)));
	BOOST_CHECK(( value(skip(r3, s4) == er)));
}

BOOST_AUTO_TEST_CASE(puddle_skip_string)
{
	using namespace puddle;

	auto e = empty_string;
	auto c = string<'c'>;
	auto bc = string<'b','c'>;
	auto abc = string<'a','b','c'>;

	auto s0 = size_c<0>;
	auto s1 = size_c<1>;
	auto s2 = size_c<2>;
	auto s3 = size_c<3>;
	auto s4 = size_c<4>;

	BOOST_CHECK(( value(skip(e, s0) == e)));
	BOOST_CHECK(( value(skip(e, s1) == e)));
	BOOST_CHECK(( value(skip(c, s0) == c)));
	BOOST_CHECK(( value(skip(c, s1) == e)));
	BOOST_CHECK(( value(skip(c, s2) == e)));
	BOOST_CHECK(( value(skip(bc, s0) == bc)));
	BOOST_CHECK(( value(skip(bc, s1) == c)));
	BOOST_CHECK(( value(skip(bc, s2) == e)));
	BOOST_CHECK(( value(skip(bc, s3) == e)));
	BOOST_CHECK(( value(skip(abc, s0) == abc)));
	BOOST_CHECK(( value(skip(abc, s1) == bc)));
	BOOST_CHECK(( value(skip(abc, s2) == c)));
	BOOST_CHECK(( value(skip(abc, s3) == e)));
	BOOST_CHECK(( value(skip(abc, s4) == e)));
}

BOOST_AUTO_TEST_SUITE_END()

