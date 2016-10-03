/**
 *  .file test/mire/ct/traits.cpp
 *  .brief Test case for compile-time traits
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_traits
#include <boost/test/unit_test.hpp>

#include <mire/ct/traits.hpp>
#include <mire/ct/head.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_traits)

BOOST_AUTO_TEST_CASE(mire_ct_traits_is_range)
{
	using namespace mire::ct;

	BOOST_CHECK(( is_range<range<bool, char, short, int, long, unsigned>>::value));
	BOOST_CHECK(( is_range<head_c<range<char, short, long>, 2>>::value));
	BOOST_CHECK(( is_range<empty_range>::value));
	BOOST_CHECK((!is_range<string<'A','B','C','D','E'>>::value));
	BOOST_CHECK((!is_range<head_c<string<'A','B','C'>, 2>>::value));
	BOOST_CHECK((!is_range<basic_string<char, 'X','Y'>>::value));
	BOOST_CHECK((!is_range<empty_string>::value));
	BOOST_CHECK((!is_range<optional<long>>::value));
	BOOST_CHECK((!is_range<empty_optional>::value));
	BOOST_CHECK((!is_range<nil_t>::value));
	BOOST_CHECK((!is_range<double>::value));
	BOOST_CHECK((!is_range<void>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_traits_is_string)
{
	using namespace mire::ct;

	BOOST_CHECK((!is_string<range<bool, char, short, int, long, unsigned>>::value));
	BOOST_CHECK((!is_string<head_c<range<char, short, long>, 2>>::value));
	BOOST_CHECK((!is_string<empty_range>::value));
	BOOST_CHECK(( is_string<string<'A','B','C','D','E'>>::value));
	BOOST_CHECK(( is_string<head_c<string<'A','B','C'>, 2>>::value));
	BOOST_CHECK(( is_string<basic_string<char, 'X','Y'>>::value));
	BOOST_CHECK(( is_string<empty_string>::value));
	BOOST_CHECK((!is_string<optional<long>>::value));
	BOOST_CHECK((!is_string<empty_optional>::value));
	BOOST_CHECK((!is_string<nil_t>::value));
	BOOST_CHECK((!is_string<double>::value));
	BOOST_CHECK((!is_string<void>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_traits_is_optional)
{
	using namespace mire::ct;

	BOOST_CHECK((!is_optional<range<bool, char, short, int, long, unsigned>>::value));
	BOOST_CHECK((!is_optional<head_c<range<char, short, long>, 2>>::value));
	BOOST_CHECK((!is_optional<empty_range>::value));
	BOOST_CHECK((!is_optional<string<'A','B','C','D','E'>>::value));
	BOOST_CHECK((!is_optional<head_c<string<'A','B','C'>, 2>>::value));
	BOOST_CHECK((!is_optional<basic_string<char, 'X','Y'>>::value));
	BOOST_CHECK((!is_optional<empty_string>::value));
	BOOST_CHECK(( is_optional<optional<long>>::value));
	BOOST_CHECK(( is_optional<empty_optional>::value));
	BOOST_CHECK((!is_optional<nil_t>::value));
	BOOST_CHECK((!is_optional<double>::value));
	BOOST_CHECK((!is_optional<void>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_traits_is_nil_t)
{
	using namespace mire::ct;

	BOOST_CHECK((!is_nil_t<range<bool, char, short, int, long, unsigned>>::value));
	BOOST_CHECK((!is_nil_t<head_c<range<char, short, long>, 2>>::value));
	BOOST_CHECK((!is_nil_t<empty_range>::value));
	BOOST_CHECK((!is_nil_t<string<'A','B','C','D','E'>>::value));
	BOOST_CHECK((!is_nil_t<head_c<string<'A','B','C'>, 2>>::value));
	BOOST_CHECK((!is_nil_t<basic_string<char, 'X','Y'>>::value));
	BOOST_CHECK((!is_nil_t<empty_string>::value));
	BOOST_CHECK((!is_nil_t<optional<long>>::value));
	BOOST_CHECK((!is_nil_t<empty_optional>::value));
	//BOOST_CHECK(( is_nil_t<nil_t>::value)); TODO
	BOOST_CHECK((!is_nil_t<double>::value));
	BOOST_CHECK((!is_nil_t<void>::value));
}

BOOST_AUTO_TEST_SUITE_END()

