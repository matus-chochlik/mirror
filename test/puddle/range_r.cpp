/**
 *  .file test/puddle/range.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_range
#include <boost/test/unit_test.hpp>

#include <puddle/range.hpp>
#include <puddle/int_const.hpp>

BOOST_AUTO_TEST_SUITE(puddle_range)

BOOST_AUTO_TEST_CASE(puddle_range_eq)
{
	using namespace puddle;

	BOOST_CHECK( value(empty_range == range<>));
	BOOST_CHECK( value(empty_range == empty_range));
	BOOST_CHECK(!value(empty_range == range<int>));
	BOOST_CHECK(!value(range<int> == range<>));

	BOOST_CHECK( value(range<long> == range<long>));
	BOOST_CHECK(!value(range<char> == range<long>));
	BOOST_CHECK(!value(range<long> == range<char>));

	BOOST_CHECK( value(range<long, int, float> == range<long, int, float>));
	BOOST_CHECK( value(range<unsigned, char> == range<unsigned, char>));

	BOOST_CHECK(!value(range<long, int, float> == range<long, int>));
	BOOST_CHECK(!value(range<long, int, float> == range<long>));
	BOOST_CHECK(!value(range<long, int, float> == range<int, float>));
	BOOST_CHECK(!value(range<long, int, float> == range<float>));

	BOOST_CHECK(!value(range<long, int> == range<long, int, float>));
	BOOST_CHECK(!value(range<long> == range<long, int, float>));
	BOOST_CHECK(!value(range<int, float> == range<long, int, float>));
	BOOST_CHECK(!value(range<float> == range<long, int, float>));
}

BOOST_AUTO_TEST_CASE(puddle_range_ne)
{
	using namespace puddle;

	BOOST_CHECK(!value(empty_range != range<>));
	BOOST_CHECK(!value(empty_range != empty_range));
	BOOST_CHECK( value(empty_range != range<int>));
	BOOST_CHECK( value(range<int> != range<>));

	BOOST_CHECK(!value(range<long> != range<long>));
	BOOST_CHECK( value(range<char> != range<long>));
	BOOST_CHECK( value(range<long> != range<char>));

	BOOST_CHECK(!value(range<long, int, float> != range<long, int, float>));
	BOOST_CHECK(!value(range<unsigned, char> != range<unsigned, char>));

	BOOST_CHECK( value(range<long, int, float> != range<long, int>));
	BOOST_CHECK( value(range<long, int, float> != range<long>));
	BOOST_CHECK( value(range<long, int, float> != range<int, float>));
	BOOST_CHECK( value(range<long, int, float> != range<float>));

	BOOST_CHECK( value(range<long, int> != range<long, int, float>));
	BOOST_CHECK( value(range<long> != range<long, int, float>));
	BOOST_CHECK( value(range<int, float> != range<long, int, float>));
	BOOST_CHECK( value(range<float> != range<long, int, float>));
}

BOOST_AUTO_TEST_SUITE_END()

