/**
 *  .file test/mire/ct/empty.cpp
 *  .brief Test case for compile-time empty meta-function
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

#include <mire/ct/empty.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_empty)

template <typename Bool, bool value>
void mire_ct_test_bool(void)
{
	BOOST_CHECK(Bool::value == value);
	BOOST_CHECK(Bool() == value);
	BOOST_CHECK(Bool::type::value == value);
	BOOST_CHECK(typename Bool::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_empty_optional)
{
	using namespace mire::ct;

	mire_ct_test_bool<empty<empty_optional>, true>();
	mire_ct_test_bool<empty<optional<long>>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_nonempty_optional)
{
	using namespace mire::ct;

	mire_ct_test_bool<nonempty<empty_optional>,false>();
	mire_ct_test_bool<nonempty<optional<char>>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_empty_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<empty<empty_range>, true>();
	mire_ct_test_bool<empty<range<long>>,false>();
	mire_ct_test_bool<empty<range<int, long, float>>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_nonempty_range)
{
	using namespace mire::ct;

	mire_ct_test_bool<nonempty<empty_range>,false>();
	mire_ct_test_bool<nonempty<range<char>>, true>();
	mire_ct_test_bool<nonempty<range<bool, wchar_t, short, double>>, true>();
}

BOOST_AUTO_TEST_CASE(mire_ct_empty_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<empty<empty_string>, true>();
	mire_ct_test_bool<empty<string<'x'>>,false>();
	mire_ct_test_bool<empty<string<'s','t','r'>>,false>();
	mire_ct_test_bool<empty<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>,false>();
}

BOOST_AUTO_TEST_CASE(mire_ct_nonempty_string)
{
	using namespace mire::ct;

	mire_ct_test_bool<nonempty<empty_string>, false>();
	mire_ct_test_bool<nonempty<string<'x'>>, true>();
	mire_ct_test_bool<nonempty<string<'s','t','r','i','n','g'>>, true>();
	mire_ct_test_bool<nonempty<basic_string<wchar_t,L'a',L'b',L'c'>>, true>();
}

BOOST_AUTO_TEST_SUITE_END()

