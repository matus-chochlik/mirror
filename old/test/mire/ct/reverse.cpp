/**
 *  .file test/mire/ct/reverse.cpp
 *  .brief Test case for compile-time reverse meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_reverse
#include <boost/test/unit_test.hpp>

#include <mire/ct/reverse.hpp>
#include <mire/ct/compare.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_reverse)

BOOST_AUTO_TEST_CASE(mire_ct_rev_range1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		reverse<range<>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		reverse<range<char, short, int, long, float, double>>,
		range<double, float, long, int, short, char>
	>::value));

	BOOST_CHECK((equal<
		reverse<reverse<range<char, short, int, long, float, double>>>,
		range<char, short, int, long, float, double>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_rev_string1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		reverse<string<>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		reverse<string<'A','B','C','D','E','F','G','H'>>,
		string<'H','G','F','E','D','C','B','A'>
	>::value));

	BOOST_CHECK((equal<
		reverse<reverse<string<'A','B','C','D','E','F','G','H'>>>,
		string<'A','B','C','D','E','F','G','H'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

