/**
 *  .file test/mirror/get_tail_r.cpp
 *  .brief Test case for compile-time get_tail operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_get_tail
#include <boost/test/unit_test.hpp>

#include <mirror/get_tail.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_get_tail)

BOOST_AUTO_TEST_CASE(mirror_get_tail_range)
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

	BOOST_CHECK(( value<equal<get_tail<er, s0>, er>>));
	BOOST_CHECK(( value<equal<get_tail<er, s1>, er>>));
	BOOST_CHECK(( value<equal<get_tail<er, s2>, er>>));
	BOOST_CHECK(( value<equal<get_tail<r1, s0>, er>>));
	BOOST_CHECK(( value<equal<get_tail<r1, s1>, r1>>));
	BOOST_CHECK(( value<equal<get_tail<r1, s2>, r1>>));
	BOOST_CHECK(( value<equal<get_tail<r2, s0>, er>>));
	BOOST_CHECK(( value<equal<get_tail<r2, s1>, r1>>));
	BOOST_CHECK(( value<equal<get_tail<r2, s2>, r2>>));
	BOOST_CHECK(( value<equal<get_tail<r3, s0>, er>>));
	BOOST_CHECK(( value<equal<get_tail<r3, s1>, r1>>));
	BOOST_CHECK(( value<equal<get_tail<r3, s2>, r2>>));
	BOOST_CHECK(( value<equal<get_tail<r3, s3>, r3>>));
	BOOST_CHECK(( value<equal<get_tail<r3, s4>, r3>>));
}

BOOST_AUTO_TEST_CASE(mirror_get_tail_string)
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

	BOOST_CHECK(( value<equal<get_tail<e, s0>, e>>));
	BOOST_CHECK(( value<equal<get_tail<c, s0>, e>>));
	BOOST_CHECK(( value<equal<get_tail<c, s1>, c>>));
	BOOST_CHECK(( value<equal<get_tail<bc, s0>, e>>));
	BOOST_CHECK(( value<equal<get_tail<bc, s1>, c>>));
	BOOST_CHECK(( value<equal<get_tail<bc, s2>, bc>>));
	BOOST_CHECK(( value<equal<get_tail<bc, s3>, bc>>));
	BOOST_CHECK(( value<equal<get_tail<bc, s4>, bc>>));
	BOOST_CHECK(( value<equal<get_tail<abc, s0>, e>>));
	BOOST_CHECK(( value<equal<get_tail<abc, s1>, c>>));
	BOOST_CHECK(( value<equal<get_tail<abc, s2>, bc>>));
	BOOST_CHECK(( value<equal<get_tail<abc, s3>, abc>>));
	BOOST_CHECK(( value<equal<get_tail<abc, s4>, abc>>));
}

BOOST_AUTO_TEST_SUITE_END()

