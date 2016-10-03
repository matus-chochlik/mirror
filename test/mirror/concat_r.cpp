/**
 *  .file test/mirror/concat_r.cpp
 *  .brief Test case for compile-time concat operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_concat
#include <boost/test/unit_test.hpp>

#include <mirror/concat.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_concat)

BOOST_AUTO_TEST_CASE(mirror_concat_range)
{
	using namespace mirror;

	using er = empty_range;
	using r1 = range<int, long, char>;
	using r2 = range<bool, float, void>;
	using r3 = range<char, bool, float>;
	using r4 = range<int, long>;
	using r5 = range<void>;

	BOOST_CHECK(( value<equal<concat<er>, er>>));
	BOOST_CHECK(( value<equal<concat<r1>, r1>>));
	BOOST_CHECK(( value<equal<concat<er, er>, er>>));
	BOOST_CHECK(( value<equal<concat<r1, er>, r1>>));
	BOOST_CHECK(( value<equal<concat<er, r1>, r1>>));
	BOOST_CHECK((!value<equal<concat<r1, r2>, r3>>));
	BOOST_CHECK(( value<equal<concat<r1, r2>, concat<r4, r3, r5>>>));
	BOOST_CHECK((!value<equal<concat<r1, r2>, concat<r3, r4, r5>>>));
	BOOST_CHECK((!value<equal<concat<r1, r2>, r4>>));
}

BOOST_AUTO_TEST_CASE(mirror_concat_string)
{
	using namespace mirror;

	using e = empty_string;
	using a = string<'a'>;
	using b = string<'b'>;
	using ab = string<'a','b'>;
	using cd = string<'c','d'>;
	using abcd = string<'a','b','c','d'>;

	BOOST_CHECK(( value<equal<concat<e>, e>>));
	BOOST_CHECK(( value<equal<concat<a>, a>>));
	BOOST_CHECK(( value<equal<concat<e, e>, e>>));
	BOOST_CHECK(( value<equal<concat<a, e>, a>>));
	BOOST_CHECK(( value<equal<concat<e, b>, b>>));
	BOOST_CHECK(( value<equal<concat<a, b>, ab>>));
	BOOST_CHECK((!value<equal<concat<a, a>, ab>>));
	BOOST_CHECK((!value<equal<concat<b, a>, ab>>));
	BOOST_CHECK(( value<equal<concat<ab, cd>, abcd>>));
	BOOST_CHECK((!value<equal<concat<cd, ab>, abcd>>));
	BOOST_CHECK(( value<equal<concat<a, b, cd>, concat<ab, cd>>>));
	BOOST_CHECK(( value<equal<concat<concat<a, b>, cd>, abcd>>));
}

BOOST_AUTO_TEST_SUITE_END()

