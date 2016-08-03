/**
 *  .file test/mire/ct/prepend.cpp
 *  .brief Test case for compile-time prepend meta-function
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

#include <mire/ct/prepend.hpp>
#include <mire/ct/compare.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_prepend)

BOOST_AUTO_TEST_CASE(mire_ct_prepend_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		prepend_c<string<'a','b','c'>, char>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		prepend_c<string<'b','c','d'>, char,'a'>,
		string<'a','b','c','d'>
	>::value));

	BOOST_CHECK((equal<
		prepend_c<string<'d','e','f'>, char, 'a','b','c'>,
		string<'a','b','c','d','e','f'>
	>::value));

	BOOST_CHECK((equal<
		prepend_c<string<'e','f','g','h','i'>, char,'a','b','c','d'>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));

	BOOST_CHECK((equal<
		prepend_c<string<'g','h','i','j','k','l'>, char,'a','b','c','d','e','f'>,
		string<'a','b','c','d','e','f','g','h','i','j','k','l'>
	>::value));

	BOOST_CHECK((equal<
		prepend_c<prepend_c<string<'g','h','i'>, char,'d','e','f'>, char,'a','b','c'>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_prepend_string2)
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
		prepend<string<'b','c','d'>, _a>,
		string<'a','b','c','d'>
	>::value));

	BOOST_CHECK((equal<
		prepend<string<'d','e','f'>, _a,_b,_c>,
		string<'a','b','c','d','e','f'>
	>::value));

	BOOST_CHECK((equal<
		prepend<string<'e','f','g','h','i'>, _a,_b,_c,_d>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));

	BOOST_CHECK((equal<
		prepend<prepend<string<'g','h','i'>, _d,_e,_f>, _a,_b,_c>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_prepend_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		prepend<range<short, int, long>>,
		range<short, int, long>
	>::value));

	BOOST_CHECK((equal<
		prepend<range<int, long, float>, short>,
		range<short, int, long, float>
	>::value));

	BOOST_CHECK((equal<
		prepend<range<short, int, long double>, bool, char, wchar_t>,
		range<bool, char, wchar_t, short, int, long double>
	>::value));

	BOOST_CHECK((equal<
		prepend<range<long, unsigned, float, double>, bool, char, wchar_t, short, int>,
		range<bool, char, wchar_t, short, int, long, unsigned, float, double>
	>::value));

	BOOST_CHECK((equal<
		prepend<prepend<range<int, long double>, wchar_t, short>, bool, char>,
		range<bool, char, wchar_t, short, int, long double>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

