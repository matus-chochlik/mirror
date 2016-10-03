/**
 *  .file test/mirror/not_r.cpp
 *  .brief Test case for compile-time not operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_not
#include <boost/test/unit_test.hpp>

#include <mirror/not.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_or)

BOOST_AUTO_TEST_CASE(mirror_or_1)
{
	using namespace mirror;

	using t = true_;
	using f = false_;

	BOOST_CHECK(( value<not_<f>>));
	BOOST_CHECK((!value<not_<t>>));
}

BOOST_AUTO_TEST_SUITE_END()

