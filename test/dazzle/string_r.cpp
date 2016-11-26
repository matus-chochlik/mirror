/**
 *  .file test/dazzle/string.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_string
#include <boost/test/unit_test.hpp>

#include <dazzle/string.hpp>
#include <dazzle/int_const.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_string)

BOOST_AUTO_TEST_CASE(dazzle_string_eq)
{
	using namespace dazzle;

	BOOST_CHECK( (empty_string == string<>));
	BOOST_CHECK( (empty_string == basic_string<char>));
	BOOST_CHECK( (empty_string == empty_string));
	BOOST_CHECK(!(empty_string == string<'a'>));
	BOOST_CHECK(!(empty_string == string<'a','b'>));
	BOOST_CHECK(!(empty_string == string<'a','b','c'>));
	BOOST_CHECK(!(empty_string == string<'a','b','c','d'>));

	BOOST_CHECK( (string<'a'> == string<'a'>));
	BOOST_CHECK(!(string<'a'> == string<'b'>));
	BOOST_CHECK(!(string<'b'> == string<'a'>));

	BOOST_CHECK( (string<'a','b'> == string<'a','b'>));
	BOOST_CHECK( (string<'a','b','c'> == string<'a','b','c'>));
	BOOST_CHECK( (string<'a','b','c','d'> == string<'a','b','c','d'>));

	BOOST_CHECK(!(string<'a'> == string<'a','b'>));
	BOOST_CHECK(!(string<'a','b'> == string<'a'>));
	BOOST_CHECK(!(string<'a'> == string<'b','a'>));
	BOOST_CHECK(!(string<'b','a'> == string<'a'>));

	BOOST_CHECK(!(string<'A','B'> == string<'a','b'>));
}

BOOST_AUTO_TEST_CASE(dazzle_string_ne)
{
	using namespace dazzle;

	BOOST_CHECK(!(empty_string != string<>));
	BOOST_CHECK(!(empty_string != basic_string<char>));
	BOOST_CHECK(!(empty_string != empty_string));
	BOOST_CHECK( (empty_string != string<'a'>));
	BOOST_CHECK( (empty_string != string<'a','b'>));
	BOOST_CHECK( (empty_string != string<'a','b','c'>));
	BOOST_CHECK( (empty_string != string<'a','b','c','d'>));

	BOOST_CHECK(!(string<'a'> != string<'a'>));
	BOOST_CHECK( (string<'a'> != string<'b'>));
	BOOST_CHECK( (string<'b'> != string<'a'>));

	BOOST_CHECK(!(string<'a','b'> != string<'a','b'>));
	BOOST_CHECK(!(string<'a','b','c'> != string<'a','b','c'>));
	BOOST_CHECK(!(string<'a','b','c','d'> != string<'a','b','c','d'>));

	BOOST_CHECK( (string<'a'> != string<'a','b'>));
	BOOST_CHECK( (string<'a','b'> != string<'a'>));
	BOOST_CHECK( (string<'a'> != string<'b','a'>));
	BOOST_CHECK( (string<'b','a'> != string<'a'>));

	BOOST_CHECK( (string<'A','B'> != string<'a','b'>));
}

BOOST_AUTO_TEST_SUITE_END()

