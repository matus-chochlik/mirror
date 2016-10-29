/**
 *  .file test/puddle/slice_r.cpp
 *  .brief Test case for compile-time slice operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_slice
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_slice)

BOOST_AUTO_TEST_CASE(puddle_slice_range)
{
	using namespace puddle;

	auto er = empty_range;
	auto rb = range<int, long>;
	auto re = range<short, char>;
	auto rc = range<long, float, short>;
	auto rl = range<int, long, float, short, char>;

	auto s0 = size_c<0>;
	auto s1 = size_c<1>;
	auto s2 = size_c<2>;
	auto s3 = size_c<3>;
	auto s4 = size_c<4>;
	auto s5 = size_c<5>;

	BOOST_CHECK(( value(slice(er, s0, s0) == er)));
	BOOST_CHECK(( value(slice(er, s1, s0) == er)));
	BOOST_CHECK(( value(slice(er, s5, s0) == er)));
	BOOST_CHECK(( value(slice(er, s0, s2) == er)));
	BOOST_CHECK(( value(slice(er, s0, s5) == er)));
	BOOST_CHECK(( value(slice(er, s3, s4) == er)));

	BOOST_CHECK(( value(slice(rl, s0, s0) == er)));
	BOOST_CHECK(( value(slice(rl, s3, s0) == er)));
	BOOST_CHECK(( value(slice(rl, s5, s4) == er)));

	BOOST_CHECK(( value(slice(rl, s0, s2) == rb)));
	BOOST_CHECK(( value(slice(rl, s1, s3) == rc)));
	BOOST_CHECK(( value(slice(rl, s3, s2) == re)));
	BOOST_CHECK(( value(slice(rl, s3, s4) == re)));

	BOOST_CHECK(( value(slice(rl, s2, s2) == slice(rc,s1, s2))));
}

BOOST_AUTO_TEST_CASE(puddle_slice_string)
{
	using namespace puddle;

	auto e = empty_string;
	auto abcde = string<'a','b','c','d','e'>;
	auto abc = string<'a','b','c'>;
	auto cde = string<'c','d','e'>;
	auto bcd = string<'b','c','d'>;

	auto s0 = size_c<0>;
	auto s1 = size_c<1>;
	auto s2 = size_c<2>;
	auto s3 = size_c<3>;
	auto s4 = size_c<4>;
	auto s5 = size_c<5>;

	BOOST_CHECK(( value(slice(e, s0, s0) == e)));
	BOOST_CHECK(( value(slice(e, s2, s1) == e)));
	BOOST_CHECK(( value(slice(e, s5, s0) == e)));
	BOOST_CHECK(( value(slice(e, s3, s4) == e)));

	BOOST_CHECK(( value(slice(abcde, s0, s0) == e)));
	BOOST_CHECK(( value(slice(abcde, s0, s3) == abc)));
	BOOST_CHECK(( value(slice(abcde, s1, s3) == bcd)));
	BOOST_CHECK(( value(slice(abcde, s2, s3) == cde)));
	BOOST_CHECK(( value(slice(abcde, s5, s4) == e)));

	BOOST_CHECK(( value(slice(abcde, s4, s3) == slice(cde, s2, s1))));
	BOOST_CHECK(( value(slice(abcde, s1, s2) == slice(abc, s1, s2))));
	BOOST_CHECK(( value(slice(abcde, s2, s1) == slice(abc, s2, s2))));
	BOOST_CHECK(( value(slice(abcde, s2, s1) == slice(bcd, s1, s1))));
	BOOST_CHECK(( value(slice(abcde, s2, s1) == slice(cde, s0, s1))));
}

BOOST_AUTO_TEST_SUITE_END()

