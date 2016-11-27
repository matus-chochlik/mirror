/**
 *  .file test/dazzle/contains_r.cpp
 *  .brief Test case for compile-time contains operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_contains
#include <boost/test/unit_test.hpp>

#include <dazzle/sequence_ops.hpp>
#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_contains)

BOOST_AUTO_TEST_CASE(dazzle_range_contains_1)
{
	using namespace dazzle;

	auto r1 = range<double, float, long, int, short, char, bool, void>;

	BOOST_CHECK(( r1.contains(empty_range)));
	BOOST_CHECK(( r1.contains(range<double>)));
	BOOST_CHECK(( r1.contains(range<float>)));
	BOOST_CHECK(( r1.contains(range<long>)));
	BOOST_CHECK(( r1.contains(range<int>)));
	BOOST_CHECK(( r1.contains(range<short>)));
	BOOST_CHECK(( r1.contains(range<char>)));
	BOOST_CHECK(( r1.contains(range<bool>)));
	BOOST_CHECK(( r1.contains(range<void>)));
	BOOST_CHECK((!r1.contains(range<wchar_t>)));

	BOOST_CHECK(( empty_range.contains(empty_range)));
	BOOST_CHECK((!empty_range.contains(range<double>)));
	BOOST_CHECK((!empty_range.contains(range<wchar_t>)));
}

BOOST_AUTO_TEST_CASE(dazzle_range_contains_2)
{
	using namespace dazzle;

	auto r1 = range<double, float, long, int, short, char, bool, void>;

	BOOST_CHECK(( r1.contains(r1)));
	BOOST_CHECK(( r1.contains(range<double, float, long>)));
	BOOST_CHECK(( r1.contains(range<float, long>)));
	BOOST_CHECK(( r1.contains(range<long, int, short, char>)));
	BOOST_CHECK(( r1.contains(range<int, short>)));
	BOOST_CHECK(( r1.contains(range<char, bool, void>)));
	BOOST_CHECK(( r1.contains(range<bool, void>)));

	BOOST_CHECK((!r1.contains(range<double, void, long>)));
	BOOST_CHECK((!r1.contains(range<long, bool, short, char>)));
}

BOOST_AUTO_TEST_CASE(dazzle_string_contains_1)
{
	using namespace dazzle;

	auto s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK(( s1.contains(string<'a'>)));
	BOOST_CHECK(( s1.contains(string<'b'>)));
	BOOST_CHECK(( s1.contains(string<'c'>)));
	BOOST_CHECK(( s1.contains(string<'d'>)));
	BOOST_CHECK(( s1.contains(string<'e'>)));
	BOOST_CHECK(( s1.contains(string<'f'>)));
	BOOST_CHECK(( s1.contains(string<'g'>)));
	BOOST_CHECK(( s1.contains(string<'h'>)));
	BOOST_CHECK((!s1.contains(string<'y'>)));

	BOOST_CHECK(( empty_string.contains(empty_string)));
	BOOST_CHECK((!empty_string.contains(string<'a'>)));
	BOOST_CHECK((!empty_string.contains(string<'x'>)));
}

BOOST_AUTO_TEST_CASE(dazzle_string_contains_2)
{
	using namespace dazzle;

	auto s1 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK(( s1.contains(s1)));
	BOOST_CHECK(( s1.contains(string<'a','b','c'>)));
	BOOST_CHECK(( s1.contains(string<'b','c','d','e'>)));
	BOOST_CHECK(( s1.contains(string<'c','d','e','f','g','h'>)));
	BOOST_CHECK(( s1.contains(string<'e','f','g'>)));
	BOOST_CHECK(( s1.contains(string<'g','h'>)));

	BOOST_CHECK((!s1.contains(string<'y','a','b'>)));
	BOOST_CHECK((!s1.contains(string<'e','z','f'>)));
	BOOST_CHECK((!s1.contains(string<'h','h','h','h'>)));
	BOOST_CHECK((!s1.contains(string<'g','h','x'>)));
}

BOOST_AUTO_TEST_SUITE_END()

