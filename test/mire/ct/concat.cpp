/**
 *  .file test/mire/ct/concat.cpp
 *  .brief Test case for compile-time concat meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_concat
#include <boost/test/unit_test.hpp>

#include <mire/ct/concat.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/c_str.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_concat)

BOOST_AUTO_TEST_CASE(mire_ct_concat_string1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		concat<string<'a','b','c'>>,
		string<'a','b','c'>
	>::value));

	BOOST_CHECK((equal<
		concat<
			string<'a','b','c'>,
			string<'d','e','f'>
		>,
		string<'a','b','c','d','e','f'>
	>::value));

	BOOST_CHECK((equal<
		concat<
			string<'a','b','c'>,
			string<'d','e','f'>,
			string<'g','h','i'>
		>,
		string<'a','b','c','d','e','f','g','h','i'>
	>::value));

	BOOST_CHECK((equal<
		concat<
			string<'a','b','c'>,
			string<'d','e','f'>,
			string<'g','h','i'>,
			string<'j','k','l'>
		>,
		string<'a','b','c','d','e','f','g','h','i','j','k','l'>
	>::value));

	BOOST_CHECK((equal<
		concat<
			concat<
				string<'a','b','c'>,
				string<'d','e','f'>
			>,
			concat<
				string<'g','h','i'>,
				string<'j','k','l'>
			>
		>,
		string<'a','b','c','d','e','f','g','h','i','j','k','l'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_concat_string2)
{
	using namespace mire::ct;

	BOOST_CHECK(std::strcmp(
		c_str<concat<string<'a','b','c'>>>::value,
		"abc"
	) == 0);

	BOOST_CHECK(std::strcmp(
		c_str<concat<
			string<'a','b','c'>,
			string<'d','e','f'>
		>>::value,
		"abcdef"
	) == 0);

	BOOST_CHECK(std::strcmp(
		c_str<concat<
			string<'a','b','c'>,
			string<'d','e','f'>,
			string<'g','h','i'>
		>>::value,
		"abcdefghi"
	) == 0);

	BOOST_CHECK(std::strcmp(
		c_str<concat<
			string<'a','b','c'>,
			string<'d','e','f'>,
			string<'g','h','i'>,
			string<'j','k','l'>
		>>::value,
		"abcdefghijkl"
	) == 0);
}

BOOST_AUTO_TEST_CASE(mire_ct_concat_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		concat<range<short, int, long>>,
		range<short, int, long>
	>::value));

	BOOST_CHECK((equal<
		concat<
			range<bool, char>,
			range<wchar_t, short, int>,
			range<long double>
		>,
		range<bool, char, wchar_t, short, int, long double>
	>::value));

	BOOST_CHECK((equal<
		concat<
			range<bool, char, wchar_t>,
			range<short, int, long>,
			range<unsigned>,
			range<float, double>
		>,
		range<bool, char, wchar_t, short, int, long, unsigned, float, double>
	>::value));

	BOOST_CHECK((equal<
		concat<
			concat<
				range<bool, char, wchar_t>,
				range<short, int, long>
			>,
			concat<
				range<unsigned>,
				range<float, double>
			>
		>,
		range<bool, char, wchar_t, short, int, long, unsigned, float, double>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

