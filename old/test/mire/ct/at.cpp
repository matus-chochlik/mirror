/**
 *  .file test/mire/ct/at.cpp
 *  .brief Test case for compile-time at meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_at
#include <boost/test/unit_test.hpp>

#include <mire/ct/at.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_at)

BOOST_AUTO_TEST_CASE(mire_ct_at_range)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, zero>,
		bool
	>::value == true));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, zero>,
		short
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, one>,
		short
	>::value == true));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, one>,
		bool
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, one>,
		int
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, two>,
		int
	>::value == true));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, two>,
		short
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, two>,
		long
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, three>,
		long
	>::value == true));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, three>,
		int
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, three>,
		unsigned
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, four>,
		unsigned
	>::value == true));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, four>,
		long
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, four>,
		float
	>::value == false));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, five>,
		float
	>::value == true));

	BOOST_CHECK((equal_types<
		at<range<bool, short, int, long, unsigned, float>, five>,
		unsigned
	>::value == false));
}

BOOST_AUTO_TEST_CASE(mire_ct_at_string)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, zero>::value == 's'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, zero>::value != 't'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, one>::value  == 't'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, one>::value  != 's'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, one>::value  != 'r'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, two>::value  == 'r'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, two>::value  != 't'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, two>::value  != 'i'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, three>::value== 'i'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, three>::value!= 'r'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, three>::value!= 'n'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, four>::value == 'n'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, four>::value != 'i'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, four>::value != 'g'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, five>::value == 'g'));
	BOOST_CHECK((at<string<'s','t','r','i','n','g'>, five>::value != 'n'));
}

BOOST_AUTO_TEST_SUITE_END()

