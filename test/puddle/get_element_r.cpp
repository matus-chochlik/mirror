/**
 *  .file test/puddle/get_element_r.cpp
 *  .brief Test case for compile-time get_element operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_get_element
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/none.hpp>
#include <puddle/type.hpp>

BOOST_AUTO_TEST_SUITE(puddle_get_element)

BOOST_AUTO_TEST_CASE(puddle_get_element_range)
{
	using namespace puddle;

	BOOST_CHECK(value(get_element(empty_range, size_t_<0>) == none));
	BOOST_CHECK(value(get_element(empty_range, size_t_<1>) == none));
	BOOST_CHECK(value(get_element(empty_range, size_t_<2>) == none));

	BOOST_CHECK(value(get_element(range<long>, size_t_<0>) == type<long>));
	BOOST_CHECK(value(get_element(range<long>, size_t_<1>) == none));
	BOOST_CHECK(value(get_element(range<long>, size_t_<2>) == none));
	BOOST_CHECK(value(get_element(range<long>, size_t_<9>) == none));

	auto r1 = range<int, int, int>;

	BOOST_CHECK(value(get_element(r1, size_t_<0>) == type<int>));
	BOOST_CHECK(value(get_element(r1, size_t_<1>) == type<int>));
	BOOST_CHECK(value(get_element(r1, size_t_<2>) == type<int>));
	BOOST_CHECK(value(get_element(r1, size_t_<3>) == none));
	BOOST_CHECK(value(get_element(r1, size_t_<9>) == none));

	auto r2 = range<char, int, bool, float>;

	BOOST_CHECK(value(get_element(r2, size_t_<0>) == type<char>));
	BOOST_CHECK(value(get_element(r2, size_t_<1>) == type<int>));
	BOOST_CHECK(value(get_element(r2, size_t_<2>) == type<bool>));
	BOOST_CHECK(value(get_element(r2, size_t_<3>) == type<float>));
	BOOST_CHECK(value(get_element(r2, size_t_<4>) == none));
	BOOST_CHECK(value(get_element(r2, size_t_<123>) == none));
}

BOOST_AUTO_TEST_CASE(puddle_get_element_string)
{
	using namespace puddle;

	BOOST_CHECK(value(get_element(empty_string, size_t_<0>) == none));
	BOOST_CHECK(value(get_element(empty_string, size_t_<1>) == none));
	BOOST_CHECK(value(get_element(empty_string, size_t_<2>) == none));

	BOOST_CHECK(value(get_element(string<'x'>, size_t_<0>) == char_<'x'>));
	BOOST_CHECK(value(get_element(string<'x'>, size_t_<1>) == none));
	BOOST_CHECK(value(get_element(string<'x'>, size_t_<2>) == none));
	BOOST_CHECK(value(get_element(string<'x'>, size_t_<9>) == none));

	auto s1 = string<'x','y','z'>;

	BOOST_CHECK(value(get_element(s1, size_t_<0>) == char_<'x'>));
	BOOST_CHECK(value(get_element(s1, size_t_<1>) == char_<'y'>));
	BOOST_CHECK(value(get_element(s1, size_t_<2>) == char_<'z'>));
	BOOST_CHECK(value(get_element(s1, size_t_<3>) == none));

	auto s2 = string<'a','b','c','d','e','f','g','h'>;

	BOOST_CHECK(value(get_element(s2, size_t_<0>) == char_<'a'>));
	BOOST_CHECK(value(get_element(s2, size_t_<1>) == char_<'b'>));
	BOOST_CHECK(value(get_element(s2, size_t_<2>) == char_<'c'>));
	BOOST_CHECK(value(get_element(s2, size_t_<3>) == char_<'d'>));
	BOOST_CHECK(value(get_element(s2, size_t_<4>) == char_<'e'>));
	BOOST_CHECK(value(get_element(s2, size_t_<5>) == char_<'f'>));
	BOOST_CHECK(value(get_element(s2, size_t_<6>) == char_<'g'>));
	BOOST_CHECK(value(get_element(s2, size_t_<7>) == char_<'h'>));
	BOOST_CHECK(value(get_element(s2, size_t_<8>) == none));
	BOOST_CHECK(value(get_element(s2, size_t_<9>) == none));
}

BOOST_AUTO_TEST_SUITE_END()

