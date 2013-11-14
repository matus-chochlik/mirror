/**
 *  .file test/mire/ct/position.cpp
 *  .brief Test case for compile-time position meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_position
#include <boost/test/unit_test.hpp>

#include <mire/ct/position.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/traits.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_position)

BOOST_AUTO_TEST_CASE(mire_ct_position_range)
{
	using namespace mire::ct;

	BOOST_CHECK((is_nil_t<
		position<range<>, range<>>
	>::value));

	BOOST_CHECK((is_nil_t<
		position<range<>, range<long>>
	>::value));

	BOOST_CHECK((is_nil_t<
		position<range<int>, range<double>>
	>::value));

	BOOST_CHECK((position<
		range<int>,
		range<int>
	>::value == 0));

	BOOST_CHECK((position<
		range<int, char, double, float>,
		range<int, char>
	>::value == 0));

	BOOST_CHECK((position<
		range<int, char, double, float>,
		range<char>
	>::value == 1));

	BOOST_CHECK((position<
		range<int, char, double, float>,
		range<double, float>
	>::value == 2));

	BOOST_CHECK((position<
		range<int, char, double, float, bool, short>,
		range<float, bool, short>
	>::value == 3));

	BOOST_CHECK((position<
		range<int, char, double, float, bool, short>,
		range<bool, short>
	>::value == 4));

	BOOST_CHECK((position<
		range<int, char, double, float, bool, short>,
		range<short>
	>::value == 5));
}

BOOST_AUTO_TEST_CASE(mire_ct_position_string)
{
	using namespace mire::ct;


	BOOST_CHECK((is_nil_t<
		position<string<>, string<>>
	>::value));

	BOOST_CHECK((is_nil_t<
		position<string<>, string<'A'>>
	>::value));

	BOOST_CHECK((is_nil_t<
		position<string<'X'>, string<'A'>>
	>::value));

	BOOST_CHECK((position<
		string<'A'>,
		string<'A'>
	>::value == 0));

	BOOST_CHECK((position<
		string<'A', 'B', 'C', 'D', 'E', 'F'>,
		string<'A'>
	>::value == 0));

	BOOST_CHECK((position<
		string<'A', 'B', 'C', 'D', 'E', 'F'>,
		string<'A', 'B', 'C', 'D', 'E', 'F'>
	>::value == 0));

	BOOST_CHECK((position<
		string<'A', 'B', 'C', 'D', 'E', 'F'>,
		string<'B', 'C'>
	>::value == 1));

	BOOST_CHECK((position<
		string<'A', 'B', 'C', 'D', 'E', 'F'>,
		string<'C'>
	>::value == 2));

	BOOST_CHECK((position<
		string<'A', 'B', 'C', 'D', 'E', 'F'>,
		string<'D', 'E', 'F'>
	>::value == 3));

	BOOST_CHECK((position<
		string<'A', 'B', 'C', 'D', 'E', 'F'>,
		string<'E', 'F'>
	>::value == 4));

	BOOST_CHECK((position<
		string<'A', 'B', 'C', 'D', 'E', 'F'>,
		string<'F'>
	>::value == 5));
}

BOOST_AUTO_TEST_SUITE_END()

