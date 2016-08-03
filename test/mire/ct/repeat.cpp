/**
 *  .file test/mire/ct/repeat.cpp
 *  .brief Test case for compile-time repeat meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_repeat
#include <boost/test/unit_test.hpp>

#include <mire/ct/repeat.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/c_str.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_repeat)

BOOST_AUTO_TEST_CASE(mire_ct_repeat_char1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		repeat_char<integral_constant<size_t, 0>, char, 'X'>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		repeat_char_c<0, char, 'Y'>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		repeat_char<integral_constant<size_t, 0>, wchar_t, L'W'>,
		basic_string<wchar_t>
	>::value));

	BOOST_CHECK((equal<
		repeat_char<integral_constant<size_t, 1>, char, 'A'>,
		string<'A'>
	>::value));

	BOOST_CHECK((equal<
		repeat_char_c<1, char, 'B'>,
		string<'B'>
	>::value));

	BOOST_CHECK((equal<
		repeat_char_c<1, wchar_t, 'C'>,
		basic_string<wchar_t, 'C'>
	>::value));

	BOOST_CHECK((equal<
		repeat_char<integral_constant<size_t, 10>, char, 'A'>,
		string<'A','A','A','A','A','A','A','A','A','A'>
	>::value));

	BOOST_CHECK((equal<
		repeat_char_c<12, char, 'B'>,
		string<'B','B','B','B','B','B','B','B','B','B','B','B'>
	>::value));

	BOOST_CHECK((equal<
		repeat_char_c<14, wchar_t, 'C'>,
		basic_string<wchar_t, 'C','C','C','C','C','C','C','C','C','C','C','C','C','C'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_repeat_type1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		repeat_type<integral_constant<size_t, 0>, int>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		repeat_type_c<0, long>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		repeat_type<integral_constant<size_t, 1>, bool>,
		range<bool>
	>::value));

	BOOST_CHECK((equal<
		repeat_type_c<1, void>,
		range<void>
	>::value));

	BOOST_CHECK((equal<
		repeat_type<integral_constant<size_t, 4>, float>,
		range<float, float, float, float>
	>::value));

	BOOST_CHECK((equal<
		repeat_type_c<4, char>,
		range<char, char, char, char>
	>::value));

	BOOST_CHECK((equal<
		repeat_type<integral_constant<size_t, 10>, double>,
		repeat_type_c<10, double>
	>::value));

	BOOST_CHECK((nonequal<
		repeat_type_c<6, short>,
		range<char, char, char, char, char, char>
	>::value));

	BOOST_CHECK((nonequal<
		repeat_type_c<6, short>,
		range<short, short, short, short, short>
	>::value));

	BOOST_CHECK((nonequal<
		repeat_type_c<6, short>,
		range<short, short, short, short, short, int>
	>::value));

	BOOST_CHECK((nonequal<
		repeat_type_c<6, short>,
		range<long, short, short, short, short, short>
	>::value));

	BOOST_CHECK((nonequal<
		repeat_type_c<6, short>,
		range<short, short, short, short, short, short, short>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

