/**
 *  .file test/puddle/string.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_string
#include <boost/test/unit_test.hpp>

#include <puddle/string.hpp>
#include <puddle/int_const.hpp>

BOOST_AUTO_TEST_SUITE(puddle_string)

BOOST_AUTO_TEST_CASE(puddle_string_eq)
{
	using namespace puddle;

	BOOST_CHECK( value(empty_string == string<>));
	BOOST_CHECK( value(empty_string == basic_string<char>));
	BOOST_CHECK( value(empty_string == empty_string));
	BOOST_CHECK(!value(empty_string == string<'a'>));
	BOOST_CHECK(!value(empty_string == string<'a','b'>));
	BOOST_CHECK(!value(empty_string == string<'a','b','c'>));
	BOOST_CHECK(!value(empty_string == string<'a','b','c','d'>));

	BOOST_CHECK( value(string<'a'> == string<'a'>));
	BOOST_CHECK(!value(string<'a'> == string<'b'>));
	BOOST_CHECK(!value(string<'b'> == string<'a'>));

	BOOST_CHECK( value(string<'a','b'> == string<'a','b'>));
	BOOST_CHECK( value(string<'a','b','c'> == string<'a','b','c'>));
	BOOST_CHECK( value(string<'a','b','c','d'> == string<'a','b','c','d'>));

	BOOST_CHECK(!value(string<'a'> == string<'a','b'>));
	BOOST_CHECK(!value(string<'a','b'> == string<'a'>));
	BOOST_CHECK(!value(string<'a'> == string<'b','a'>));
	BOOST_CHECK(!value(string<'b','a'> == string<'a'>));

	BOOST_CHECK(!value(string<'A','B'> == string<'a','b'>));
}

BOOST_AUTO_TEST_CASE(puddle_string_ne)
{
	using namespace puddle;

	BOOST_CHECK(!value(empty_string != string<>));
	BOOST_CHECK(!value(empty_string != basic_string<char>));
	BOOST_CHECK(!value(empty_string != empty_string));
	BOOST_CHECK( value(empty_string != string<'a'>));
	BOOST_CHECK( value(empty_string != string<'a','b'>));
	BOOST_CHECK( value(empty_string != string<'a','b','c'>));
	BOOST_CHECK( value(empty_string != string<'a','b','c','d'>));

	BOOST_CHECK(!value(string<'a'> != string<'a'>));
	BOOST_CHECK( value(string<'a'> != string<'b'>));
	BOOST_CHECK( value(string<'b'> != string<'a'>));

	BOOST_CHECK(!value(string<'a','b'> != string<'a','b'>));
	BOOST_CHECK(!value(string<'a','b','c'> != string<'a','b','c'>));
	BOOST_CHECK(!value(string<'a','b','c','d'> != string<'a','b','c','d'>));

	BOOST_CHECK( value(string<'a'> != string<'a','b'>));
	BOOST_CHECK( value(string<'a','b'> != string<'a'>));
	BOOST_CHECK( value(string<'a'> != string<'b','a'>));
	BOOST_CHECK( value(string<'b','a'> != string<'a'>));

	BOOST_CHECK( value(string<'A','B'> != string<'a','b'>));
}

BOOST_AUTO_TEST_SUITE_END()

