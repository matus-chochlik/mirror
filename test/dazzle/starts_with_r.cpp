/**
 *  .file test/dazzle/starts_with_r.cpp
 *  .brief Test case for compile-time starts_with operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_starts_with
#include <boost/test/unit_test.hpp>

#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_starts_with)

BOOST_AUTO_TEST_CASE(dazzle_starts_with_range)
{
	using namespace dazzle;

	auto er = empty_range;
	auto r1 = range<int>;
	auto r2 = range<int, long>;
	auto r3 = range<int, long, char>;

	BOOST_CHECK(( r3.starts_with(er)));
	BOOST_CHECK(( r2.starts_with(er)));
	BOOST_CHECK(( r1.starts_with(er)));
	BOOST_CHECK(( er.starts_with(er)));
	BOOST_CHECK(( r3.starts_with(r1)));
	BOOST_CHECK(( r2.starts_with(r1)));
	BOOST_CHECK(( r1.starts_with(r1)));
	BOOST_CHECK((!er.starts_with(r1)));
	BOOST_CHECK(( r3.starts_with(r2)));
	BOOST_CHECK(( r2.starts_with(r2)));
	BOOST_CHECK((!r1.starts_with(r2)));
	BOOST_CHECK((!er.starts_with(r2)));
	BOOST_CHECK(( r3.starts_with(r3)));
	BOOST_CHECK((!r2.starts_with(r3)));
	BOOST_CHECK((!r1.starts_with(r3)));
	BOOST_CHECK((!er.starts_with(r3)));
}

BOOST_AUTO_TEST_CASE(dazzle_starts_with_string)
{
	using namespace dazzle;

	auto e = empty_string;
	auto a = string<'a'>;
	auto ab = string<'a','b'>;
	auto abc = string<'a','b','c'>;

	BOOST_CHECK(( abc.starts_with(  e)));
	BOOST_CHECK((  ab.starts_with(  e)));
	BOOST_CHECK((   a.starts_with(  e)));
	BOOST_CHECK((   e.starts_with(  e)));
	BOOST_CHECK(( abc.starts_with(  a)));
	BOOST_CHECK((  ab.starts_with(  a)));
	BOOST_CHECK((   a.starts_with(  a)));
	BOOST_CHECK((!  e.starts_with(  a)));
	BOOST_CHECK(( abc.starts_with( ab)));
	BOOST_CHECK((  ab.starts_with( ab)));
	BOOST_CHECK((!  a.starts_with( ab)));
	BOOST_CHECK((!  e.starts_with( ab)));
	BOOST_CHECK(( abc.starts_with(abc)));
	BOOST_CHECK((! ab.starts_with(abc)));
	BOOST_CHECK((!  a.starts_with(abc)));
	BOOST_CHECK((!  e.starts_with(abc)));
}

BOOST_AUTO_TEST_SUITE_END()

