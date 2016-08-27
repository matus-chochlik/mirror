/**
 *  .file test/mirror/skip_r.cpp
 *  .brief Test case for compile-time skip operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_skip
#include <boost/test/unit_test.hpp>

#include <mirror/skip.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_skip)

BOOST_AUTO_TEST_CASE(mirror_skip_range)
{
	using namespace mirror;

	using er = empty_range;
	using r1 = range<char>;
	using r2 = range<long, char>;
	using r3 = range<int, long, char>;

	using s0 = size_const<0>;
	using s1 = size_const<1>;
	using s2 = size_const<2>;
	using s3 = size_const<3>;
	using s4 = size_const<4>;

	BOOST_CHECK(( value<equal<skip<er, s0>, er>>));
	BOOST_CHECK(( value<equal<skip<er, s1>, er>>));
	BOOST_CHECK(( value<equal<skip<er, s2>, er>>));
	BOOST_CHECK(( value<equal<skip<er, s3>, er>>));
	BOOST_CHECK(( value<equal<skip<r1, s0>, r1>>));
	BOOST_CHECK(( value<equal<skip<r1, s1>, er>>));
	BOOST_CHECK(( value<equal<skip<r1, s2>, er>>));
	BOOST_CHECK(( value<equal<skip<r2, s0>, r2>>));
	BOOST_CHECK(( value<equal<skip<r2, s1>, r1>>));
	BOOST_CHECK(( value<equal<skip<r2, s2>, er>>));
	BOOST_CHECK(( value<equal<skip<r2, s3>, er>>));
	BOOST_CHECK(( value<equal<skip<r3, s0>, r3>>));
	BOOST_CHECK(( value<equal<skip<r3, s1>, r2>>));
	BOOST_CHECK(( value<equal<skip<r3, s2>, r1>>));
	BOOST_CHECK(( value<equal<skip<r3, s3>, er>>));
	BOOST_CHECK(( value<equal<skip<r3, s4>, er>>));
}

BOOST_AUTO_TEST_CASE(mirror_skip_string)
{
	using namespace mirror;

	using e = empty_string;
	using c = string<'c'>;
	using bc = string<'b','c'>;
	using abc = string<'a','b','c'>;

	using s0 = size_const<0>;
	using s1 = size_const<1>;
	using s2 = size_const<2>;
	using s3 = size_const<3>;
	using s4 = size_const<4>;

	BOOST_CHECK(( value<equal<skip<e, s0>, e>>));
	BOOST_CHECK(( value<equal<skip<e, s1>, e>>));
	BOOST_CHECK(( value<equal<skip<c, s0>, c>>));
	BOOST_CHECK(( value<equal<skip<c, s1>, e>>));
	BOOST_CHECK(( value<equal<skip<c, s2>, e>>));
	BOOST_CHECK(( value<equal<skip<bc, s0>, bc>>));
	BOOST_CHECK(( value<equal<skip<bc, s1>, c>>));
	BOOST_CHECK(( value<equal<skip<bc, s2>, e>>));
	BOOST_CHECK(( value<equal<skip<bc, s3>, e>>));
	BOOST_CHECK(( value<equal<skip<abc, s0>, abc>>));
	BOOST_CHECK(( value<equal<skip<abc, s1>, bc>>));
	BOOST_CHECK(( value<equal<skip<abc, s2>, c>>));
	BOOST_CHECK(( value<equal<skip<abc, s3>, e>>));
	BOOST_CHECK(( value<equal<skip<abc, s4>, e>>));
}

BOOST_AUTO_TEST_SUITE_END()

