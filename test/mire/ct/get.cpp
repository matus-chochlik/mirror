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

BOOST_AUTO_TEST_CASE(mire_ct_get_optional)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		get<optional<long>>,
		long
	>::value));

	BOOST_CHECK((!equal_types<
		get<optional<int>>,
		long
	>::value));

	BOOST_CHECK((equal_types<
		get<optional<int>>,
		int
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

