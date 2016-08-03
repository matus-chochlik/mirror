/**
 *  .file test/mire/ct/front.cpp
 *  .brief Test case for compile-time front meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_front
#include <boost/test/unit_test.hpp>

#include <mire/ct/front.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_front)

BOOST_AUTO_TEST_CASE(mire_ct_front_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		front<range<long>>,
		long
	>::value));

	BOOST_CHECK((!equal_types<
		front<range<char>>,
		bool
	>::value));

	BOOST_CHECK((equal_types<
		front<range<short, int, long>>,
		short
	>::value));

	BOOST_CHECK((!equal_types<
		front<range<short, int, long>>,
		int
	>::value));

	BOOST_CHECK((!equal_types<
		front<range<short, int, long>>,
		long
	>::value));

	BOOST_CHECK((!equal_types<
		front<range<bool, short, int, long, unsigned, float>>,
		char
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_front_string)
{
	using namespace mire::ct;

	BOOST_CHECK((front<empty_string>::value == '\0'));
	BOOST_CHECK((front<string<'A'>>::value  == 'A'));
	BOOST_CHECK((front<string<'A'>>::value  != '\0'));
	BOOST_CHECK((front<string<'B','C','D'>>::value != 'A'));
	BOOST_CHECK((front<string<'B','C','D'>>::value == 'B'));
	BOOST_CHECK((front<string<'B','C','D'>>::value != 'C'));
	BOOST_CHECK((front<string<'B','C','D'>>::value != 'D'));
}

BOOST_AUTO_TEST_SUITE_END()

