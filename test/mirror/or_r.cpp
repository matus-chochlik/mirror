/**
 *  .file test/mirror/or_r.cpp
 *  .brief Test case for compile-time or operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_or
#include <boost/test/unit_test.hpp>

#include <mirror/or.hpp>
#include <mirror/value.hpp>

BOOST_AUTO_TEST_SUITE(mirror_or)

BOOST_AUTO_TEST_CASE(mirror_or_1)
{
	using namespace mirror;

	using t = true_;
	using f = false_;

	BOOST_CHECK((!value<or_<f>>));
	BOOST_CHECK(( value<or_<t>>));

	BOOST_CHECK((!value<or_<f, f>>));
	BOOST_CHECK(( value<or_<f, t>>));
	BOOST_CHECK(( value<or_<t, f>>));
	BOOST_CHECK(( value<or_<t, t>>));

	BOOST_CHECK((!value<or_<f, f, f>>));
	BOOST_CHECK(( value<or_<f, f, t>>));
	BOOST_CHECK(( value<or_<f, t, f>>));
	BOOST_CHECK(( value<or_<f, t, t>>));
	BOOST_CHECK(( value<or_<t, f, f>>));
	BOOST_CHECK(( value<or_<t, f, t>>));
	BOOST_CHECK(( value<or_<t, t, f>>));
	BOOST_CHECK(( value<or_<t, t, t>>));

	BOOST_CHECK((!value<or_<f, f, f, f>>));
	BOOST_CHECK(( value<or_<f, f, f, t>>));
	BOOST_CHECK(( value<or_<f, f, t, f>>));
	BOOST_CHECK(( value<or_<f, f, t, t>>));
	BOOST_CHECK(( value<or_<f, t, f, f>>));
	BOOST_CHECK(( value<or_<f, t, f, t>>));
	BOOST_CHECK(( value<or_<f, t, t, f>>));
	BOOST_CHECK(( value<or_<f, t, t, t>>));
	BOOST_CHECK(( value<or_<t, f, f, f>>));
	BOOST_CHECK(( value<or_<t, f, f, t>>));
	BOOST_CHECK(( value<or_<t, f, t, f>>));
	BOOST_CHECK(( value<or_<t, f, t, t>>));
	BOOST_CHECK(( value<or_<t, t, f, f>>));
	BOOST_CHECK(( value<or_<t, t, f, t>>));
	BOOST_CHECK(( value<or_<t, t, t, f>>));
	BOOST_CHECK(( value<or_<t, t, t, t>>));
}

BOOST_AUTO_TEST_CASE(mirror_or_2)
{
	using namespace mirror;

	using t = true_;
	using f = false_;
	using n = none;

	BOOST_CHECK(( value<or_<t, n>>));
	BOOST_CHECK(( value<or_<t, f, n>>));
	BOOST_CHECK(( value<or_<f, t, n>>));
}

BOOST_AUTO_TEST_SUITE_END()

