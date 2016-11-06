/**
 *  .file test/puddle/push_back_r.cpp
 *  .brief Test case for compile-time push_back operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_push_back
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/type.hpp>

BOOST_AUTO_TEST_SUITE(puddle_push_back)

BOOST_AUTO_TEST_CASE(puddle_push_back_range)
{
	using namespace puddle;

	BOOST_CHECK((value(
		push_back(empty_range, type<char>) ==
		range<char>
	)));
	BOOST_CHECK((value(
		push_back(range<char>, type<int>) ==
		range<char, int>
	)));
	BOOST_CHECK((value(
		push_back(range<char, int>, type<bool>) ==
		range<char, int, bool>
	)));
	BOOST_CHECK((value(
		push_back(push_back(range<char>, type<int>), type<bool>) ==
		range<char, int, bool>
	)));
}

BOOST_AUTO_TEST_CASE(puddle_push_back_string)
{
	using namespace puddle;

	BOOST_CHECK((value(
		push_back(empty_string, char_<'x'>) ==
		string<'x'>
	)));

	BOOST_CHECK((value(
		push_back(string<'y'>, char_<'x'>) ==
		string<'y','x'>
	)));

	BOOST_CHECK((value(
		push_back(string<'z','y'>, char_<'x'>) ==
		string<'z','y','x'>
	)));

	BOOST_CHECK((value(
		push_back(push_back(string<'z'>, char_<'y'>), char_<'x'>) ==
		string<'z','y','x'>
	)));
}

BOOST_AUTO_TEST_SUITE_END()

