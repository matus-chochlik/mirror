/**
 *  .file test/dazzle/skip_r.cpp
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
#define BOOST_TEST_MODULE DAZZLE_skip
#include <boost/test/unit_test.hpp>

#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_skip)

BOOST_AUTO_TEST_CASE(dazzle_skip_range)
{
	using namespace dazzle;

	auto er = empty_range;
	auto r1 = range<char>;
	auto r2 = range<long, char>;
	auto r3 = range<int, long, char>;

	auto s0 = size_t_<0>;
	auto s1 = size_t_<1>;
	auto s2 = size_t_<2>;
	auto s3 = size_t_<3>;
	auto s4 = size_t_<4>;

	BOOST_CHECK(( er.skip(s0) == er));
	BOOST_CHECK(( er.skip(s1) == er));
	BOOST_CHECK(( er.skip(s2) == er));
	BOOST_CHECK(( er.skip(s3) == er));
	BOOST_CHECK(( r1.skip(s0) == r1));
	BOOST_CHECK(( r1.skip(s1) == er));
	BOOST_CHECK(( r1.skip(s2) == er));
	BOOST_CHECK(( r2.skip(s0) == r2));
	BOOST_CHECK(( r2.skip(s1) == r1));
	BOOST_CHECK(( r2.skip(s2) == er));
	BOOST_CHECK(( r2.skip(s3) == er));
	BOOST_CHECK(( r3.skip(s0) == r3));
	BOOST_CHECK(( r3.skip(s1) == r2));
	BOOST_CHECK(( r3.skip(s2) == r1));
	BOOST_CHECK(( r3.skip(s3) == er));
	BOOST_CHECK(( r3.skip(s4) == er));
}

BOOST_AUTO_TEST_CASE(dazzle_skip_string)
{
	using namespace dazzle;

	auto e = empty_string;
	auto c = string<'c'>;
	auto bc = string<'b','c'>;
	auto abc = string<'a','b','c'>;

	auto s0 = size_t_<0>;
	auto s1 = size_t_<1>;
	auto s2 = size_t_<2>;
	auto s3 = size_t_<3>;
	auto s4 = size_t_<4>;

	BOOST_CHECK(( e.skip(s0) == e));
	BOOST_CHECK(( e.skip(s1) == e));
	BOOST_CHECK(( c.skip(s0) == c));
	BOOST_CHECK(( c.skip(s1) == e));
	BOOST_CHECK(( c.skip(s2) == e));
	BOOST_CHECK(( bc.skip(s0) == bc));
	BOOST_CHECK(( bc.skip(s1) == c));
	BOOST_CHECK(( bc.skip(s2) == e));
	BOOST_CHECK(( bc.skip(s3) == e));
	BOOST_CHECK(( abc.skip(s0) == abc));
	BOOST_CHECK(( abc.skip(s1) == bc));
	BOOST_CHECK(( abc.skip(s2) == c));
	BOOST_CHECK(( abc.skip(s3) == e));
	BOOST_CHECK(( abc.skip(s4) == e));
}

BOOST_AUTO_TEST_SUITE_END()

