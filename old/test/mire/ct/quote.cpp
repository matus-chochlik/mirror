/**
 *  .file test/mire/ct/quote.cpp
 *  .brief Test case for compile-time quote expressions
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_quote
#include <boost/test/unit_test.hpp>

#include <mire/ct/quote.hpp>
#include <mire/ct/compare.hpp>

#include <type_traits>

BOOST_AUTO_TEST_SUITE(mire_ct_quote)

BOOST_AUTO_TEST_CASE(mire_ct_quote_test1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		quote<std::add_pointer>::apply<bool>,
		bool*
	>::value));

	BOOST_CHECK((equal_types<
		quote<std::remove_cv>::apply<const double>,
		double
	>::value));

	BOOST_CHECK(( quote<std::is_same>::apply<double,double>::value));
	BOOST_CHECK((!quote<std::is_same>::apply<double, float>::value));
}

template <typename Char, Char A, Char B>
struct mire_ct_quote_test2_func
 : mire::ct::integral_constant<bool, A == B>
{ };

BOOST_AUTO_TEST_CASE(mire_ct_quote_test2)
{
	using namespace mire::ct;

	BOOST_CHECK(( quote_c<mire_ct_quote_test2_func>::apply_c<char, 'A', 'A'>::value));
	BOOST_CHECK((!quote_c<mire_ct_quote_test2_func>::apply_c<char, 'A', 'B'>::value));
}

template <typename Char, Char A, Char B, Char C>
struct mire_ct_quote_test3_func
 : mire::ct::integral_constant<bool, (A == B) == (B == C)>
{ };

BOOST_AUTO_TEST_CASE(mire_ct_quote_test3)
{
	using namespace mire::ct;

	BOOST_CHECK(( quote_c<mire_ct_quote_test3_func>::apply_c<char, 'A', 'A', 'A'>::value));
	BOOST_CHECK((!quote_c<mire_ct_quote_test3_func>::apply_c<char, 'A', 'A', 'B'>::value));
	BOOST_CHECK((!quote_c<mire_ct_quote_test3_func>::apply_c<char, 'A', 'B', 'B'>::value));
	BOOST_CHECK(( quote_c<mire_ct_quote_test3_func>::apply_c<char, 'B', 'B', 'B'>::value));
	BOOST_CHECK((!quote_c<mire_ct_quote_test3_func>::apply_c<char, 'B', 'B', 'A'>::value));
	BOOST_CHECK((!quote_c<mire_ct_quote_test3_func>::apply_c<char, 'B', 'A', 'A'>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_quote_test4)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		quote_c<basic_string>::apply_c<char, 'a','b','c','d','e','f'>,
		string<'a','b','c','d','e','f'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

