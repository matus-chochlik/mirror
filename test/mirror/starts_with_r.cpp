/**
 *  .file test/mirror/starts_with_r.cpp
 *  .brief Test case for compile-time starts_with operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_starts_with
#include <boost/test/unit_test.hpp>

#include <mirror/starts_with.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_starts_with)

BOOST_AUTO_TEST_CASE(mirror_starts_with_range)
{
	using namespace mirror;

	using er = empty_range;
	using r1 = range<int>;
	using r2 = range<int, long>;
	using r3 = range<int, long, char>;

	BOOST_CHECK(( value<starts_with<r3, er>>));
	BOOST_CHECK(( value<starts_with<r2, er>>));
	BOOST_CHECK(( value<starts_with<r1, er>>));
	BOOST_CHECK(( value<starts_with<er, er>>));
	BOOST_CHECK(( value<starts_with<r3, r1>>));
	BOOST_CHECK(( value<starts_with<r2, r1>>));
	BOOST_CHECK(( value<starts_with<r1, r1>>));
	BOOST_CHECK((!value<starts_with<er, r1>>));
	BOOST_CHECK(( value<starts_with<r3, r2>>));
	BOOST_CHECK(( value<starts_with<r2, r2>>));
	BOOST_CHECK((!value<starts_with<r1, r2>>));
	BOOST_CHECK((!value<starts_with<er, r2>>));
	BOOST_CHECK(( value<starts_with<r3, r3>>));
	BOOST_CHECK((!value<starts_with<r2, r3>>));
	BOOST_CHECK((!value<starts_with<r1, r3>>));
	BOOST_CHECK((!value<starts_with<er, r3>>));
}

BOOST_AUTO_TEST_CASE(mirror_starts_with_string)
{
	using namespace mirror;

	using e = empty_string;
	using a = string<'a'>;
	using ab = string<'a','b'>;
	using abc = string<'a','b','c'>;

	BOOST_CHECK(( value<starts_with<abc,   e>>));
	BOOST_CHECK(( value<starts_with< ab,   e>>));
	BOOST_CHECK(( value<starts_with<  a,   e>>));
	BOOST_CHECK(( value<starts_with<  e,   e>>));
	BOOST_CHECK(( value<starts_with<abc,   a>>));
	BOOST_CHECK(( value<starts_with< ab,   a>>));
	BOOST_CHECK(( value<starts_with<  a,   a>>));
	BOOST_CHECK((!value<starts_with<  e,   a>>));
	BOOST_CHECK(( value<starts_with<abc,  ab>>));
	BOOST_CHECK(( value<starts_with< ab,  ab>>));
	BOOST_CHECK((!value<starts_with<  a,  ab>>));
	BOOST_CHECK((!value<starts_with<  e,  ab>>));
	BOOST_CHECK(( value<starts_with<abc, abc>>));
	BOOST_CHECK((!value<starts_with< ab, abc>>));
	BOOST_CHECK((!value<starts_with<  a, abc>>));
	BOOST_CHECK((!value<starts_with<  e, abc>>));
}

BOOST_AUTO_TEST_SUITE_END()

