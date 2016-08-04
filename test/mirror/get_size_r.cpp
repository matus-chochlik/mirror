/**
 *  .file test/mirror/get_size_r.cpp
 *  .brief Test case for compile-time get_size meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_get_size
#include <boost/test/unit_test.hpp>

#include <mirror/get_size.hpp>

BOOST_AUTO_TEST_SUITE(mirror_get_size)

BOOST_AUTO_TEST_CASE(mirror_get_size_optional)
{
	using namespace mirror;

	BOOST_CHECK((get_size<empty_optional>::value == 0));
	BOOST_CHECK((get_size<optional<long>>::value == 1));
	BOOST_CHECK((get_size<optional<bool>>::value == 1));
	BOOST_CHECK((get_size<optional<char>>::value == 1));
}

BOOST_AUTO_TEST_CASE(mirror_get_size_range)
{
	using namespace mirror;

	BOOST_CHECK((get_size<empty_range>::value == 0));
	BOOST_CHECK((get_size<range<long>>::value == 1));
	BOOST_CHECK((get_size<range<short, int>>::value == 2));
	BOOST_CHECK((get_size<range<int, long, float>>::value == 3));
	BOOST_CHECK((get_size<range<long, float, double, bool>>::value == 4));
}

BOOST_AUTO_TEST_CASE(mirror_get_size_string)
{
	using namespace mirror;

	BOOST_CHECK((get_size<empty_string>::value == 0));
	BOOST_CHECK((get_size<string<'x'>>::value == 1));
	BOOST_CHECK((get_size<string<'x','y'>>::value == 2));
	BOOST_CHECK((get_size<string<'s','t','r'>>::value == 3));
	BOOST_CHECK((get_size<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>::value == 4));
}

BOOST_AUTO_TEST_SUITE_END()

