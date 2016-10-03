/**
 *  .file test/mirror/get_head_r.cpp
 *  .brief Test case for compile-time get_head operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_get_head
#include <boost/test/unit_test.hpp>

#include <mirror/get_head.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_get_head)

BOOST_AUTO_TEST_CASE(mirror_get_head_range)
{
	using namespace mirror;

	using er = empty_range;
	using r1 = range<int>;
	using r2 = range<int, long>;
	using r3 = range<int, long, char>;

	using s0 = size_const<0>;
	using s1 = size_const<1>;
	using s2 = size_const<2>;
	using s3 = size_const<3>;
	using s4 = size_const<4>;

	BOOST_CHECK(( value<equal<get_head<er, s0>, er>>));
	BOOST_CHECK(( value<equal<get_head<er, s1>, er>>));
	BOOST_CHECK(( value<equal<get_head<er, s2>, er>>));
	BOOST_CHECK(( value<equal<get_head<r1, s0>, er>>));
	BOOST_CHECK(( value<equal<get_head<r1, s1>, r1>>));
	BOOST_CHECK(( value<equal<get_head<r1, s2>, r1>>));
	BOOST_CHECK(( value<equal<get_head<r2, s0>, er>>));
	BOOST_CHECK(( value<equal<get_head<r2, s1>, r1>>));
	BOOST_CHECK(( value<equal<get_head<r2, s2>, r2>>));
	BOOST_CHECK(( value<equal<get_head<r3, s0>, er>>));
	BOOST_CHECK(( value<equal<get_head<r3, s1>, r1>>));
	BOOST_CHECK(( value<equal<get_head<r3, s2>, r2>>));
	BOOST_CHECK(( value<equal<get_head<r3, s3>, r3>>));
	BOOST_CHECK(( value<equal<get_head<r3, s4>, r3>>));
}

BOOST_AUTO_TEST_CASE(mirror_get_head_string)
{
	using namespace mirror;

	using e = empty_string;
	using a = string<'a'>;
	using ab = string<'a','b'>;
	using abc = string<'a','b','c'>;

	using s0 = size_const<0>;
	using s1 = size_const<1>;
	using s2 = size_const<2>;
	using s3 = size_const<3>;
	using s4 = size_const<4>;

	BOOST_CHECK(( value<equal<get_head<e, s0>, e>>));
	BOOST_CHECK(( value<equal<get_head<a, s0>, e>>));
	BOOST_CHECK(( value<equal<get_head<a, s1>, a>>));
	BOOST_CHECK(( value<equal<get_head<ab, s0>, e>>));
	BOOST_CHECK(( value<equal<get_head<ab, s1>, a>>));
	BOOST_CHECK(( value<equal<get_head<ab, s2>, ab>>));
	BOOST_CHECK(( value<equal<get_head<ab, s3>, ab>>));
	BOOST_CHECK(( value<equal<get_head<ab, s4>, ab>>));
	BOOST_CHECK(( value<equal<get_head<abc, s0>, e>>));
	BOOST_CHECK(( value<equal<get_head<abc, s1>, a>>));
	BOOST_CHECK(( value<equal<get_head<abc, s2>, ab>>));
	BOOST_CHECK(( value<equal<get_head<abc, s3>, abc>>));
	BOOST_CHECK(( value<equal<get_head<abc, s4>, abc>>));
}

BOOST_AUTO_TEST_SUITE_END()

