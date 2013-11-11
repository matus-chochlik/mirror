/**
 *  .file test/mire/ct/front.cpp
 *  .brief Test case for compile-time front meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_front
#include <boost/test/unit_test.hpp>

#include <mire/ct/front.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_front)

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

template <typename Char, char value, bool check>
void mire_ct_test_char(void)
{
	BOOST_CHECK((Char::value == value) == check);
	BOOST_CHECK((Char() == value) == check);
	BOOST_CHECK((Char::type::value == value) == check);
	BOOST_CHECK((typename Char::type() == value) == check);
}

BOOST_AUTO_TEST_CASE(mire_ct_front_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<equal_types<
		front<range<long>>,
		long
	>, true>();

	mire_ct_test_bool<equal_types<
		front<range<char>>,
		bool
	>,false>();

	mire_ct_test_bool<equal_types<
		front<range<short, int, long>>,
		short
	>, true>();

	mire_ct_test_bool<equal_types<
		front<range<short, int, long>>,
		int
	>,false>();

	mire_ct_test_bool<equal_types<
		front<range<short, int, long>>,
		long
	>,false>();

	mire_ct_test_bool<equal_types<
		front<range<bool, short, int, long, unsigned, float>>,
		char
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_front_string)
{
	using namespace mire::ct;

	mire_ct_test_char<front<empty_string>, '\0', true>();
	mire_ct_test_char<front<string<'A'>>, 'A', true>();
	mire_ct_test_char<front<string<'A'>>, '\0', false>();
	mire_ct_test_char<front<string<'B','C','D'>>, 'A',false>();
	mire_ct_test_char<front<string<'B','C','D'>>, 'B', true>();
	mire_ct_test_char<front<string<'B','C','D'>>, 'C',false>();
	mire_ct_test_char<front<string<'B','C','D'>>, 'D',false>();
}

BOOST_AUTO_TEST_SUITE_END()

