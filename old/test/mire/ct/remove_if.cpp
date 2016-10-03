/**
 *  .file test/mire/ct/remove_if.cpp
 *  .brief Test case for compile-time remove_if meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_remove_if
#include <boost/test/unit_test.hpp>

#include <mire/ct/remove_if.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/not.hpp>
#include <mire/ct/compare.hpp>

#include <type_traits>

BOOST_AUTO_TEST_SUITE(mire_ct_remove_if)

BOOST_AUTO_TEST_CASE(mire_ct_remove_if_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		remove_if<empty_range, std::is_integral<arg<0>>>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		remove_if<range<double, int, float, short, void>, std::is_integral<arg<0>>>,
		range<double, float, void>
	>::value));

	BOOST_CHECK((equal<
		remove_if<range<double, int, float, char>, std::is_floating_point<arg<0>>>,
		range<int, char>
	>::value));

	BOOST_CHECK((equal<
		remove_if<range<double, int, float, char>, std::is_void<arg<0>>>,
		range<double, int, float, char>
	>::value));

	BOOST_CHECK((equal<
		remove_if<range<double, int, float, char>, std::is_fundamental<arg<0>>>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		remove_if<range<double, int, float, char>, not_<std::is_same<arg<0>, char>>>,
		range<char>
	>::value));
}

template <typename Char1, Char1 X>
struct mire_ct_remove_if_string_same_char
{
	template <typename Char2, Char2 C>
	struct apply_c
	 : mire::ct::integral_constant<bool, C == X>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_remove_if_string1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		remove_if<empty_string, mire_ct_remove_if_string_same_char<char, 'A'>>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		remove_if<
			string<'a'>,
			mire_ct_remove_if_string_same_char<char, 'A'>
		>,
		string<'a'>
	>::value));

	BOOST_CHECK((equal<
		remove_if<
			string<'A'>,
			mire_ct_remove_if_string_same_char<char, 'A'>
		>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		remove_if<
			string<'B','L','A','H'>,
			mire_ct_remove_if_string_same_char<char, 'H'>
		>,
		string<'B','L','A'>
	>::value));

	BOOST_CHECK((equal<
		remove_if<
			string<'S','t','r','i','n','g'>,
			mire_ct_remove_if_string_same_char<char, 'A'>
		>,
		string<'S','t','r','i','n','g'>
	>::value));
}

struct mire_ct_remove_if_string_is_upper
{
	template <typename Char, Char C>
	struct apply_c
	 : mire::ct::integral_constant<bool, (C >= 'A' && C <= 'Z')>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_remove_if_string2)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		remove_if<empty_string, mire_ct_remove_if_string_is_upper>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		remove_if<
			string<'a','b','c','d','e'>,
			mire_ct_remove_if_string_is_upper
		>,
		string<'a','b','c','d','e'>
	>::value));

	BOOST_CHECK((equal<
		remove_if<
			string<'S','t','R','i','n','G'>,
			mire_ct_remove_if_string_is_upper
		>,
		string<'t','i','n'>
	>::value));

	BOOST_CHECK((equal<
		remove_if<
			string<'S','T','R','I','N','G'>,
			mire_ct_remove_if_string_is_upper
		>,
		empty_string
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

