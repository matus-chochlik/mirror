/**
 *  .file test/puddle/contains_r.cpp
 *  .brief Test case for compile-time contains operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_contains
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_contains)

BOOST_AUTO_TEST_CASE(puddle_range_contains_1)
{
	using namespace puddle;

	auto r1 = range<double, float, long, int, short, char, bool, void>;

	BOOST_CHECK(( value(contains(r1, empty_range))));
	BOOST_CHECK(( value(contains(r1, range<double>))));
	BOOST_CHECK(( value(contains(r1, range<float>))));
	BOOST_CHECK(( value(contains(r1, range<long>))));
	BOOST_CHECK(( value(contains(r1, range<int>))));
	BOOST_CHECK(( value(contains(r1, range<short>))));
	BOOST_CHECK(( value(contains(r1, range<char>))));
	BOOST_CHECK(( value(contains(r1, range<bool>))));
	BOOST_CHECK(( value(contains(r1, range<void>))));
	BOOST_CHECK((!value(contains(r1, range<wchar_t>))));

	BOOST_CHECK(( value(contains(empty_range, empty_range))));
	BOOST_CHECK((!value(contains(empty_range, range<double>))));
	BOOST_CHECK((!value(contains(empty_range, range<wchar_t>))));
}

BOOST_AUTO_TEST_CASE(puddle_range_contains_2)
{
	using namespace puddle;

	auto r1 = range<double, float, long, int, short, char, bool, void>;

	BOOST_CHECK(( value(contains(r1, r1))));
	BOOST_CHECK(( value(contains(r1, range<double, float, long>))));
	BOOST_CHECK(( value(contains(r1, range<float, long>))));
	BOOST_CHECK(( value(contains(r1, range<long, int, short, char>))));
	BOOST_CHECK(( value(contains(r1, range<int, short>))));
	BOOST_CHECK(( value(contains(r1, range<char, bool, void>))));
	BOOST_CHECK(( value(contains(r1, range<bool, void>))));

	BOOST_CHECK((!value(contains(r1, range<double, void, long>))));
	BOOST_CHECK((!value(contains(r1, range<long, bool, short, char>))));
}

BOOST_AUTO_TEST_CASE(puddle_string_contains_1)
{
	using namespace puddle;

	auto s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK(( value(contains(s1, string<'a'>))));
	BOOST_CHECK(( value(contains(s1, string<'b'>))));
	BOOST_CHECK(( value(contains(s1, string<'c'>))));
	BOOST_CHECK(( value(contains(s1, string<'d'>))));
	BOOST_CHECK(( value(contains(s1, string<'e'>))));
	BOOST_CHECK(( value(contains(s1, string<'f'>))));
	BOOST_CHECK(( value(contains(s1, string<'g'>))));
	BOOST_CHECK(( value(contains(s1, string<'h'>))));
	BOOST_CHECK((!value(contains(s1, string<'y'>))));

	BOOST_CHECK(( value(contains(empty_string, empty_string))));
	BOOST_CHECK((!value(contains(empty_string, string<'a'>))));
	BOOST_CHECK((!value(contains(empty_string, string<'x'>))));
}

BOOST_AUTO_TEST_CASE(puddle_string_contains_2)
{
	using namespace puddle;

	auto s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK(( value(contains(s1, s1))));
	BOOST_CHECK(( value(contains(s1, string<'a','b','c'>))));
	BOOST_CHECK(( value(contains(s1, string<'b','c','d','e'>))));
	BOOST_CHECK(( value(contains(s1, string<'c','d','e','f','g','h'>))));
	BOOST_CHECK(( value(contains(s1, string<'e','f','g'>))));
	BOOST_CHECK(( value(contains(s1, string<'g','h'>))));

	BOOST_CHECK((!value(contains(s1, string<'y','a','b'>))));
	BOOST_CHECK((!value(contains(s1, string<'e','z','f'>))));
	BOOST_CHECK((!value(contains(s1, string<'h','h','h','h'>))));
	BOOST_CHECK((!value(contains(s1, string<'g','h','x'>))));
}

BOOST_AUTO_TEST_SUITE_END()

