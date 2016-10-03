/**
 *  .file test/mirror/minus_r.cpp
 *  .brief Test case for compile-time minus operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_minus
#include <boost/test/unit_test.hpp>

#include <mirror/minus.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_minus)

BOOST_AUTO_TEST_CASE(mirror_minus_1)
{
	using namespace mirror;

	BOOST_CHECK_EQUAL((value<minus<int_<3>, int_<2>>>), value<int_<1>>);
	BOOST_CHECK_EQUAL((value<minus<int_<12>, int_<34>>>), value<int_<-22>>);

	BOOST_CHECK_EQUAL(
		(value<minus<minus<int_<10>, int_<5>>, minus<int_<4>, int_<3>>>>),
		(value<minus<int_<6>, int_<2>>>)
	);
}

BOOST_AUTO_TEST_SUITE_END()

