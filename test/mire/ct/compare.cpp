/**
 *  .file test/mire/ct/compare.cpp
 *  .brief Test case for compile-time equal meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_compare
#include <boost/test/unit_test.hpp>

#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_compare)

BOOST_AUTO_TEST_CASE(mire_ct_equal_optional)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		empty_optional,
		empty_optional
	>::value == true));
	BOOST_CHECK((equal<
		optional<float>,
		optional<float>
	>::value == true));
	BOOST_CHECK((equal<
		empty_optional,
		optional<char>
	>::value == false));
	BOOST_CHECK((equal<
		optional<char>,
		empty_optional
	>::value == false));
	BOOST_CHECK((equal<
		optional<short>,
		optional<float>
	>::value == false));
	BOOST_CHECK((equal<
		optional<float>,
		optional<short>
	>::value == false));
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_optional)
{
	using namespace mire::ct;

	BOOST_CHECK((nonequal<
		empty_optional,
		empty_optional
	>::value == false));
	BOOST_CHECK((nonequal<
		optional<long>,
		optional<long>
	>::value == false));
	BOOST_CHECK((nonequal<
		empty_optional,
		optional<short>
	>::value == true));
	BOOST_CHECK((nonequal<
		optional<short>,
		empty_optional
	>::value == true));
	BOOST_CHECK((nonequal<
		optional<char>,
		optional<bool>
	>::value == true));
	BOOST_CHECK((nonequal<
		optional<bool>,
		optional<char>
	>::value == true));
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		empty_range,
		empty_range
	>::value == true));
	BOOST_CHECK((equal<
		range<float>,
		range<float>
	>::value == true));
	BOOST_CHECK((equal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>::value == true));
	BOOST_CHECK((equal<
		empty_range,
		range<float>
	>::value == false));
	BOOST_CHECK((equal<
		range<float>,
		empty_range
	>::value == false));
	BOOST_CHECK((equal<
		range<bool, char, short, int, long, float, double>,
		range<wchar_t, long long, long double, unsigned>
	>::value == false));
	BOOST_CHECK((equal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, wchar_t>
	>::value == false));
	BOOST_CHECK((equal<
		range<char, bool, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>::value == false));
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_range)
{
	using namespace mire::ct;

	BOOST_CHECK((nonequal<
		empty_range,
		empty_range
	>::value == false));
	BOOST_CHECK((nonequal<
		range<float>,
		range<float>
	>::value == false));
	BOOST_CHECK((nonequal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>::value == false));
	BOOST_CHECK((nonequal<
		empty_range,
		range<float>
	>::value == true));
	BOOST_CHECK((nonequal<
		range<float>,
		empty_range
	>::value == true));
	BOOST_CHECK((nonequal<
		range<bool, char, short, int, long, float, double>,
		range<wchar_t, long long, long double, unsigned>
	>::value == true));
	BOOST_CHECK((nonequal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, wchar_t>
	>::value == true));
	BOOST_CHECK((nonequal<
		range<char, bool, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>::value == true));
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		empty_string,
		empty_string
	>::value == true));
	BOOST_CHECK((equal<
		string<'s'>,
		string<'s'>
	>::value == true));
	BOOST_CHECK((equal<
		string<'x'>,
		string<'y'>
	>::value == false));
	BOOST_CHECK((equal<
		string<'x','y'>,
		string<'x','y'>
	>::value == true));
	BOOST_CHECK((equal<
		string<'z','y','x'>,
		string<'x','y','z'>
	>::value == false));
	BOOST_CHECK((equal<
		string<'s','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>::value == true));
	BOOST_CHECK((equal<
		string<'S','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>::value == false));
	BOOST_CHECK((equal<
		string<'s','t','r','i','n','g'>,
		string<'S','t','r','i','n','g'>
	>::value == false));
	BOOST_CHECK((equal<
		string<'s','t','r','i','n','G'>,
		string<'s','t','r','i','n','g'>
	>::value == false));
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_string)
{
	using namespace mire::ct;

	BOOST_CHECK((nonequal<
		empty_string,
		empty_string
	>::value == false));
	BOOST_CHECK((nonequal<
		string<'s'>,
		string<'s'>
	>::value == false));
	BOOST_CHECK((nonequal<
		string<'x'>,
		string<'y'>
	>::value == true));
	BOOST_CHECK((nonequal<
		string<'x','y'>,
		string<'x','y'>
	>::value == false));
	BOOST_CHECK((nonequal<
		string<'z','y','x'>,
		string<'x','y','z'>
	>::value == true));
	BOOST_CHECK((nonequal<
		string<'s','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>::value == false));
	BOOST_CHECK((nonequal<
		string<'S','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>::value == true));
	BOOST_CHECK((nonequal<
		string<'s','t','r','i','n','g'>,
		string<'S','t','r','i','n','g'>
	>::value == true));
	BOOST_CHECK((nonequal<
		string<'s','t','r','i','n','G'>,
		string<'s','t','r','i','n','g'>
	>::value == true));
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_int_const)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		integral_constant<int, 0>,
		integral_constant<int, 0>
	>::value == true));
	BOOST_CHECK((equal<
		integral_constant<long, 1>,
		integral_constant<long, 1>
	>::value == true));
	BOOST_CHECK((equal<
		integral_constant<int, 5>,
		integral_constant<int, 5>
	>::value == true));
	BOOST_CHECK((equal<
		integral_constant<int, 1>,
		integral_constant<int, 3>
	>::value == false));
	BOOST_CHECK((equal<
		integral_constant<short, 5>,
		integral_constant<long, 5>
	>::value == true));
	BOOST_CHECK((equal<
		integral_constant<short, 4>,
		integral_constant<unsigned, 5>
	>::value == false));
	BOOST_CHECK((equal<
		integral_constant<int, 1>,
		integral_constant<bool,true>
	>::value == true));
	BOOST_CHECK((equal<
		integral_constant<int, 2>,
		integral_constant<bool,false>
	>::value == false));
	BOOST_CHECK((equal<
		integral_constant<unsigned, 0>,
		integral_constant<bool,false>
	>::value == true));
	BOOST_CHECK((equal<
		integral_constant<bool, true>,
		integral_constant<bool, true>
	>::value == true));
	BOOST_CHECK((equal<
		integral_constant<bool,false>,
		integral_constant<bool, true>
	>::value == false));
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_int_const)
{
	using namespace mire::ct;

	BOOST_CHECK((nonequal<
		integral_constant<int, 0>,
		integral_constant<int, 0>
	>::value == false));
	BOOST_CHECK((nonequal<
		integral_constant<int, 2>,
		integral_constant<int, 3>
	>::value == true));
	BOOST_CHECK((nonequal<
		integral_constant<long, 1>,
		integral_constant<long, 1>
	>::value == false));
	BOOST_CHECK((nonequal<
		integral_constant<long, 5>,
		integral_constant<long, 9>
	>::value == true));
	BOOST_CHECK((nonequal<
		integral_constant<bool, true>,
		integral_constant<long, 1>
	>::value == false));
	BOOST_CHECK((nonequal<
		integral_constant<bool, true>,
		integral_constant<long, 0>
	>::value == true));
	BOOST_CHECK((nonequal<
		integral_constant<bool, false>,
		integral_constant<long, 1>
	>::value == true));
	BOOST_CHECK((nonequal<
		integral_constant<short, 1>,
		integral_constant<bool, true>
	>::value == false));
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_types_test)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<int, int>::value == true));
	BOOST_CHECK((equal_types<int, int, int, int, int>::value == true));
	BOOST_CHECK((equal_types<float, float, float, float>::value == true));
	BOOST_CHECK((equal_types<char, short, long, unsigned>::value == false));
	BOOST_CHECK((equal_types<bool, int, int, int, int>::value == false));
	BOOST_CHECK((equal_types<int, int, bool, int, int>::value == false));
	BOOST_CHECK((equal_types<int, int, int, int, bool>::value == false));
}

BOOST_AUTO_TEST_SUITE_END()

