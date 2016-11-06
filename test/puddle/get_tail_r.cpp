/**
 *  .file test/puddle/get_tail_r.cpp
 *  .brief Test case for compile-time get_tail operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_get_tail
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_get_tail)

BOOST_AUTO_TEST_CASE(puddle_get_tail_range)
{
	using namespace puddle;

	BOOST_CHECK( value(
		get_tail(empty_range, size_c<0>) ==
		empty_range
	));

	BOOST_CHECK( value(
		get_tail(empty_range, size_c<10>) ==
		empty_range
	));

	BOOST_CHECK( value(
		get_tail(range<long, int, char, bool>, size_c<0>) ==
		empty_range
	));

	BOOST_CHECK( value(
		get_tail(range<long, int, char, bool>, size_c<1>) ==
		range<bool>
	));

	BOOST_CHECK( value(
		get_tail(range<long, int, char, bool>, size_c<2>) ==
		range<char, bool>
	));

	BOOST_CHECK( value(
		get_tail(range<long, int, char, bool>, size_c<3>) ==
		range<int, char, bool>
	));

	BOOST_CHECK( value(
		get_tail(range<long, int, char, bool>, size_c<4>) ==
		range<long, int, char, bool>
	));

	BOOST_CHECK( value(
		get_tail(range<long, int, char, bool>, size_c<5>) ==
		range<long, int, char, bool>
	));

	BOOST_CHECK( value(
		get_tail(range<long, int, char, bool>, size_c<100>) ==
		range<long, int, char, bool>
	));
}

BOOST_AUTO_TEST_CASE(puddle_get_tail_string)
{
	using namespace puddle;

	BOOST_CHECK( value(
		get_tail(empty_string, size_c<0>) ==
		empty_string
	));

	BOOST_CHECK( value(
		get_tail(empty_string, size_c<12>) ==
		empty_string
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<0>) ==
		empty_string
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<1>) ==
		string<'e'>
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<2>) ==
		string<'d','e'>
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<3>) ==
		string<'c','d','e'>
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<4>) ==
		string<'b','c','d','e'>
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<5>) ==
		string<'a','b','c','d','e'>
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<6>) ==
		string<'a','b','c','d','e'>
	));

	BOOST_CHECK( value(
		get_tail(string<'a','b','c','d','e'>, size_c<100>) ==
		string<'a','b','c','d','e'>
	));

}

BOOST_AUTO_TEST_SUITE_END()

