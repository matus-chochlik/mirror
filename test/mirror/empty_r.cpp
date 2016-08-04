/**
 *  .file test/mirror/empty_r.cpp
 *  .brief Test case for compile-time empty meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_empty
#include <boost/test/unit_test.hpp>

#include <mire/ct/empty.hpp>

BOOST_AUTO_TEST_SUITE(mirror_empty)

BOOST_AUTO_TEST_CASE(mirror_empty_optional)
{
	using namespace mirror;

	BOOST_CHECK(( empty<empty_optional>()));
	BOOST_CHECK((!empty<optional<long>>()));
}

BOOST_AUTO_TEST_CASE(mirror_empty_range)
{
	using namespace mirror;

	BOOST_CHECK(( empty<empty_range>()));
	BOOST_CHECK((!empty<range<long>>()));
	BOOST_CHECK((!empty<range<int, long, float>>()));
}

BOOST_AUTO_TEST_CASE(mirror_empty_string)
{
	using namespace mirror;

	BOOST_CHECK(( empty<empty_string>()));
	BOOST_CHECK((!empty<string<'x'>>()));
	BOOST_CHECK((!empty<string<'s','t','r'>>()));
	BOOST_CHECK((!empty<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>()));
}

BOOST_AUTO_TEST_SUITE_END()

