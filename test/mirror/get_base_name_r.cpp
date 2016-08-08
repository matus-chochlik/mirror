/**
 *  .file test/mirror/get_base_name_r.cpp
 *  .brief Test case for compile-time get_base_name operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_concat
#include <boost/test/unit_test.hpp>

#include <mirror/get_base_name.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>

BOOST_AUTO_TEST_SUITE(mirror_get_base_name)

BOOST_AUTO_TEST_CASE(mirror_get_base_name)
{
	using namespace mirror;

	BOOST_CHECK(( value<equal<
		get_base_name<MIRRORED(int)>,
		string<'i','n','t'>
	>>));

	BOOST_CHECK(( value<equal<
		get_base_name<MIRRORED(double)>,
		string<'d','o','u','b','l','e'>
	>>));
	// TODO
}

BOOST_AUTO_TEST_SUITE_END()

