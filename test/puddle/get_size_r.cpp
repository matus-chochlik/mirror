/**
 *  .file test/puddle/get_size_r.cpp
 *  .brief Test case for compile-time get_size operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_get_size
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/none.hpp>

BOOST_AUTO_TEST_SUITE(puddle_get_size)

BOOST_AUTO_TEST_CASE(puddle_get_size_none)
{
	using namespace puddle;

	BOOST_CHECK((value(get_size(none)) == 0));
}

BOOST_AUTO_TEST_CASE(puddle_get_size_range)
{
	using namespace puddle;

	BOOST_CHECK((value(get_size(empty_range)) == 0));
	BOOST_CHECK((value(get_size(range<long>)) == 1));
	BOOST_CHECK((value(get_size(range<short, int>)) == 2));
	BOOST_CHECK((value(get_size(range<int, long, float>)) == 3));
	BOOST_CHECK((value(size(range<long, float, double, bool>)) == 4));
}

BOOST_AUTO_TEST_CASE(puddle_get_size_string)
{
	using namespace puddle;

	BOOST_CHECK((value(get_size(empty_string)) == 0));
	BOOST_CHECK((value(get_size(string<'x'>)) == 1));
	BOOST_CHECK((value(get_size(string<'x','y'>)) == 2));
	BOOST_CHECK((value(size(basic_string<wchar_t,L's',L't',L'r'>)) == 3));
	BOOST_CHECK((value(size(string<'a','b','c','d'>)) == 4));
}

BOOST_AUTO_TEST_SUITE_END()

