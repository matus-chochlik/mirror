/**
 *  .file test/mire/ct/pop_front.cpp
 *  .brief Test case for compile-time pop_front meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_pop_front
#include <boost/test/unit_test.hpp>

#include <mire/ct/pop_front.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_pop_front)

BOOST_AUTO_TEST_CASE(mire_ct_pop_front_range)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		pop_front<range<>>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		pop_front<range<long>>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		pop_front<range<long, short>>,
		range<short>
	>::value));

	BOOST_CHECK((equal<
		pop_front<pop_front<range<long, short>>>,
		empty_range
	>::value));

	BOOST_CHECK((equal<
		pop_front<range<void, int, char, bool, long, short, double, float>>,
		range<int, char, bool, long, short, double, float>
	>::value));

	BOOST_CHECK((equal<
		pop_front<pop_front<pop_front<range<int, bool, long, double, float>>>>,
		range<double, float>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_pop_front_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		pop_front<empty_string>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		pop_front<string<'A'>>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		pop_front<string<'A','B'>>,
		string<'B'>
	>::value));

	BOOST_CHECK((equal<
		pop_front<pop_front<string<'A','B'>>>,
		empty_string
	>::value));

	BOOST_CHECK((equal<
		pop_front<basic_string<wchar_t,L'A',L'B',L'C'>>,
		basic_string<wchar_t,L'B',L'C'>
	>::value));

	BOOST_CHECK((equal<
		pop_front<pop_front<pop_front<basic_string<wchar_t,L'A',L'B',L'C'>>>>,
		basic_string<wchar_t>
	>::value));

	BOOST_CHECK((equal<
		pop_front<pop_front<pop_front<string<'A','B','C','D','E','F','G','H','I'>>>>,
		string<'D','E','F','G','H','I'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

