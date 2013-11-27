/**
 *  .file test/mire/ct/find.cpp
 *  .brief Test case for compile-time find meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_find
#include <boost/test/unit_test.hpp>

#include <mire/ct/find.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_find)

BOOST_AUTO_TEST_CASE(mire_ct_find_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		find<range<>, range<>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		find<range<bool, char, short>, range<int, long>>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		find<range<bool, char, short, int>, range<bool, char, short, int>>,
		range<bool, char, short, int>
	>::value));

	BOOST_CHECK((equal<
		find<range<bool, char, short, int, long, bool>, range<bool>>,
		range<bool, char, short, int, long, bool>
	>::value));

	BOOST_CHECK((equal<
		find<range<bool, char, short, int, long, bool>, range<bool, char>>,
		range<bool, char, short, int, long, bool>
	>::value));

	BOOST_CHECK((equal<
		find<range<bool, char, short, int, long>, range<char, short>>,
		range<char, short, int, long>
	>::value));

	BOOST_CHECK((equal<
		find<range<bool, char, short, int, long>, range<int, long>>,
		range<int, long>
	>::value));

	BOOST_CHECK((equal<
		find<range<bool, char, short, int, long>, range<long>>,
		range<long>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_find_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		find<string<>, string<>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		find<string<'a','b','c'>, string<'x','y'>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		find<string<'s','t','r','i','n','g','s'>, string<'s'>>,
		string<'s','t','r','i','n','g','s'>
	>::value));

	BOOST_CHECK((equal<
		find<string<'s','t','r','i','n','g','s'>, string<'t','r','i'>>,
		string<'t','r','i','n','g','s'>
	>::value));

	BOOST_CHECK((equal<
		find<string<'s','t','r','i','n','g','s'>, string<'i','n','g'>>,
		string<'i','n','g','s'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

