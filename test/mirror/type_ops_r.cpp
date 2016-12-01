/**
 *  .file test/mirror/type_ops.cpp
 *  .brief Test case for compile-time type operations
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_type_ops
#include <boost/test/unit_test.hpp>

#include <mirror/type_ops.hpp>

BOOST_AUTO_TEST_SUITE(mirror_type_ops)

BOOST_AUTO_TEST_CASE(mirror_type_equal)
{
	using namespace mirror;

	identity<long> l;
	identity<int> i;
	identity<char> c;
	identity<short> s;

	BOOST_CHECK( bool(l == l));
	BOOST_CHECK(!bool(l == i));
	BOOST_CHECK(!bool(s == l));
	BOOST_CHECK( bool(i == i));
	BOOST_CHECK(!bool(i == l));
	BOOST_CHECK(!bool(c == i));
	BOOST_CHECK( bool(c == c));
	BOOST_CHECK( bool(s == s));
	BOOST_CHECK(!bool(c == s));
}

BOOST_AUTO_TEST_CASE(mirror_type_not_equal)
{
	using namespace mirror;

	identity<long> l;
	identity<int> i;
	identity<char> c;
	identity<short> s;

	BOOST_CHECK(!bool(l != l));
	BOOST_CHECK( bool(l != i));
	BOOST_CHECK( bool(s != l));
	BOOST_CHECK(!bool(i != i));
	BOOST_CHECK( bool(i != l));
	BOOST_CHECK( bool(c != i));
	BOOST_CHECK(!bool(c != c));
	BOOST_CHECK(!bool(s != s));
	BOOST_CHECK( bool(c != s));
}

BOOST_AUTO_TEST_SUITE_END()

