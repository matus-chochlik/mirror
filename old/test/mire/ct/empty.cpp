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

BOOST_AUTO_TEST_CASE(mire_ct_empty_optional)
{
	using namespace mire::ct;

	BOOST_CHECK(( empty<empty_optional>::value));
	BOOST_CHECK((!empty<optional<long>>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_nonempty_optional)
{
	using namespace mire::ct;

	BOOST_CHECK((!nonempty<empty_optional>::value));
	BOOST_CHECK(( nonempty<optional<char>>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_empty_range)
{
	using namespace mire::ct;

	BOOST_CHECK(( empty<empty_range>::value));
	BOOST_CHECK((!empty<range<long>>::value));
	BOOST_CHECK((!empty<range<int, long, float>>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_nonempty_range)
{
	using namespace mire::ct;

	BOOST_CHECK((!nonempty<empty_range>::value));
	BOOST_CHECK(( nonempty<range<char>>::value));
	BOOST_CHECK(( nonempty<range<bool, wchar_t, short, double>>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_empty_string)
{
	using namespace mire::ct;

	BOOST_CHECK(( empty<empty_string>::value));
	BOOST_CHECK((!empty<string<'x'>>::value));
	BOOST_CHECK((!empty<string<'s','t','r'>>::value));
	BOOST_CHECK((!empty<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_nonempty_string)
{
	using namespace mire::ct;

	BOOST_CHECK((!nonempty<empty_string>::value));
	BOOST_CHECK(( nonempty<string<'x'>>::value));
	BOOST_CHECK(( nonempty<string<'s','t','r','i','n','g'>>::value));
	BOOST_CHECK(( nonempty<basic_string<wchar_t,L'a',L'b',L'c'>>::value));
}

BOOST_AUTO_TEST_SUITE_END()

