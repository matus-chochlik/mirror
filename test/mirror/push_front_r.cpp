/**
 *  .file test/mirror/push_front_r.cpp
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
#define BOOST_TEST_MODULE MIRROR_push_front
#include <boost/test/unit_test.hpp>

#include <mirror/push_front.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_push_front)

BOOST_AUTO_TEST_CASE(mirror_push_front_range)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<
		push_front<empty_range, char>,
		range<char>
	>>));
	BOOST_CHECK((value<equal<
		push_front<range<char>, int>,
		range<int, char>
	>>));
	BOOST_CHECK((value<equal<
		push_front<range<char, int>, bool>,
		range<bool, char, int>
	>>));
	BOOST_CHECK((value<equal<
		push_front<push_front<range<char>, int>, bool>,
		range<bool, int, char>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_push_front_string)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<
		push_front<empty_string, char_<'x'>>,
		string<'x'>
	>>));

	BOOST_CHECK((value<equal<
		push_front<string<'y'>, char_<'x'>>,
		string<'x','y'>
	>>));

	BOOST_CHECK((value<equal<
		push_front<string<'y','z'>, char_<'x'>>,
		string<'x','y','z'>
	>>));

	BOOST_CHECK((value<equal<
		push_front<push_front<string<'z'>, char_<'y'>>, char_<'x'>>,
		string<'x','y','z'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

