/**
 *  .file test/mirror/push_back_r.cpp
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
#define BOOST_TEST_MODULE MIRROR_push_back
#include <boost/test/unit_test.hpp>

#include <mirror/push_back.hpp>
#include <mirror/equal.hpp>

BOOST_AUTO_TEST_SUITE(mirror_push_back)

BOOST_AUTO_TEST_CASE(mirror_push_back_range)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<
		push_back<empty_range, char>,
		range<char>
	>>));
	BOOST_CHECK((value<equal<
		push_back<range<char>, int>,
		range<char, int>
	>>));
	BOOST_CHECK((value<equal<
		push_back<range<char, int>, bool>,
		range<char, int, bool>
	>>));
	BOOST_CHECK((value<equal<
		push_back<push_back<range<char>, int>, bool>,
		range<char, int, bool>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_push_back_string)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<
		push_back<empty_string, char_<'x'>>,
		string<'x'>
	>>));

	BOOST_CHECK((value<equal<
		push_back<string<'y'>, char_<'x'>>,
		string<'y','x'>
	>>));

	BOOST_CHECK((value<equal<
		push_back<string<'z','y'>, char_<'x'>>,
		string<'z','y','x'>
	>>));

	BOOST_CHECK((value<equal<
		push_back<push_back<string<'z'>, char_<'y'>>, char_<'x'>>,
		string<'z','y','x'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

