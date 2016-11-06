/**
 *  .file test/puddle/get_front_r.cpp
 *  .brief Test case for compile-time get_front operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_get_front
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/none.hpp>
#include <puddle/type.hpp>

BOOST_AUTO_TEST_SUITE(puddle_get_front)

BOOST_AUTO_TEST_CASE(puddle_get_front_range)
{
	using namespace puddle;

	BOOST_CHECK(value(get_front(empty_range) == none));
	BOOST_CHECK(value(get_front(range<long>) == type<long>));
	BOOST_CHECK(value(get_front(range<char>) == type<char>));
	BOOST_CHECK(value(get_front(range<int>) == type<int>));
	BOOST_CHECK(value(get_front(range<int, bool>) == type<int>));
	BOOST_CHECK(value(get_front(range<int, int, int>) == type<int>));
	BOOST_CHECK(value(get_front(range<double, float>) == type<double>));
	BOOST_CHECK(value(get_front(range<char, int, bool>) == type<char>));

	BOOST_CHECK(value(get_front(range<int, bool>) != type<bool>));
	BOOST_CHECK(value(get_front(range<double, float>) != type<float>));
	BOOST_CHECK(value(get_front(range<char, int, bool>) != type<long>));
}

BOOST_AUTO_TEST_CASE(puddle_get_front_string)
{
	using namespace puddle;

	BOOST_CHECK(value(get_front(empty_string) == none));
	BOOST_CHECK(value(get_front(string<'x'>) == char_<'x'>));
	BOOST_CHECK(value(get_front(string<'y'>) == char_<'y'>));
	BOOST_CHECK(value(get_front(string<'x','y','z'>) == char_<'x'>));
	BOOST_CHECK(value(get_front(string<'a','b','c','d'>) == char_<'a'>));

	BOOST_CHECK(value(get_front(string<'x','y','z'>) != char_<'w'>));
	BOOST_CHECK(value(get_front(string<'x','y','z'>) != char_<'y'>));
	BOOST_CHECK(value(get_front(string<'x','y','z'>) != char_<'z'>));
}

BOOST_AUTO_TEST_SUITE_END()

