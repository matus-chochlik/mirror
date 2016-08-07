/**
 *  .file test/mirror/pop_front_r.cpp
 *  .brief Test case for compile-time pop_front operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_pop_front
#include <boost/test/unit_test.hpp>

#include <mirror/pop_front.hpp>
#include <mirror/equal.hpp>

BOOST_AUTO_TEST_SUITE(mirror_pop_front)

BOOST_AUTO_TEST_CASE(mirror_pop_front_range)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<pop_front<empty_range>, empty_range>>));
	BOOST_CHECK((value<equal<pop_front<range<double>>, empty_range>>));
	BOOST_CHECK((value<equal<pop_front<range<int, char>>, range<char>>>));
	BOOST_CHECK((value<equal<pop_front<range<long, char, bool>>, range<char, bool>>>));
}

BOOST_AUTO_TEST_CASE(mirror_pop_front_string)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<pop_front<empty_string>, empty_string>>));
	BOOST_CHECK((value<equal<pop_front<string<'x'>>, empty_string>>));
	BOOST_CHECK((value<equal<pop_front<string<'x','y'>>, string<'y'>>>));
	BOOST_CHECK((value<equal<pop_front<string<'x','y','z'>>, string<'y','z'>>>));
}

BOOST_AUTO_TEST_SUITE_END()

