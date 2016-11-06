/**
 *  .file test/mirror/to_container_r.cpp
 *  .brief Test case for compile-time to_container operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_to_container
#include <boost/test/unit_test.hpp>

#include <mirror/to_container.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_to_container)

BOOST_AUTO_TEST_CASE(mirror_to_container_none_1)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<
		to_container<none>,
		none
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_to_container_range_1)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<
		to_container<identity<long>>,
		range<long>
	>>));

	BOOST_CHECK(( value<equal<
		to_container<empty_range>,
		empty_range
	>>));

	BOOST_CHECK(( value<equal<
		to_container<range<long>>,
		range<long>
	>>));

	BOOST_CHECK(( value<equal<
		to_container<range<int, bool, char>>,
		range<int, bool, char>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_to_container_string_1)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<
		to_container<int_const<wchar_t, L'x'>>,
		basic_string<wchar_t, L'x'>
	>>));

	BOOST_CHECK(( value<equal<
		to_container<char_<'a'>>,
		string<'a'>
	>>));

	BOOST_CHECK(( value<equal<
		to_container<string<'a'>>,
		string<'a'>
	>>));

	BOOST_CHECK(( value<equal<
		to_container<string<'a','b'>>,
		string<'a','b'>
	>>));

	BOOST_CHECK(( value<equal<
		to_container<string<'a','b','c'>>,
		string<'a','b','c'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

