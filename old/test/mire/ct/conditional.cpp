/**
 *  .file test/mire/ct/if.cpp
 *  .brief Test case for compile-time conditional meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013-2015 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_conditional
#include <boost/test/unit_test.hpp>

#include <mire/ct/conditional.hpp>
#include <mire/ct/compare.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_conditional)

BOOST_AUTO_TEST_CASE(mire_ct_conditional1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		conditional<true_type, char, double>,
		char
	>::value));

	BOOST_CHECK((equal_types<
		conditional<false_type, char, double>,
		double
	>::value));

	BOOST_CHECK((equal_types<
		conditional<true_type, double, char>,
		double
	>::value));

	BOOST_CHECK((equal_types<
		conditional<false_type, double, char>,
		char
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_conditional_c1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		conditional_c<true, char, double>,
		char
	>::value));

	BOOST_CHECK((equal_types<
		conditional_c<false, char, double>,
		double
	>::value));

	BOOST_CHECK((equal_types<
		conditional_c<true, double, char>,
		double
	>::value));

	BOOST_CHECK((equal_types<
		conditional_c<false, double, char>,
		char
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

