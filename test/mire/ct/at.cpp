/**
 *  .file test/mire/ct/at.cpp
 *  .brief Test case for compile-time at meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_at
#include <boost/test/unit_test.hpp>

#include <mire/ct/at.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_at)

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

BOOST_AUTO_TEST_CASE(mire_ct_at_range)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, zero>::type,
		bool
	>, true>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, zero>::type,
		short
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, one>::type,
		short
	>, true>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, one>::type,
		bool
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, one>::type,
		int
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, two>::type,
		int
	>, true>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, two>::type,
		short
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, two>::type,
		long
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, three>::type,
		long
	>, true>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, three>::type,
		int
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, three>::type,
		unsigned
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, four>::type,
		unsigned
	>, true>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, four>::type,
		long
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, four>::type,
		float
	>,false>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, five>::type,
		float
	>, true>();

	mire_ct_test_bool<is_same<
		at<range<bool, short, int, long, unsigned, float>, five>::type,
		unsigned
	>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_at_string)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> zero;
	typedef integral_constant<size_t, 1> one;
	typedef integral_constant<size_t, 2> two;
	typedef integral_constant<size_t, 3> three;
	typedef integral_constant<size_t, 4> four;
	typedef integral_constant<size_t, 5> five;

	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, zero>, 's', true>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, zero>, 't',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, one>,  't', true>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, one>,  's',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, one>,  'r',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, two>,  'r', true>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, two>,  't',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, two>,  'i',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, three>,'i', true>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, three>,'r',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, three>,'n',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, four>, 'n', true>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, four>, 'i',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, four>, 'g',false>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, five>, 'g', true>();
	mire_ct_test_char<at<string<'s','t','r','i','n','g'>, five>, 'n',false>();
}

BOOST_AUTO_TEST_SUITE_END()

