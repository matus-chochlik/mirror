/**
 *  .file test/dazzle/ends_with_r.cpp
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
#define BOOST_TEST_MODULE DAZZLE_ends_with
#include <boost/test/unit_test.hpp>

#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_ends_with)

BOOST_AUTO_TEST_CASE(dazzle_ends_with_range)
{
	using namespace dazzle;

	auto er = empty_range;
	auto r1 = range<char>;
	auto r2 = range<long, char>;
	auto r3 = range<int, long, char>;

	BOOST_CHECK(( r3.ends_with(er)));
	BOOST_CHECK(( r2.ends_with(er)));
	BOOST_CHECK(( r1.ends_with(er)));
	BOOST_CHECK(( er.ends_with(er)));
	BOOST_CHECK(( r3.ends_with(r1)));
	BOOST_CHECK(( r2.ends_with(r1)));
	BOOST_CHECK(( r1.ends_with(r1)));
	BOOST_CHECK((!er.ends_with(r1)));
	BOOST_CHECK(( r3.ends_with(r2)));
	BOOST_CHECK(( r2.ends_with(r2)));
	BOOST_CHECK((!r1.ends_with(r2)));
	BOOST_CHECK((!er.ends_with(r2)));
	BOOST_CHECK(( r3.ends_with(r3)));
	BOOST_CHECK((!r2.ends_with(r3)));
	BOOST_CHECK((!r1.ends_with(r3)));
	BOOST_CHECK((!er.ends_with(r3)));
}

BOOST_AUTO_TEST_CASE(dazzle_ends_with_string)
{
	using namespace dazzle;

	auto e = empty_string;
	auto c = string<'c'>;
	auto bc = string<'b','c'>;
	auto abc = string<'a','b','c'>;

	BOOST_CHECK(( abc.ends_with(  e)));
	BOOST_CHECK((  bc.ends_with(  e)));
	BOOST_CHECK((   c.ends_with(  e)));
	BOOST_CHECK((   e.ends_with(  e)));
	BOOST_CHECK(( abc.ends_with(  c)));
	BOOST_CHECK((  bc.ends_with(  c)));
	BOOST_CHECK((   c.ends_with(  c)));
	BOOST_CHECK((!  e.ends_with(  c)));
	BOOST_CHECK(( abc.ends_with( bc)));
	BOOST_CHECK((  bc.ends_with( bc)));
	BOOST_CHECK((!  c.ends_with( bc)));
	BOOST_CHECK((!  e.ends_with( bc)));
	BOOST_CHECK(( abc.ends_with(abc)));
	BOOST_CHECK((! bc.ends_with(abc)));
	BOOST_CHECK((!  c.ends_with(abc)));
	BOOST_CHECK((!  e.ends_with(abc)));
}

BOOST_AUTO_TEST_SUITE_END()

