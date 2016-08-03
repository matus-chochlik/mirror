/**
 *  .file test/mire/ct/int_to_str.cpp
 *  .brief Test case for compile-time int-to-string meta-functions
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_int_to_str
#include <boost/test/unit_test.hpp>

#include <mire/ct/int_to_str.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_int_to_str)

BOOST_AUTO_TEST_CASE(mire_ct_int_to_str2_test1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 0>>,
		string<'0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 1>>,
		string<'1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 2>>,
		string<'1','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 3>>,
		string<'1','1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 4>>,
		string<'1','0','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 5>>,
		string<'1','0','1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 6>>,
		string<'1','1','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 7>>,
		string<'1','1','1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 8>>,
		string<'1','0','0','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 9>>,
		string<'1','0','0','1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 10>>,
		string<'1','0','1','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 11>>,
		string<'1','0','1','1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 12>>,
		string<'1','1','0','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 13>>,
		string<'1','1','0','1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 14>>,
		string<'1','1','1','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str2<integral_constant<unsigned short, 15>>,
		string<'1','1','1','1'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_int_to_str10_test1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 0>>,
		string<'0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 1>>,
		string<'1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 9>>,
		string<'9'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 10>>,
		string<'1','0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 12>>,
		string<'1','2'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 123>>,
		string<'1','2','3'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 1234>>,
		string<'1','2','3','4'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 12345>>,
		string<'1','2','3','4','5'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 123456>>,
		string<'1','2','3','4','5','6'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 1234567>>,
		string<'1','2','3','4','5','6','7'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 12345678>>,
		string<'1','2','3','4','5','6','7','8'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<int, 123456789>>,
		string<'1','2','3','4','5','6','7','8','9'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str10<integral_constant<long long, 1234567890ll>>,
		string<'1','2','3','4','5','6','7','8','9','0'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_int_to_str16_test1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<int, 0>>,
		string<'0'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<int, 1>>,
		string<'1'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<int, 7>>,
		string<'7'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<int, 14>>,
		string<'E'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<unsigned, 0x1F>>,
		string<'1','F'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<unsigned, 0xABCD>>,
		string<'A','B','C','D'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<unsigned, 0xEF1234>>,
		string<'E','F','1','2','3','4'>
	>::value));

	BOOST_CHECK((equal<
		int_to_str16<integral_constant<unsigned long long, 0xA1B2C3D4E5F6>>,
		string<'A','1','B','2','C','3','D','4','E','5','F','6'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

