/**
 *  .file test/dazzle/range.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_range
#include <boost/test/unit_test.hpp>

#include <dazzle/range.hpp>
#include <dazzle/int_const.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_range)

BOOST_AUTO_TEST_CASE(dazzle_range_eq)
{
	using namespace dazzle;

	BOOST_CHECK( (empty_range == range<>));
	BOOST_CHECK( (empty_range == empty_range));
	BOOST_CHECK(!(empty_range == range<int>));
	BOOST_CHECK(!(range<int> == range<>));

	BOOST_CHECK( (range<long> == range<long>));
	BOOST_CHECK(!(range<char> == range<long>));
	BOOST_CHECK(!(range<long> == range<char>));

	BOOST_CHECK( (range<long, int, float> == range<long, int, float>));
	BOOST_CHECK( (range<unsigned, char> == range<unsigned, char>));

	BOOST_CHECK(!(range<long, int, float> == range<long, int>));
	BOOST_CHECK(!(range<long, int, float> == range<long>));
	BOOST_CHECK(!(range<long, int, float> == range<int, float>));
	BOOST_CHECK(!(range<long, int, float> == range<float>));

	BOOST_CHECK(!(range<long, int> == range<long, int, float>));
	BOOST_CHECK(!(range<long> == range<long, int, float>));
	BOOST_CHECK(!(range<int, float> == range<long, int, float>));
	BOOST_CHECK(!(range<float> == range<long, int, float>));
}

BOOST_AUTO_TEST_CASE(dazzle_range_ne)
{
	using namespace dazzle;

	BOOST_CHECK(!(empty_range != range<>));
	BOOST_CHECK(!(empty_range != empty_range));
	BOOST_CHECK( (empty_range != range<int>));
	BOOST_CHECK( (range<int> != range<>));

	BOOST_CHECK(!(range<long> != range<long>));
	BOOST_CHECK( (range<char> != range<long>));
	BOOST_CHECK( (range<long> != range<char>));

	BOOST_CHECK(!(range<long, int, float> != range<long, int, float>));
	BOOST_CHECK(!(range<unsigned, char> != range<unsigned, char>));

	BOOST_CHECK( (range<long, int, float> != range<long, int>));
	BOOST_CHECK( (range<long, int, float> != range<long>));
	BOOST_CHECK( (range<long, int, float> != range<int, float>));
	BOOST_CHECK( (range<long, int, float> != range<float>));

	BOOST_CHECK( (range<long, int> != range<long, int, float>));
	BOOST_CHECK( (range<long> != range<long, int, float>));
	BOOST_CHECK( (range<int, float> != range<long, int, float>));
	BOOST_CHECK( (range<float> != range<long, int, float>));
}

BOOST_AUTO_TEST_SUITE_END()

