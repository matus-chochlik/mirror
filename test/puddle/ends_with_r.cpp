/**
 *  .file test/puddle/ends_with_r.cpp
 *  .brief Test case for compile-time ends_with operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_ends_with
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>

BOOST_AUTO_TEST_SUITE(puddle_ends_with)

BOOST_AUTO_TEST_CASE(puddle_ends_with_range)
{
	using namespace puddle;

	auto er = empty_range;
	auto r1 = range<char>;
	auto r2 = range<long, char>;
	auto r3 = range<int, long, char>;

	BOOST_CHECK(( value(ends_with(r3, er))));
	BOOST_CHECK(( value(ends_with(r2, er))));
	BOOST_CHECK(( value(ends_with(r1, er))));
	BOOST_CHECK(( value(ends_with(er, er))));
	BOOST_CHECK(( value(ends_with(r3, r1))));
	BOOST_CHECK(( value(ends_with(r2, r1))));
	BOOST_CHECK(( value(ends_with(r1, r1))));
	BOOST_CHECK((!value(ends_with(er, r1))));
	BOOST_CHECK(( value(ends_with(r3, r2))));
	BOOST_CHECK(( value(ends_with(r2, r2))));
	BOOST_CHECK((!value(ends_with(r1, r2))));
	BOOST_CHECK((!value(ends_with(er, r2))));
	BOOST_CHECK(( value(ends_with(r3, r3))));
	BOOST_CHECK((!value(ends_with(r2, r3))));
	BOOST_CHECK((!value(ends_with(r1, r3))));
	BOOST_CHECK((!value(ends_with(er, r3))));
}

BOOST_AUTO_TEST_CASE(puddle_ends_with_string)
{
	using namespace puddle;

	auto e = empty_string;
	auto c = string<'c'>;
	auto bc = string<'b','c'>;
	auto abc = string<'a','b','c'>;

	BOOST_CHECK(( value(ends_with(abc,   e))));
	BOOST_CHECK(( value(ends_with( bc,   e))));
	BOOST_CHECK(( value(ends_with(  c,   e))));
	BOOST_CHECK(( value(ends_with(  e,   e))));
	BOOST_CHECK(( value(ends_with(abc,   c))));
	BOOST_CHECK(( value(ends_with( bc,   c))));
	BOOST_CHECK(( value(ends_with(  c,   c))));
	BOOST_CHECK((!value(ends_with(  e,   c))));
	BOOST_CHECK(( value(ends_with(abc,  bc))));
	BOOST_CHECK(( value(ends_with( bc,  bc))));
	BOOST_CHECK((!value(ends_with(  c,  bc))));
	BOOST_CHECK((!value(ends_with(  e,  bc))));
	BOOST_CHECK(( value(ends_with(abc, abc))));
	BOOST_CHECK((!value(ends_with( bc, abc))));
	BOOST_CHECK((!value(ends_with(  c, abc))));
	BOOST_CHECK((!value(ends_with(  e, abc))));
}

BOOST_AUTO_TEST_SUITE_END()

