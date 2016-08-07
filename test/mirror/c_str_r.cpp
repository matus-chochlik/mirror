/**
 *  .file test/mirror/c_str_r.cpp
 *  .brief Test case for compile-time c_str operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_c_str
#include <boost/test/unit_test.hpp>

#include <mirror/c_str.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mirror_concat)

BOOST_AUTO_TEST_CASE(mirror_string_c_str)
{
	using namespace mirror;

	using e = empty_string;
	using a = string<'a'>;
	using ab = string<'a','b'>;
	using abcd = string<'a','b','c','d'>;

	using std::strcmp;

	BOOST_CHECK_EQUAL(strcmp(c_str<e>, ""), 0);
	BOOST_CHECK_EQUAL(strcmp(c_str<a>, "a"), 0);
	BOOST_CHECK_EQUAL(strcmp(c_str<ab>, "ab"), 0);
	BOOST_CHECK_EQUAL(strcmp(c_str<abcd>, "abcd"), 0);
}

BOOST_AUTO_TEST_SUITE_END()

