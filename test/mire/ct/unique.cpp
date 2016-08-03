/**
 *  .file test/mire/ct/unique.cpp
 *  .brief Test case for compile-time unique meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_unique
#include <boost/test/unit_test.hpp>

#include <mire/ct/unique.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_unique)

BOOST_AUTO_TEST_CASE(mire_ct_unique_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		unique<range<>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		unique<range<bool, char, int, float, double>>,
		range<bool, char, int, float, double>
	>::value));

	BOOST_CHECK((equal<
		unique<range<bool, char, bool, int, int, int, float, double, float>>,
		range<bool, char, int, float, double>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_unique_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		unique<string<>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		unique<string<'s','t','r','i','n','g'>>,
		string<'s','t','r','i','n','g'>
	>::value));

	BOOST_CHECK((equal<
		unique<string<'s','t','s','r','i','i','i','n','i','g','n'>>,
		string<'s','t','r','i','n','g'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

