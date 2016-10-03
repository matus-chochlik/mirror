/**
 *  .file test/mirror/get_front_r.cpp
 *  .brief Test case for compile-time get_front operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_get_front
#include <boost/test/unit_test.hpp>

#include <mirror/get_front.hpp>
#include <mirror/int_const.hpp>
#include <mirror/value.hpp>
#include <type_traits>

BOOST_AUTO_TEST_SUITE(mirror_get_front)

BOOST_AUTO_TEST_CASE(mirror_get_front_range)
{
	using namespace mirror;

	BOOST_CHECK((value<std::is_same<
		get_front<empty_range>,
		none
	>>));
	BOOST_CHECK((value<std::is_same<
		get_front<range<long>>,
		long
	>>));
	BOOST_CHECK((value<std::is_same<
		get_front<range<char>>,
		char
	>>));
	BOOST_CHECK((value<std::is_same<
		get_front<range<int>>,
		int
	>>));
	BOOST_CHECK((value<std::is_same<
		get_front<range<int, double>>,
		int
	>>));
	BOOST_CHECK((value<std::is_same<
		get_front<range<int, int, int>>,
		int
	>>));
	BOOST_CHECK((value<std::is_same<
		get_front<range<double, float>>,
		double
	>>));
	BOOST_CHECK((value<std::is_same<
		get_front<range<char, int, bool>>,
		char
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_get_front_string)
{
	using namespace mirror;

	BOOST_CHECK_EQUAL('\0',
		(value<get_front<empty_string>>)
	);
	BOOST_CHECK_EQUAL('x',
		(value<get_front<string<'x'>>>)
	);
	BOOST_CHECK_EQUAL('y',
		(value<get_front<string<'y'>>>)
	);
	BOOST_CHECK_EQUAL('x',
		(value<get_front<string<'x','y','z'>>>)
	);
	BOOST_CHECK_EQUAL('a',
		(value<get_front<string<'a','b','c','d'>>>)
	);
	BOOST_CHECK_EQUAL(L'w',
		(value<get_front<basic_string<wchar_t,L'w'>>>)
	);
	BOOST_CHECK_EQUAL(L's',
		(value<get_front<basic_string<wchar_t,L's',L't',L'r'>>>)
	);
}

BOOST_AUTO_TEST_SUITE_END()

