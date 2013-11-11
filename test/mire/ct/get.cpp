/**
 *  .file test/mire/ct/get.cpp
 *  .brief Test case for compile-time get meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_get
#include <boost/test/unit_test.hpp>

#include <mire/ct/get.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_get)

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_get_optional)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal_types<
		get<optional<long>>,
		long
	>, true>();

	mire_ct_test_bool<equal_types<
		get<optional<int>>,
		long
	>,false>();

	mire_ct_test_bool<equal_types<
		get<optional<int>>,
		int
	>, true>();
}

BOOST_AUTO_TEST_SUITE_END()

