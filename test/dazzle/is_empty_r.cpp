/**
 *  .file test/dazzle/is_empty_r.cpp
 *  .brief Test case for compile-time is_empty operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_is_empty
#include <boost/test/unit_test.hpp>

#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>
#include <dazzle/none.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_is_empty)

BOOST_AUTO_TEST_CASE(dazzle_is_empty_none)
{
	using namespace dazzle;

	BOOST_CHECK(( none.is_empty()));
}

BOOST_AUTO_TEST_CASE(dazzle_is_empty_range)
{
	using namespace dazzle;

	BOOST_CHECK(( empty_range.is_empty()));
	BOOST_CHECK((!range<long>.is_empty()));
	BOOST_CHECK((!range<int, long, float>.is_empty()));
}

BOOST_AUTO_TEST_CASE(dazzle_is_empty_string)
{
	using namespace dazzle;

	BOOST_CHECK(( empty_string.is_empty()));
	BOOST_CHECK((!string<'x'>.is_empty()));
	BOOST_CHECK((!string<'s','t','r'>.is_empty()));
	BOOST_CHECK((!basic_string<wchar_t,L'a',L'b'>.is_empty()));
}

BOOST_AUTO_TEST_SUITE_END()

