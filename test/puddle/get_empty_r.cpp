/**
 *  .file test/puddle/get_empty_r.cpp
 *  .brief Test case for compile-time get_empty operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_get_empty
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <puddle/none.hpp>

BOOST_AUTO_TEST_SUITE(puddle_get_empty)

BOOST_AUTO_TEST_CASE(puddle_get_empty_none)
{
	using namespace puddle;

	BOOST_CHECK(( value(is_empty(get_empty(none)))));
}

BOOST_AUTO_TEST_CASE(puddle_get_empty_range)
{
	using namespace puddle;

	BOOST_CHECK((value(is_empty(get_empty(empty_range)))));
	BOOST_CHECK((value(is_empty(get_empty(range<long>)))));
	BOOST_CHECK((value(is_empty(get_empty(range<int, long, float>)))));
}

BOOST_AUTO_TEST_CASE(puddle_get_empty_string)
{
	using namespace puddle;

	BOOST_CHECK((value(is_empty(get_empty(empty_string)))));
	BOOST_CHECK((value(is_empty(get_empty(string<'x'>)))));
	BOOST_CHECK((value(is_empty(get_empty(string<'s','t','r'>)))));
	BOOST_CHECK((value(is_empty(get_empty(basic_string<wchar_t,L'a'>)))));
}

BOOST_AUTO_TEST_SUITE_END()

