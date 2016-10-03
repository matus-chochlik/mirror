/**
 *  .file test/mirror/string_ops.cpp
 *  .brief Test case for compile-time string operations
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_string_ops
#include <boost/test/unit_test.hpp>

#include <mirror/string_ops.hpp>
#include <reflexpr>

BOOST_AUTO_TEST_SUITE(mirror_string_ops)

BOOST_AUTO_TEST_CASE(mirror_string_equal)
{
	using namespace mirror;

	empty_string e;
	string<'a'> a;
	string<'a','b'> ab;
	string<'a','b','c','d'> abcd;
	string<'a','b','c','d','e'> abcde;

	BOOST_CHECK( bool(e == e));
	BOOST_CHECK(!bool(e == a));
	BOOST_CHECK(!bool(a == e));
	BOOST_CHECK( bool(a == a));
	BOOST_CHECK(!bool(ab == abcd));
	BOOST_CHECK( bool(abcd == abcd));
	BOOST_CHECK(!bool(abcde == abcd));
	BOOST_CHECK( bool(abcde == abcde));
}

BOOST_AUTO_TEST_CASE(mirror_string_not_equal)
{
	using namespace mirror;

	empty_string e;
	string<'a'> a;
	string<'a','b'> ab;
	string<'a','b','c','d'> abcd;
	string<'a','b','c','d','e'> abcde;

	BOOST_CHECK(!bool(e != e));
	BOOST_CHECK( bool(e != a));
	BOOST_CHECK( bool(a != e));
	BOOST_CHECK(!bool(a != a));
	BOOST_CHECK( bool(ab != abcd));
	BOOST_CHECK(!bool(abcd != abcd));
	BOOST_CHECK( bool(abcde != abcd));
	BOOST_CHECK(!bool(abcde != abcde));
}

BOOST_AUTO_TEST_CASE(mirror_string_plus)
{
	using namespace mirror;

	empty_string e;
	string<'a'> a;
	string<'b'> b;
	string<'a','b'> ab;
	string<'c','d','e'> cde;
	string<'a','b','c','d','e'> abcde;

	BOOST_CHECK( bool(e+e == e));
	BOOST_CHECK( bool(a+e == a));
	BOOST_CHECK( bool(e+a == a));
	BOOST_CHECK( bool(a+b == ab));
	BOOST_CHECK( bool(b+a != ab));
	BOOST_CHECK( bool(e+a+b == ab));
	BOOST_CHECK( bool(a+e+b == ab));
	BOOST_CHECK( bool(a+b+e == ab));
	BOOST_CHECK( bool(ab+cde == abcde));
	BOOST_CHECK( bool(a+b+cde == ab + cde));
	BOOST_CHECK( bool(e+ab+e+cde+e == abcde));
	BOOST_CHECK( bool(cde+ab != abcde));
}

BOOST_AUTO_TEST_SUITE_END()

