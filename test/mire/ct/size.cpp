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

template <typename Size, size_t value>
void mire_ct_test_size_t(void)
{
	BOOST_CHECK(Size::value == value);
	BOOST_CHECK(Size() == value);
	BOOST_CHECK(Size::type::value== value);
	BOOST_CHECK(typename Size::type() == value);
}

BOOST_AUTO_TEST_CASE(mire_ct_size_optional)
{
	using namespace mire::ct;

	mire_ct_test_size_t<size<empty_optional>, 0>();
	mire_ct_test_size_t<size<optional<long>>, 1>();
	mire_ct_test_size_t<size<optional<bool>>, 1>();
	mire_ct_test_size_t<size<optional<char>>, 1>();
}

BOOST_AUTO_TEST_CASE(mire_ct_size_range)
{
	using namespace mire::ct;

	mire_ct_test_size_t<size<empty_range>, 0>();
	mire_ct_test_size_t<size<range<long>>, 1>();
	mire_ct_test_size_t<size<range<short, int>>, 2>();
	mire_ct_test_size_t<size<range<int, long, float>>, 3>();
	mire_ct_test_size_t<size<range<long, float, double, bool>>, 4>();
}

BOOST_AUTO_TEST_CASE(mire_ct_size_string)
{
	using namespace mire::ct;

	mire_ct_test_size_t<size<empty_string>, 0>();
	mire_ct_test_size_t<size<string<'x'>>, 1>();
	mire_ct_test_size_t<size<string<'x','y'>>, 2>();
	mire_ct_test_size_t<size<string<'s','t','r'>>, 3>();
	mire_ct_test_size_t<size<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>, 4>();
}

BOOST_AUTO_TEST_CASE(mire_ct_length_string)
{
	using namespace mire::ct;

	mire_ct_test_size_t<length<empty_string>, 0>();
	mire_ct_test_size_t<length<string<'x'>>, 1>();
	mire_ct_test_size_t<length<string<'x','y'>>, 2>();
	mire_ct_test_size_t<length<string<'s','t','r'>>, 3>();
	mire_ct_test_size_t<length<basic_string<wchar_t,L'a',L'b',L'c',L'd'>>, 4>();
}

BOOST_AUTO_TEST_SUITE_END()

