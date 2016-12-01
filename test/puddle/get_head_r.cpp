/**
 *  .file test/puddle/get_head_r.cpp
 *  .brief Test case for compile-time get_head operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_get_head
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_get_head)

BOOST_AUTO_TEST_CASE(puddle_get_head_range)
{
	using namespace puddle;

	BOOST_CHECK( value(
		get_head(empty_range, size_t_<0>) ==
		empty_range
	));

	BOOST_CHECK( value(
		get_head(empty_range, size_t_<10>) ==
		empty_range
	));

	BOOST_CHECK( value(
		get_head(range<long, int, char, bool>, size_t_<0>) ==
		empty_range
	));

	BOOST_CHECK( value(
		get_head(range<long, int, char, bool>, size_t_<1>) ==
		range<long>
	));

	BOOST_CHECK( value(
		get_head(range<long, int, char, bool>, size_t_<2>) ==
		range<long, int>
	));

	BOOST_CHECK( value(
		get_head(range<long, int, char, bool>, size_t_<3>) ==
		range<long, int, char>
	));

	BOOST_CHECK( value(
		get_head(range<long, int, char, bool>, size_t_<4>) ==
		range<long, int, char, bool>
	));

	BOOST_CHECK( value(
		get_head(range<long, int, char, bool>, size_t_<5>) ==
		range<long, int, char, bool>
	));

	BOOST_CHECK( value(
		get_head(range<long, int, char, bool>, size_t_<100>) ==
		range<long, int, char, bool>
	));
}

BOOST_AUTO_TEST_CASE(puddle_get_head_string)
{
	using namespace puddle;

	BOOST_CHECK( value(
		get_head(empty_string, size_t_<0>) ==
		empty_string
	));

	BOOST_CHECK( value(
		get_head(empty_string, size_t_<12>) ==
		empty_string
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<0>) ==
		empty_string
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<1>) ==
		string<'a'>
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<2>) ==
		string<'a','b'>
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<3>) ==
		string<'a','b','c'>
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<4>) ==
		string<'a','b','c','d'>
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<5>) ==
		string<'a','b','c','d','e'>
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<6>) ==
		string<'a','b','c','d','e'>
	));

	BOOST_CHECK( value(
		get_head(string<'a','b','c','d','e'>, size_t_<100>) ==
		string<'a','b','c','d','e'>
	));

}

BOOST_AUTO_TEST_SUITE_END()

