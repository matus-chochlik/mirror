/**
 *  .file test/mire/ct/to_string.cpp
 *  .brief Test case for compile-time to_string meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_to_string
#include <boost/test/unit_test.hpp>

#include <mire/ct/to_string.hpp>
#include <mire/ct/compare.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_to_string)

struct mire_ct_test_string_abcdef
{
	static constexpr const char* c_str = "abcdef";
	static constexpr size_t size = 6;
};

struct mire_ct_test_string_ghijklmnopqrstu
{
	static constexpr const char* c_str = "ghijklmnopqrstu";
	static constexpr size_t size = 15;
};

BOOST_AUTO_TEST_CASE(mire_ct_string_to_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		to_string<mire_ct_test_string_abcdef>,
		string<'a','b','c','d','e','f'>
	>::value));

	BOOST_CHECK((equal<
		to_string<mire_ct_test_string_ghijklmnopqrstu>,
		string<'g','h','i','j','k','l','m','n','o','p','q','r','s','t','u'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

