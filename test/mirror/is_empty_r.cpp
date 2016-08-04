/**
 *  .file test/mirror/is_empty_r.cpp
 *  .brief Test case for compile-time is_empty meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_is_empty
#include <boost/test/unit_test.hpp>

#include <mirror/is_empty.hpp>

BOOST_AUTO_TEST_SUITE(mirror_is_empty)

BOOST_AUTO_TEST_CASE(mirror_is_empty_optional)
{
	using namespace mirror;

	BOOST_CHECK(( is_empty<empty_optional>::value));
	BOOST_CHECK((!is_empty<optional<long>>::value));
}

BOOST_AUTO_TEST_CASE(mirror_is_empty_range)
{
	using namespace mirror;

	BOOST_CHECK(( is_empty<empty_range>::value));
	BOOST_CHECK((!is_empty<range<long>>::value));
	BOOST_CHECK((!is_empty<range<int, long, float>>::value));
}

BOOST_AUTO_TEST_CASE(mirror_is_empty_string)
{
	using namespace mirror;

	BOOST_CHECK(( is_empty<empty_string>::value));
	BOOST_CHECK((!is_empty<string<'x'>>::value));
	BOOST_CHECK((!is_empty<string<'s','t','r'>>::value));
	BOOST_CHECK((!is_empty<basic_string<wchar_t,L'a',L'b'>>::value));
}

BOOST_AUTO_TEST_SUITE_END()

