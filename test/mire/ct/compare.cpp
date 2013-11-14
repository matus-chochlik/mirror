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

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_optional)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		empty_optional,
		empty_optional
	>, true>();
	mire_ct_test_bool<equal<
		optional<float>,
		optional<float>
	>, true>();
	mire_ct_test_bool<equal<
		empty_optional,
		optional<char>
	>,false>();
	mire_ct_test_bool<equal<
		optional<char>,
		empty_optional
	>,false>();
	mire_ct_test_bool<equal<
		optional<short>,
		optional<float>
	>,false>();
	mire_ct_test_bool<equal<
		optional<float>,
		optional<short>
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_optional)
{
	using namespace mire::ct;

	mire_ct_test_bool<nonequal<
		empty_optional,
		empty_optional
	>,false>();
	mire_ct_test_bool<nonequal<
		optional<long>,
		optional<long>
	>,false>();
	mire_ct_test_bool<nonequal<
		empty_optional,
		optional<short>
	>, true>();
	mire_ct_test_bool<nonequal<
		optional<short>,
		empty_optional
	>, true>();
	mire_ct_test_bool<nonequal<
		optional<char>,
		optional<bool>
	>, true>();
	mire_ct_test_bool<nonequal<
		optional<bool>,
		optional<char>
	>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		empty_range,
		empty_range
	>, true>();
	mire_ct_test_bool<equal<
		range<float>,
		range<float>
	>, true>();
	mire_ct_test_bool<equal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>, true>();
	mire_ct_test_bool<equal<
		empty_range,
		range<float>
	>,false>();
	mire_ct_test_bool<equal<
		range<float>,
		empty_range
	>,false>();
	mire_ct_test_bool<equal<
		range<bool, char, short, int, long, float, double>,
		range<wchar_t, long long, long double, unsigned>
	>,false>();
	mire_ct_test_bool<equal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, wchar_t>
	>,false>();
	mire_ct_test_bool<equal<
		range<char, bool, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<nonequal<
		empty_range,
		empty_range
	>,false>();
	mire_ct_test_bool<nonequal<
		range<float>,
		range<float>
	>,false>();
	mire_ct_test_bool<nonequal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>,false>();
	mire_ct_test_bool<nonequal<
		empty_range,
		range<float>
	>, true>();
	mire_ct_test_bool<nonequal<
		range<float>,
		empty_range
	>, true>();
	mire_ct_test_bool<nonequal<
		range<bool, char, short, int, long, float, double>,
		range<wchar_t, long long, long double, unsigned>
	>, true>();
	mire_ct_test_bool<nonequal<
		range<bool, char, short, int, long, float, double>,
		range<bool, char, short, int, long, float, wchar_t>
	>, true>();
	mire_ct_test_bool<nonequal<
		range<char, bool, short, int, long, float, double>,
		range<bool, char, short, int, long, float, double>
	>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		empty_string,
		empty_string
	>, true>();
	mire_ct_test_bool<equal<
		string<'s'>,
		string<'s'>
	>, true>();
	mire_ct_test_bool<equal<
		string<'x'>,
		string<'y'>
	>,false>();
	mire_ct_test_bool<equal<
		string<'x','y'>,
		string<'x','y'>
	>, true>();
	mire_ct_test_bool<equal<
		string<'z','y','x'>,
		string<'x','y','z'>
	>,false>();
	mire_ct_test_bool<equal<
		string<'s','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>, true>();
	mire_ct_test_bool<equal<
		string<'S','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>,false>();
	mire_ct_test_bool<equal<
		string<'s','t','r','i','n','g'>,
		string<'S','t','r','i','n','g'>
	>,false>();
	mire_ct_test_bool<equal<
		string<'s','t','r','i','n','G'>,
		string<'s','t','r','i','n','g'>
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<nonequal<
		empty_string,
		empty_string
	>,false>();
	mire_ct_test_bool<nonequal<
		string<'s'>,
		string<'s'>
	>,false>();
	mire_ct_test_bool<nonequal<
		string<'x'>,
		string<'y'>
	>, true>();
	mire_ct_test_bool<nonequal<
		string<'x','y'>,
		string<'x','y'>
	>,false>();
	mire_ct_test_bool<nonequal<
		string<'z','y','x'>,
		string<'x','y','z'>
	>, true>();
	mire_ct_test_bool<nonequal<
		string<'s','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>,false>();
	mire_ct_test_bool<nonequal<
		string<'S','t','r','i','n','g'>,
		string<'s','t','r','i','n','g'>
	>, true>();
	mire_ct_test_bool<nonequal<
		string<'s','t','r','i','n','g'>,
		string<'S','t','r','i','n','g'>
	>, true>();
	mire_ct_test_bool<nonequal<
		string<'s','t','r','i','n','G'>,
		string<'s','t','r','i','n','g'>
	>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_int_const)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal<
		integral_constant<int, 0>,
		integral_constant<int, 0>
	>, true>();
	mire_ct_test_bool<equal<
		integral_constant<long, 1>,
		integral_constant<long, 1>
	>, true>();
	mire_ct_test_bool<equal<
		integral_constant<int, 5>,
		integral_constant<int, 5>
	>, true>();
	mire_ct_test_bool<equal<
		integral_constant<int, 1>,
		integral_constant<int, 3>
	>,false>();
	mire_ct_test_bool<equal<
		integral_constant<short, 5>,
		integral_constant<long, 5>
	>, true>();
	mire_ct_test_bool<equal<
		integral_constant<short, 4>,
		integral_constant<unsigned, 5>
	>,false>();
	mire_ct_test_bool<equal<
		integral_constant<int, 1>,
		integral_constant<bool,true>
	>, true>();
	mire_ct_test_bool<equal<
		integral_constant<int, 2>,
		integral_constant<bool,false>
	>,false>();
	mire_ct_test_bool<equal<
		integral_constant<unsigned, 0>,
		integral_constant<bool,false>
	>, true>();
	mire_ct_test_bool<equal<
		integral_constant<bool, true>,
		integral_constant<bool, true>
	>, true>();
	mire_ct_test_bool<equal<
		integral_constant<bool,false>,
		integral_constant<bool, true>
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_nonequal_int_const)
{
	using namespace mire::ct;

	mire_ct_test_bool<nonequal<
		integral_constant<int, 0>,
		integral_constant<int, 0>
	>,false>();
	mire_ct_test_bool<nonequal<
		integral_constant<int, 2>,
		integral_constant<int, 3>
	>, true>();
	mire_ct_test_bool<nonequal<
		integral_constant<long, 1>,
		integral_constant<long, 1>
	>,false>();
	mire_ct_test_bool<nonequal<
		integral_constant<long, 5>,
		integral_constant<long, 9>
	>, true>();
	mire_ct_test_bool<nonequal<
		integral_constant<bool, true>,
		integral_constant<long, 1>
	>,false>();
	mire_ct_test_bool<nonequal<
		integral_constant<bool, true>,
		integral_constant<long, 0>
	>, true>();
	mire_ct_test_bool<nonequal<
		integral_constant<bool, false>,
		integral_constant<long, 1>
	>, true>();
	mire_ct_test_bool<nonequal<
		integral_constant<short, 1>,
		integral_constant<bool, true>
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_equal_types_test)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal_types<int, int>, true>();
	mire_ct_test_bool<equal_types<int, int, int, int, int>, true>();
	mire_ct_test_bool<equal_types<float, float, float, float>, true>();
	mire_ct_test_bool<equal_types<char, short, long, unsigned>, false>();
	mire_ct_test_bool<equal_types<bool, int, int, int, int>,false>();
	mire_ct_test_bool<equal_types<int, int, bool, int, int>,false>();
	mire_ct_test_bool<equal_types<int, int, int, int, bool>,false>();
}

BOOST_AUTO_TEST_SUITE_END()

