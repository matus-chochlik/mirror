/**
 *  .file test/mire/ct/zip.cpp
 *  .brief Test case for compile-time zip meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_zip
#include <boost/test/unit_test.hpp>

#include <mire/ct/zip.hpp>
#include <mire/ct/repeat.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_zip)

BOOST_AUTO_TEST_CASE(mire_ct_zip_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		zip<range<>>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		zip<range<int, bool, char, float, double>>,
		range<int, bool, char, float, double>
	>::value));

	BOOST_CHECK((equal<
		zip<
			range<long, long, long, long>,
			range<char, char, char, char>
		>,
		range<long, char, long, char, long, char, long, char>
	>::value));

	BOOST_CHECK((equal<
		zip<
			range<char, char, char, char>,
			range<long, long, long, long>
		>,
		range<char, long, char, long, char, long, char, long>
	>::value));

	BOOST_CHECK((equal<
		zip<
			range<long, long, long>,
			range<char, char, char>,
			range<void, void, void>
		>,
		range<long, char, void, long, char, void, long, char, void>
	>::value));

	BOOST_CHECK((equal<
		zip<
			range<long, long>,
			range<char, char>,
			range<void, void>,
			range<bool, bool>
		>,
		range<long, char, void, bool, long, char, void, bool>
	>::value));

	BOOST_CHECK((equal<
		zip<
			range<int>,
			range<char>,
			range<wchar_t>,
			range<long>,
			range<double>,
			range<void>,
			range<bool>
		>,
		range<int, char, wchar_t, long, double, void, bool>
	>::value));

	BOOST_CHECK((equal<
		zip<
			empty_range,
			empty_range,
			empty_range,
			range<>,
			empty_range,
			range<>,
			empty_range
		>,
		empty_range
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_zip_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		zip<string<>>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		zip<string<'A','B','C','D'>>,
		string<'A','B','C','D'>
	>::value));

	BOOST_CHECK((equal<
		zip<
			string<'S','T','A','L','K','E','R'>,
			repeat_char_c<7, char, '.'>
		>,
		string<'S','.','T','.','A','.','L','.','K','.','E','.','R','.'>
	>::value));

	BOOST_CHECK((equal<
		zip<
			string<'A','C','E','G','I'>,
			string<'B','D','F','H','J'>
		>,
		string<'A','B','C','D','E','F','G','H','I','J'>
	>::value));

	BOOST_CHECK((equal<
		zip<
			string<'A','F','K','P','U'>,
			string<'B','G','L','Q','V'>,
			string<'C','H','M','R','W'>,
			string<'D','I','N','S','X'>,
			string<'E','J','O','T','Y'>
		>,
		string<
			'A','B','C','D','E',
			'F','G','H','I','J',
			'K','L','M','N','O',
			'P','Q','R','S','T',
			'U','V','W','X','Y'
		>
	>::value));

}

BOOST_AUTO_TEST_SUITE_END()

