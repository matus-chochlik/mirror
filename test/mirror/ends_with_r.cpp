/**
 *  .file test/mirror/ends_with_r.cpp
 *  .brief Test case for compile-time ends_with operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_ends_with
#include <boost/test/unit_test.hpp>

#include <mirror/ends_with.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_ends_with)

BOOST_AUTO_TEST_CASE(mirror_ends_with_range)
{
	using namespace mirror;

	using er = empty_range;
	using r1 = range<char>;
	using r2 = range<long, char>;
	using r3 = range<int, long, char>;

	BOOST_CHECK(( value<ends_with<r3, er>>));
	BOOST_CHECK(( value<ends_with<r2, er>>));
	BOOST_CHECK(( value<ends_with<r1, er>>));
	BOOST_CHECK(( value<ends_with<er, er>>));
	BOOST_CHECK(( value<ends_with<r3, r1>>));
	BOOST_CHECK(( value<ends_with<r2, r1>>));
	BOOST_CHECK(( value<ends_with<r1, r1>>));
	BOOST_CHECK((!value<ends_with<er, r1>>));
	BOOST_CHECK(( value<ends_with<r3, r2>>));
	BOOST_CHECK(( value<ends_with<r2, r2>>));
	BOOST_CHECK((!value<ends_with<r1, r2>>));
	BOOST_CHECK((!value<ends_with<er, r2>>));
	BOOST_CHECK(( value<ends_with<r3, r3>>));
	BOOST_CHECK((!value<ends_with<r2, r3>>));
	BOOST_CHECK((!value<ends_with<r1, r3>>));
	BOOST_CHECK((!value<ends_with<er, r3>>));
}

BOOST_AUTO_TEST_CASE(mirror_ends_with_string)
{
	using namespace mirror;

	using e = empty_string;
	using c = string<'c'>;
	using bc = string<'b','c'>;
	using abc = string<'a','b','c'>;

	BOOST_CHECK(( value<ends_with<abc,   e>>));
	BOOST_CHECK(( value<ends_with< bc,   e>>));
	BOOST_CHECK(( value<ends_with<  c,   e>>));
	BOOST_CHECK(( value<ends_with<  e,   e>>));
	BOOST_CHECK(( value<ends_with<abc,   c>>));
	BOOST_CHECK(( value<ends_with< bc,   c>>));
	BOOST_CHECK(( value<ends_with<  c,   c>>));
	BOOST_CHECK((!value<ends_with<  e,   c>>));
	BOOST_CHECK(( value<ends_with<abc,  bc>>));
	BOOST_CHECK(( value<ends_with< bc,  bc>>));
	BOOST_CHECK((!value<ends_with<  c,  bc>>));
	BOOST_CHECK((!value<ends_with<  e,  bc>>));
	BOOST_CHECK(( value<ends_with<abc, abc>>));
	BOOST_CHECK((!value<ends_with< bc, abc>>));
	BOOST_CHECK((!value<ends_with<  c, abc>>));
	BOOST_CHECK((!value<ends_with<  e, abc>>));
}

BOOST_AUTO_TEST_SUITE_END()

