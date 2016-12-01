/**
 *  .file test/mirror/slice_r.cpp
 *  .brief Test case for compile-time slice operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_slice
#include <boost/test/unit_test.hpp>

#include <mirror/slice.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_slice)

BOOST_AUTO_TEST_CASE(mirror_slice_range)
{
	using namespace mirror;

	using er = empty_range;
	using rb = range<int, long>;
	using re = range<short, char>;
	using rc = range<long, float, short>;
	using rl = range<int, long, float, short, char>;

	using s0 = size_t_<0>;
	using s1 = size_t_<1>;
	using s2 = size_t_<2>;
	using s3 = size_t_<3>;
	using s4 = size_t_<4>;
	using s5 = size_t_<5>;

	BOOST_CHECK(( value<equal<slice<er, s0, s0>, er>>));
	BOOST_CHECK(( value<equal<slice<er, s1, s0>, er>>));
	BOOST_CHECK(( value<equal<slice<er, s5, s0>, er>>));
	BOOST_CHECK(( value<equal<slice<er, s0, s2>, er>>));
	BOOST_CHECK(( value<equal<slice<er, s0, s5>, er>>));
	BOOST_CHECK(( value<equal<slice<er, s3, s4>, er>>));

	BOOST_CHECK(( value<equal<slice<rl, s0, s0>, er>>));
	BOOST_CHECK(( value<equal<slice<rl, s3, s0>, er>>));
	BOOST_CHECK(( value<equal<slice<rl, s5, s4>, er>>));

	BOOST_CHECK(( value<equal<slice<rl, s0, s2>, rb>>));
	BOOST_CHECK(( value<equal<slice<rl, s1, s3>, rc>>));
	BOOST_CHECK(( value<equal<slice<rl, s3, s2>, re>>));
	BOOST_CHECK(( value<equal<slice<rl, s3, s4>, re>>));

	BOOST_CHECK(( value<equal<slice<rl, s2, s2>, slice<rc,s1, s2>>>));
}

BOOST_AUTO_TEST_CASE(mirror_slice_string)
{
	using namespace mirror;

	using e = empty_string;
	using abcde = string<'a','b','c','d','e'>;
	using abc = string<'a','b','c'>;
	using cde = string<'c','d','e'>;
	using bcd = string<'b','c','d'>;

	using s0 = size_t_<0>;
	using s1 = size_t_<1>;
	using s2 = size_t_<2>;
	using s3 = size_t_<3>;
	using s4 = size_t_<4>;
	using s5 = size_t_<5>;

	BOOST_CHECK(( value<equal<slice<e, s0, s0>, e>>));
	BOOST_CHECK(( value<equal<slice<e, s2, s1>, e>>));
	BOOST_CHECK(( value<equal<slice<e, s5, s0>, e>>));
	BOOST_CHECK(( value<equal<slice<e, s3, s4>, e>>));

	BOOST_CHECK(( value<equal<slice<abcde, s0, s0>, e>>));
	BOOST_CHECK(( value<equal<slice<abcde, s0, s3>, abc>>));
	BOOST_CHECK(( value<equal<slice<abcde, s1, s3>, bcd>>));
	BOOST_CHECK(( value<equal<slice<abcde, s2, s3>, cde>>));
	BOOST_CHECK(( value<equal<slice<abcde, s5, s4>, e>>));

	BOOST_CHECK(( value<equal<slice<abcde, s4, s3>, slice<cde, s2, s1>>>));
	BOOST_CHECK(( value<equal<slice<abcde, s1, s2>, slice<abc, s1, s2>>>));
	BOOST_CHECK(( value<equal<slice<abcde, s2, s1>, slice<abc, s2, s2>>>));
	BOOST_CHECK(( value<equal<slice<abcde, s2, s1>, slice<bcd, s1, s1>>>));
	BOOST_CHECK(( value<equal<slice<abcde, s2, s1>, slice<cde, s0, s1>>>));
}

BOOST_AUTO_TEST_SUITE_END()

