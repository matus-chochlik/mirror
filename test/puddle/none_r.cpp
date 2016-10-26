/**
 *  .file test/puddle/none.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_none
#include <boost/test/unit_test.hpp>

#include <puddle/none.hpp>
#include <puddle/type.hpp>
#include <puddle/string.hpp>
#include <puddle/int_const.hpp>

BOOST_AUTO_TEST_SUITE(puddle_none)

BOOST_AUTO_TEST_CASE(puddle_none_1)
{
	using namespace puddle;

	BOOST_CHECK( value(none == none));
	BOOST_CHECK(!value(none != none));
}

BOOST_AUTO_TEST_CASE(puddle_none_2)
{
	using namespace puddle;

	BOOST_CHECK(!value(none == false));
	BOOST_CHECK( value(none != false));
	BOOST_CHECK(!value(none == 1));
	BOOST_CHECK( value(none != 1));
	BOOST_CHECK(!value(none == 23.45));
	BOOST_CHECK( value(none != 23.45));
}

BOOST_AUTO_TEST_CASE(puddle_none_3)
{
	using namespace puddle;

	BOOST_CHECK(!value(none == true_));
	BOOST_CHECK( value(none != true_));
	BOOST_CHECK(!value(none == int_<1>));
	BOOST_CHECK( value(none != int_<1>));
	BOOST_CHECK(!value(none == type<long>));
	BOOST_CHECK( value(none != type<long>));
	BOOST_CHECK(!value(none == string<'x'>));
	BOOST_CHECK( value(none != string<'x'>));
}

BOOST_AUTO_TEST_SUITE_END()

