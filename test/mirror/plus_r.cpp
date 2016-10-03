/**
 *  .file test/mirror/plus_r.cpp
 *  .brief Test case for compile-time plus operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_plus
#include <boost/test/unit_test.hpp>

#include <mirror/plus.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_plus)

BOOST_AUTO_TEST_CASE(mirror_plus_1)
{
	using namespace mirror;

	BOOST_CHECK_EQUAL((value<plus<int_<1>, int_<2>>>), value<int_<3>>);
	BOOST_CHECK_EQUAL((value<plus<int_<12>, int_<34>>>), value<int_<46>>);

	BOOST_CHECK_EQUAL(
		(value<plus<plus<int_<1>, int_<2>>, plus<int_<3>, int_<4>>>>),
		(value<plus<int_<5>, int_<5>>>)
	);
}

BOOST_AUTO_TEST_SUITE_END()

