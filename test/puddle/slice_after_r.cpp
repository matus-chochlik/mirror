/**
 *  .file test/puddle/slice_after_r.cpp
 *  .brief Test case for compile-time slice_after operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_slice_after
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/int_const.hpp>
#include <puddle/type.hpp>

BOOST_AUTO_TEST_SUITE(puddle_slice_after)

BOOST_AUTO_TEST_CASE(puddle_slice_after_range)
{
	using namespace puddle;

	auto r1 = range<double, float, long, int, short, char, bool>;

	BOOST_CHECK(( value(
		slice_after(r1, empty_range) ==
		r1
	)));

	BOOST_CHECK(( value(
		slice_after(r1, type<void>) ==
		empty_range
	)));

	BOOST_CHECK(( value(
		slice_after(r1, range<void>) ==
		empty_range
	)));

	BOOST_CHECK(( value(
		slice_after(r1, range<double>) ==
		range<float, long, int, short, char, bool>
	)));

	BOOST_CHECK(( value(
		slice_after(r1, type<float>) ==
		range<long, int, short, char, bool>
	)));

	BOOST_CHECK(( value(
		slice_after(r1, range<double, float>) ==
		range<long, int, short, char, bool>
	)));

	BOOST_CHECK(( value(
		slice_after(r1, range<int>) ==
		range<short, char, bool>
	)));

	BOOST_CHECK(( value(
		slice_after(r1, type<short>) ==
		range<char, bool>
	)));

	BOOST_CHECK(( value(
		slice_after(r1, range<double, float, long, int>) ==
		range<short, char, bool>
	)));

	BOOST_CHECK(( value(
		slice_after(r1, range<float, long, int, short, char, bool>) ==
		empty_range
	)));

	BOOST_CHECK(( value(
		slice_after(r1, range<long, int, short, char, bool, void>) ==
		empty_range
	)));
}

BOOST_AUTO_TEST_CASE(puddle_slice_after_string)
{
	using namespace puddle;

	auto s1 = string<'a','b','c','d','e','f','g','h','i'>;

	BOOST_CHECK(( value(
		slice_after(s1, empty_string) ==
		s1
	)));

	BOOST_CHECK(( value(
		slice_after(s1, string<'j'>) ==
		empty_string
	)));

	BOOST_CHECK(( value(
		slice_after(s1, char_<'k'>) ==
		empty_string
	)));

	BOOST_CHECK(( value(
		slice_after(s1, char_<'a'>) ==
		string<'b','c','d','e','f','g','h','i'>
	)));

	BOOST_CHECK(( value(
		slice_after(s1, string<'a'>) ==
		string<'b','c','d','e','f','g','h','i'>
	)));

	BOOST_CHECK(( value(
		slice_after(s1, string<'b'>) ==
		string<'c','d','e','f','g','h','i'>
	)));

	BOOST_CHECK(( value(
		slice_after(s1, string<'e','f','g'>) ==
		string<'h','i'>
	)));

	BOOST_CHECK(( value(
		slice_after(s1, string<'a','b','c','d','e'>) ==
		string<'f','g','h','i'>
	)));

	BOOST_CHECK(( value(
		slice_after(s1, string<'c','d','e','f','g','h','i'>) ==
		empty_string
	)));

	BOOST_CHECK(( value(
		slice_after(s1, string<'e','f','g','h','i','j','k'>) ==
		empty_string
	)));
}

BOOST_AUTO_TEST_SUITE_END()

