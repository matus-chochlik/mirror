/**
 *  .file test/dazzle/slice_after_r.cpp
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
#define BOOST_TEST_MODULE DAZZLE_slice_after
#include <boost/test/unit_test.hpp>

#include <dazzle/string.hpp>
#include <dazzle/range.hpp>
#include <dazzle/int_const.hpp>
#include <dazzle/type.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_slice_after)

BOOST_AUTO_TEST_CASE(dazzle_slice_after_range)
{
	using namespace dazzle;

	auto r1 = range<double, float, long, int, short, char, bool>;

	BOOST_CHECK(((
		r1.slice_after(empty_range) ==
		r1
	)));

	BOOST_CHECK(((
		r1.slice_after(type<void>) ==
		empty_range
	)));

	BOOST_CHECK(((
		r1.slice_after(range<void>) ==
		empty_range
	)));

	BOOST_CHECK(((
		r1.slice_after(range<double>) ==
		range<float, long, int, short, char, bool>
	)));

	BOOST_CHECK(((
		r1.slice_after(type<float>) ==
		range<long, int, short, char, bool>
	)));

	BOOST_CHECK(((
		r1.slice_after(range<double, float>) ==
		range<long, int, short, char, bool>
	)));

	BOOST_CHECK(((
		r1.slice_after(range<int>) ==
		range<short, char, bool>
	)));

	BOOST_CHECK(((
		r1.slice_after(type<short>) ==
		range<char, bool>
	)));

	BOOST_CHECK(((
		r1.slice_after(range<double, float, long, int>) ==
		range<short, char, bool>
	)));

	BOOST_CHECK(((
		r1.slice_after(range<float, long, int, short, char, bool>) ==
		empty_range
	)));

	BOOST_CHECK(((
		r1.slice_after(range<long, int, short, char, bool, void>) ==
		empty_range
	)));
}

BOOST_AUTO_TEST_CASE(dazzle_slice_after_string)
{
	using namespace dazzle;

	auto s1 = string<'a','b','c','d','e','f','g','h','i'>;

	BOOST_CHECK(((
		s1.slice_after(empty_string) ==
		s1
	)));

	BOOST_CHECK(((
		s1.slice_after(string<'j'>) ==
		empty_string
	)));

	BOOST_CHECK(((
		s1.slice_after(char_<'k'>) ==
		empty_string
	)));

	BOOST_CHECK(((
		s1.slice_after(char_<'a'>) ==
		string<'b','c','d','e','f','g','h','i'>
	)));

	BOOST_CHECK(((
		s1.slice_after(string<'a'>) ==
		string<'b','c','d','e','f','g','h','i'>
	)));

	BOOST_CHECK(((
		s1.slice_after(string<'b'>) ==
		string<'c','d','e','f','g','h','i'>
	)));

	BOOST_CHECK(((
		s1.slice_after(string<'e','f','g'>) ==
		string<'h','i'>
	)));

	BOOST_CHECK(((
		s1.slice_after(string<'a','b','c','d','e'>) ==
		string<'f','g','h','i'>
	)));

	BOOST_CHECK(((
		s1.slice_after(string<'c','d','e','f','g','h','i'>) ==
		empty_string
	)));

	BOOST_CHECK(((
		s1.slice_after(string<'e','f','g','h','i','j','k'>) ==
		empty_string
	)));
}

BOOST_AUTO_TEST_SUITE_END()

