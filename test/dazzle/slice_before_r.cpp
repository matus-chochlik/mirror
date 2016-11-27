/**
 *  .file test/dazzle/slice_before_r.cpp
 *  .brief Test case for compile-time slice_before operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_slice_before
#include <boost/test/unit_test.hpp>

#include <dazzle/string.hpp>
#include <dazzle/range.hpp>
#include <dazzle/int_const.hpp>
#include <dazzle/type.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_slice_before)

BOOST_AUTO_TEST_CASE(dazzle_slice_before_range)
{
	using namespace dazzle;

	auto r1 = range<double, float, long, int, short, char, bool>;

	BOOST_CHECK(((
		r1.slice_before(empty_range) ==
		empty_range
	)));

	BOOST_CHECK(((
		r1.slice_before(type<void>) ==
		r1
	)));

	BOOST_CHECK(((
		r1.slice_before(range<void>) ==
		r1
	)));

	BOOST_CHECK(((
		r1.slice_before(range<double>) ==
		empty_range
	)));

	BOOST_CHECK(((
		r1.slice_before(range<double, float>) ==
		empty_range
	)));

	BOOST_CHECK(((
		r1.slice_before(range<double, float, unsigned>) ==
		r1
	)));

	BOOST_CHECK(((
		r1.slice_before(type<long>) ==
		range<double, float>
	)));

	BOOST_CHECK(((
		r1.slice_before(range<int, short, char>) ==
		range<double, float, long>
	)));

	BOOST_CHECK(((
		r1.slice_before(range<int, short, bool>) ==
		r1
	)));

	BOOST_CHECK(((
		r1.slice_before(type<char>) ==
		range<double, float, long, int, short>
	)));

	BOOST_CHECK(((
		r1.slice_before(range<char>) ==
		range<double, float, long, int, short>
	)));

	BOOST_CHECK(((
		r1.slice_before(range<bool>) ==
		range<double, float, long, int, short, char>
	)));
}

BOOST_AUTO_TEST_CASE(dazzle_slice_before_string)
{
	using namespace dazzle;

	auto s1 = string<'a','b','c','d','e','f','g','h','i'>;

	BOOST_CHECK(((
		s1.slice_before(empty_string) ==
		empty_string
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'j'>) ==
		s1
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'a'>) ==
		empty_string
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'a','b','c'>) ==
		empty_string
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'a','b','x'>) ==
		s1
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'e'>) ==
		string<'a','b','c','d'>
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'d','e','f','g'>) ==
		string<'a','b','c'>
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'g','h','i'>) ==
		string<'a','b','c','d','e','f'>
	)));

	BOOST_CHECK(((
		s1.slice_before(string<'i'>) ==
		string<'a','b','c','d','e','f','g','h'>
	)));
}

BOOST_AUTO_TEST_SUITE_END()

