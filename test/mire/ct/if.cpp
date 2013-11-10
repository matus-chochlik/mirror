/**
 *  .file test/mire/ct/if.cpp
 *  .brief Test case for compile-time if_ meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_if
#include <boost/test/unit_test.hpp>

#include <mire/ct/if.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_if)

BOOST_AUTO_TEST_CASE(mire_ct_if1)
{
	using namespace mire::ct;

	BOOST_CHECK((is_same<
		if_<true_type, char, double>::type,
		char
	>::value));

	BOOST_CHECK((is_same<
		if_<false_type, char, double>::type,
		double
	>::value));

	BOOST_CHECK((is_same<
		if_<true_type, double, char>::type,
		double
	>::value));

	BOOST_CHECK((is_same<
		if_<false_type, double, char>::type,
		char
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_if_c1)
{
	using namespace mire::ct;

	BOOST_CHECK((is_same<
		if_c<true, char, double>::type,
		char
	>::value));

	BOOST_CHECK((is_same<
		if_c<false, char, double>::type,
		double
	>::value));

	BOOST_CHECK((is_same<
		if_c<true, double, char>::type,
		double
	>::value));

	BOOST_CHECK((is_same<
		if_c<false, double, char>::type,
		char
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

