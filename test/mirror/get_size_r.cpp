/**
 *  .file test/mirror/get_size_r.cpp
 *  .brief Test case for compile-time get_size operation
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

	BOOST_CHECK((value<get_size<empty_optional>> == 0));
	BOOST_CHECK((value<get_size<optional<long>>> == 1));
	BOOST_CHECK((value<get_size<optional<bool>>> == 1));
	BOOST_CHECK((value<get_size<optional<char>>> == 1));
}

BOOST_AUTO_TEST_CASE(mirror_get_size_range)
{
	using namespace mirror;

	BOOST_CHECK((value<get_size<empty_range>> == 0));
	BOOST_CHECK((value<get_size<range<long>>> == 1));
	BOOST_CHECK((value<get_size<range<short, int>>> == 2));
	BOOST_CHECK((value<get_size<range<int, long, float>>> == 3));
	BOOST_CHECK((value<get_size<range<long, float, double, bool>>> == 4));
}

BOOST_AUTO_TEST_CASE(mirror_get_size_string)
{
	using namespace mirror;

	BOOST_CHECK((value<get_size<empty_string>> == 0));
	BOOST_CHECK((value<get_size<string<'x'>>> == 1));
	BOOST_CHECK((value<get_size<string<'x','y'>>> == 2));
	BOOST_CHECK((value<get_size<basic_string<wchar_t,L's',L't',L'r'>>> == 3));
	BOOST_CHECK((value<get_size<string<'a','b','c','d'>>> == 4));
}

BOOST_AUTO_TEST_SUITE_END()

