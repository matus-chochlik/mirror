/**
 *  .file test/mire/ct/append.cpp
 *  .brief Test case for compile-time append meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_empty
#include <boost/test/unit_test.hpp>

#include <mire/ct/append.hpp>
#include <mire/ct/compare.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_append)

BOOST_AUTO_TEST_CASE(mire_ct_append_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		append_c<string<'a','b','c'>, char>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		append_c<string<'a','b','c'>, char,'d'>,
		string<'a','b','c','d'>
	>::value));

	BOOST_CHECK((equal<
		append_c<string<'a','b','c'>, char, 'd','e','f'>,
		string<'a','b','c','d','e','f'>
	>::value));

	BOOST_CHECK((equal<
		append_c<string<'a','b','c','d','e'>, char,'f','g','h','i'>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));

	BOOST_CHECK((equal<
		append_c<string<'a','b','c','d','e','f'>, char,'g','h','i','j','k','l'>,
		string<'a','b','c','d','e','f','g','h','i','j','k','l'>
	>::value));

	BOOST_CHECK((equal<
		append_c<append_c<string<'a','b','c'>, char,'d','e','f'>, char,'g','h','i'>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_append_string2)
{
	using namespace mire::ct;

	typedef integral_constant<char, 'a'> _a;
	typedef integral_constant<char, 'b'> _b;
	typedef integral_constant<char, 'c'> _c;
	typedef integral_constant<char, 'd'> _d;
	typedef integral_constant<char, 'e'> _e;
	typedef integral_constant<char, 'f'> _f;
	typedef integral_constant<char, 'g'> _g;
	typedef integral_constant<char, 'h'> _h;
	typedef integral_constant<char, 'i'> _i;

	BOOST_CHECK((equal<
		append<string<'a','b','c'>, _d>,
		string<'a','b','c','d'>
	>::value));

	BOOST_CHECK((equal<
		append<string<'a','b','c'>, _d,_e,_f>,
		string<'a','b','c','d','e','f'>
	>::value));

	BOOST_CHECK((equal<
		append<string<'a','b','c','d','e'>, _f,_g,_h,_i>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));

	BOOST_CHECK((equal<
		append<append<string<'a','b','c'>, _d,_e,_f>, _g,_h,_i>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_append_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		append<range<short, int, long>>,
		range<short, int, long>
	>::value));

	BOOST_CHECK((equal<
		append<range<short, int, long>, float>,
		range<short, int, long, float>
	>::value));

	BOOST_CHECK((equal<
		append<range<bool, char, wchar_t, short>, int, long double>,
		range<bool, char, wchar_t, short, int, long double>
	>::value));

	BOOST_CHECK((equal<
		append<range<bool, char, wchar_t, short, int>, long, unsigned, float, double>,
		range<bool, char, wchar_t, short, int, long, unsigned, float, double>
	>::value));

	BOOST_CHECK((equal<
		append<append<range<bool, char>, wchar_t, short>, int, long double>,
		range<bool, char, wchar_t, short, int, long double>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

