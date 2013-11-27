/**
 *  .file test/mire/ct/size.cpp
 *  .brief Test case for compile-time size meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_size
#include <boost/test/unit_test.hpp>

#include <mire/ct/size.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_size)

BOOST_AUTO_TEST_CASE(mire_ct_size_optional)
{
	using namespace mire::ct;

	BOOST_CHECK((size<empty_optional>::value == 0));
	BOOST_CHECK((size<optional<long>>::value == 1));
	BOOST_CHECK((size<optional<bool>>::value == 1));
	BOOST_CHECK((size<optional<char>>::value == 1));
}

BOOST_AUTO_TEST_CASE(mire_ct_size_range)
{
	using namespace mire::ct;

	BOOST_CHECK((size<empty_range>::value == 0));
	BOOST_CHECK((size<range<long>>::value == 1));
	BOOST_CHECK((size<range<short, int>>::value == 2));
	BOOST_CHECK((size<range<int, long, float>>::value == 3));
	BOOST_CHECK((size<range<long, float, double, bool>>::value == 4));
}

BOOST_AUTO_TEST_CASE(mire_ct_size_string)
{
	using namespace mire::ct;

	BOOST_CHECK((size<empty_string>::value == 0));
	BOOST_CHECK((size<string<'x'>>::value == 1));
	BOOST_CHECK((size<string<'x','y'>>::value == 2));
	BOOST_CHECK((size<string<'s','t','r'>>::value == 3));
	BOOST_CHECK((size<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>::value == 4));
}

BOOST_AUTO_TEST_CASE(mire_ct_length_string)
{
	using namespace mire::ct;

	BOOST_CHECK((length<empty_string>::value == 0));
	BOOST_CHECK((length<string<'x'>>::value == 1));
	BOOST_CHECK((length<string<'x','y'>>::value == 2));
	BOOST_CHECK((length<string<'s','t','r'>>::value == 3));
	BOOST_CHECK((length<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>::value == 4));
}

BOOST_AUTO_TEST_SUITE_END()

