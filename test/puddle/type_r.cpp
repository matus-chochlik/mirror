/**
 *  .file test/puddle/type.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_type
#include <boost/test/unit_test.hpp>

#include <puddle/type.hpp>
#include <puddle/int_const.hpp>

BOOST_AUTO_TEST_SUITE(puddle_type)

BOOST_AUTO_TEST_CASE(puddle_type_eq1)
{
	using namespace puddle;

	BOOST_CHECK( value(type<int> == type<int>));
	BOOST_CHECK( value(type<void> == type<void>));
	BOOST_CHECK( value(type<bool> == type<bool>));
	BOOST_CHECK( value(type<long> == type<long>));
	BOOST_CHECK( value(type<char> == type<char>));
	BOOST_CHECK( value(type<float> == type<float>));
	BOOST_CHECK( value(type<short> == type<short>));
	BOOST_CHECK( value(type<double> == type<double>));
	BOOST_CHECK( value(type<unsigned> == type<unsigned>));
}

BOOST_AUTO_TEST_CASE(puddle_type_eq2)
{
	using namespace puddle;

	BOOST_CHECK(!value(type<int> == type<void>));
	BOOST_CHECK(!value(type<int> == type<bool>));
	BOOST_CHECK(!value(type<int> == type<long>));
	BOOST_CHECK(!value(type<int> == type<char>));
	BOOST_CHECK(!value(type<int> == type<float>));
	BOOST_CHECK(!value(type<int> == type<short>));
	BOOST_CHECK(!value(type<int> == type<double>));
	BOOST_CHECK(!value(type<int> == type<unsigned>));

	BOOST_CHECK(!value(type<void> == type<int>));
	BOOST_CHECK(!value(type<bool> == type<int>));
	BOOST_CHECK(!value(type<long> == type<int>));
	BOOST_CHECK(!value(type<char> == type<int>));
	BOOST_CHECK(!value(type<float> == type<int>));
	BOOST_CHECK(!value(type<short> == type<int>));
	BOOST_CHECK(!value(type<double> == type<int>));
	BOOST_CHECK(!value(type<unsigned> == type<int>));
}

BOOST_AUTO_TEST_CASE(puddle_type_ne1)
{
	using namespace puddle;

	BOOST_CHECK(!value(type<int> != type<int>));
	BOOST_CHECK(!value(type<void> != type<void>));
	BOOST_CHECK(!value(type<bool> != type<bool>));
	BOOST_CHECK(!value(type<long> != type<long>));
	BOOST_CHECK(!value(type<char> != type<char>));
	BOOST_CHECK(!value(type<float> != type<float>));
	BOOST_CHECK(!value(type<short> != type<short>));
	BOOST_CHECK(!value(type<double> != type<double>));
	BOOST_CHECK(!value(type<unsigned> != type<unsigned>));
}

BOOST_AUTO_TEST_CASE(puddle_type_ne2)
{
	using namespace puddle;

	BOOST_CHECK( value(type<int> != type<void>));
	BOOST_CHECK( value(type<int> != type<bool>));
	BOOST_CHECK( value(type<int> != type<long>));
	BOOST_CHECK( value(type<int> != type<char>));
	BOOST_CHECK( value(type<int> != type<float>));
	BOOST_CHECK( value(type<int> != type<short>));
	BOOST_CHECK( value(type<int> != type<double>));
	BOOST_CHECK( value(type<int> != type<unsigned>));

	BOOST_CHECK( value(type<void> != type<int>));
	BOOST_CHECK( value(type<bool> != type<int>));
	BOOST_CHECK( value(type<long> != type<int>));
	BOOST_CHECK( value(type<char> != type<int>));
	BOOST_CHECK( value(type<float> != type<int>));
	BOOST_CHECK( value(type<short> != type<int>));
	BOOST_CHECK( value(type<double> != type<int>));
	BOOST_CHECK( value(type<unsigned> != type<int>));
}

BOOST_AUTO_TEST_SUITE_END()

