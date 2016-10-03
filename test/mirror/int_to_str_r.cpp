/**
 *  .file test/mirror/int_to_dec_str_r.cpp
 *  .brief Test case for compile-time int_to_dec_str operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_int_to_dec_str
#include <boost/test/unit_test.hpp>

#include <mirror/int_to_str.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_equal)

BOOST_AUTO_TEST_CASE(mirror_uint_to_dec_str)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<
		uint_to_dec_str<0>,
		string<'0'>
	>>));

	BOOST_CHECK(( value<equal<
		uint_to_dec_str<1>,
		string<'1'>
	>>));

	BOOST_CHECK(( value<equal<
		uint_to_dec_str<9>,
		string<'9'>
	>>));

	BOOST_CHECK(( value<equal<
		uint_to_dec_str<1234>,
		string<'1','2','3','4'>
	>>));

	BOOST_CHECK(( value<equal<
		uint_to_dec_str<1234567890>,
		string<'1','2','3','4','5','6','7','8','9','0'>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_int_to_dec_str)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<
		int_to_dec_str<0>,
		string<'0'>
	>>));

	BOOST_CHECK(( value<equal<
		int_to_dec_str<1>,
		string<'1'>
	>>));

	BOOST_CHECK(( value<equal<
		int_to_dec_str<-1>,
		string<'-','1'>
	>>));

	BOOST_CHECK(( value<equal<
		int_to_dec_str<9>,
		string<'9'>
	>>));

	BOOST_CHECK(( value<equal<
		int_to_dec_str<1234567890>,
		string<'1','2','3','4','5','6','7','8','9','0'>
	>>));

	BOOST_CHECK(( value<equal<
		int_to_dec_str<-1234567890>,
		string<'-','1','2','3','4','5','6','7','8','9','0'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

