/**
 *  .file test/mire/ct/remove.cpp
 *  .brief Test case for compile-time remove meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_remove
#include <boost/test/unit_test.hpp>

#include <mire/ct/remove.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_remove)

BOOST_AUTO_TEST_CASE(mire_ct_remove_range)
{
	using namespace mire;
	using namespace mire::ct;

	BOOST_CHECK((equal<
		ct::remove<range<>, void>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		ct::remove<range<void, void, void>, void>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		ct::remove<range<long, long, long>, bool>,
		range<long, long, long>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<range<int, char, char>, char>,
		range<int>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<range<long, float, long>, long>,
		range<float>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<range<bool, bool, long>, bool>,
		range<long>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<range<char, bool, void, long, float, bool, double>, bool>,
		range<char, void, long, float, double>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<ct::remove<range<char, bool, void, long, float, double>, bool>, void>,
		range<char, long, float, double>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_remove_string1)
{
	using namespace mire;
	using namespace mire::ct;

	typedef integral_constant<char, 'A'> _A;
	typedef integral_constant<char, 'B'> _B;
	typedef integral_constant<char, 'C'> _C;
	typedef integral_constant<char, 'D'> _D;

	BOOST_CHECK((equal<
		ct::remove<empty_string, _A>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		ct::remove<string<'A','A','A'>, _A>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		ct::remove<string<'A','A','A','A'>, _B>,
		string<'A','A','A','A'>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<string<'B','A','A','A'>, _B>,
		string<'A','A','A'>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<string<'B','C','B','B'>, _C>,
		ct::remove<string<'B','B','C','B'>, _C>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<string<'D','D','D','A'>, _A>,
		string<'D','D','D'>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<string<'D','D','D','A'>, _A>,
		string<'D','D','D'>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<string<'A','B','D','C','A','D','B','C'>, _A>,
		string<'B','D','C','D','B','C'>
	>::value));

	BOOST_CHECK((equal<
		ct::remove<ct::remove<string<'A','B','D','C','A','D','B','C'>, _A>, _D>,
		string<'B','C','B','C'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_remove_string2)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		remove_c<empty_string, char, 'A'>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		remove_c<string<'A','A','A'>, char, 'A'>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		remove_c<string<'A','A','A','A'>, char, 'B'>,
		string<'A','A','A','A'>
	>::value));

	BOOST_CHECK((equal<
		remove_c<string<'B','A','A','A'>, char, 'B'>,
		string<'A','A','A'>
	>::value));

	BOOST_CHECK((equal<
		remove_c<basic_string<wchar_t,L'B',L'A',L'B',L'A'>, wchar_t, L'B'>,
		basic_string<wchar_t,L'A',L'A'>
	>::value));

	BOOST_CHECK((equal<
		remove_c<string<'B','C','B','B'>, char, 'C'>,
		remove_c<string<'B','B','C','B'>, char, 'C'>
	>::value));

	BOOST_CHECK((equal<
		remove_c<string<'D','D','D','A'>, char, 'A'>,
		string<'D','D','D'>
	>::value));

	BOOST_CHECK((equal<
		remove_c<string<'D','D','D','A'>, char, 'A'>,
		string<'D','D','D'>
	>::value));

	BOOST_CHECK((equal<
		remove_c<string<'A','B','D','C','A','D','B','C'>, char, 'A'>,
		string<'B','D','C','D','B','C'>
	>::value));

	BOOST_CHECK((equal<
		remove_c<remove_c<string<'A','B','D','C','A','D','B','C'>, char, 'A'>, char, 'D'>,
		string<'B','C','B','C'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

