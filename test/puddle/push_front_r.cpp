/**
 *  .file test/puddle/push_front_r.cpp
 *  .brief Test case for compile-time push_front operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_push_front
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/type.hpp>


BOOST_AUTO_TEST_SUITE(puddle_push_front)

BOOST_AUTO_TEST_CASE(puddle_push_front_range)
{
	using namespace puddle;

	BOOST_CHECK((value(
		push_front(empty_range, type<char>) ==
		range<char>
	)));
	BOOST_CHECK((value(
		push_front(range<char>, type<int>) ==
		range<int, char>
	)));
	BOOST_CHECK((value(
		push_front(range<char, int>, type<bool>) ==
		range<bool, char, int>
	)));
	BOOST_CHECK((value(
		push_front(push_front(range<char>, type<int>), type<bool>) ==
		range<bool, int, char>
	)));
}

BOOST_AUTO_TEST_CASE(puddle_push_front_string)
{
	using namespace puddle;

	BOOST_CHECK((value(
		push_front(empty_string, char_<'x'>) ==
		string<'x'>
	)));

	BOOST_CHECK((value(
		push_front(string<'y'>, char_<'x'>) ==
		string<'x','y'>
	)));

	BOOST_CHECK((value(
		push_front(string<'y','z'>, char_<'x'>) ==
		string<'x','y','z'>
	)));

	BOOST_CHECK((value(
		push_front(push_front(string<'z'>, char_<'y'>), char_<'x'>) ==
		string<'x','y','z'>
	)));
}

BOOST_AUTO_TEST_SUITE_END()

