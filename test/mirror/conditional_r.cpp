/**
 *  .file test/mirror/conditional.cpp
 *  .brief Test case for compile-time conditional operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_conditional
#include <boost/test/unit_test.hpp>

#include <mirror/conditional.hpp>
#include <mirror/value.hpp>
#include <type_traits>

BOOST_AUTO_TEST_SUITE(mirror_conditional)

BOOST_AUTO_TEST_CASE(mirror_conditional_1)
{
	using namespace mirror;

	BOOST_CHECK((value<std::is_same<
		conditional<true_, long, char>,
		long
	>>));

	BOOST_CHECK((value<std::is_same<
		conditional<false_, long, char>,
		char
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

