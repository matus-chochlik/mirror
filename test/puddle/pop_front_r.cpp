/**
 *  .file test/puddle/pop_front_r.cpp
 *  .brief Test case for compile-time pop_front operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_pop_front
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/type.hpp>

BOOST_AUTO_TEST_SUITE(puddle_pop_front)

BOOST_AUTO_TEST_CASE(puddle_pop_front_range)
{
	using namespace puddle;

	BOOST_CHECK((value(
		pop_front(empty_range) ==
		empty_range
	)));
	BOOST_CHECK((value(
		pop_front(range<double>) ==
		empty_range
	)));
	BOOST_CHECK((value(
		pop_front(range<int, char>) ==
		range<char>
	)));
	BOOST_CHECK((value(
		pop_front(range<long, char, bool>) ==
		range<char, bool>
	)));
	BOOST_CHECK((value(
		pop_front(pop_front(range<long, char, bool>)) ==
		range<bool>
	)));
}

BOOST_AUTO_TEST_CASE(puddle_pop_front_string)
{
	using namespace puddle;

	BOOST_CHECK((value(
		pop_front(empty_string) ==
		empty_string
	)));
	BOOST_CHECK((value(
		pop_front(string<'x'>) ==
		empty_string
	)));
	BOOST_CHECK((value(
		pop_front(string<'x','y'>) ==
		string<'y'>
	)));
	BOOST_CHECK((value(
		pop_front(string<'x','y','z'>) ==
		string<'y','z'>
	)));
	BOOST_CHECK((value(
		pop_front(pop_front(string<'x','y','z'>)) ==
		string<'z'>
	)));
}

BOOST_AUTO_TEST_SUITE_END()

