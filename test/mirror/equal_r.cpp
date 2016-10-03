/**
 *  .file test/mirror/equal_r.cpp
 *  .brief Test case for compile-time equal operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_equal
#include <boost/test/unit_test.hpp>

#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_equal)

BOOST_AUTO_TEST_CASE(mirror_equal_range)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<empty_range, empty_range>>));
	BOOST_CHECK(( value<equal<range<int>, range<int>>>));
	BOOST_CHECK(( value<equal<range<char, int, bool>, range<char, int, bool>>>));
	BOOST_CHECK((!value<equal<range<long>, range<double>>>));
	BOOST_CHECK((!value<equal<empty_range, range<char, int, bool>>>));
	BOOST_CHECK((!value<equal<range<char>, range<char, int, bool>>>));
	BOOST_CHECK((!value<equal<range<int, bool>, range<char, int, bool>>>));
	BOOST_CHECK((!value<equal<range<char, int, bool>, range<bool, int, char>>>));
}

BOOST_AUTO_TEST_CASE(mirror_equal_string)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<empty_string, empty_string>>));
	BOOST_CHECK(( value<equal<string<'a'>, string<'a'>>>));
	BOOST_CHECK(( value<equal<string<'a','b'>, string<'a','b'>>>));
	BOOST_CHECK(( value<equal<string<'a','b','c'>, string<'a','b','c'>>>));
	BOOST_CHECK((!value<equal<string<'b'>, string<'c'>>>));
	BOOST_CHECK((!value<equal<string<'b'>, empty_string>>));
	BOOST_CHECK((!value<equal<empty_string, string<'x','y','z'>>>));
	BOOST_CHECK((!value<equal<string<'a','b'>, string<'a','b','c'>>>));
	BOOST_CHECK((!value<equal<string<'a','b','c'>, string<'a','b'>>>));
	BOOST_CHECK((!value<equal<string<'b','c'>, string<'a','b','c'>>>));
	BOOST_CHECK((!value<equal<string<'a','b','c'>, string<'b','c'>>>));
}

BOOST_AUTO_TEST_SUITE_END()

