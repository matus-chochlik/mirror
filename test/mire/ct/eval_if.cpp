/**
 *  .file test/mire/ct/eval_if.cpp
 *  .brief Test case for compile-time if_ meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_eval_if
#include <boost/test/unit_test.hpp>

#include <mire/ct/string.hpp>
#include <mire/ct/range.hpp>
#include <mire/ct/eval_if.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/front.hpp>
#include <mire/ct/nil_type.hpp>
#include <mire/ct/traits.hpp>
#include <mire/ct/c_str.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_eval_if)

BOOST_AUTO_TEST_CASE(mire_ct_eval_if1)
{
	using namespace mire::ct;

	typedef string<'N','/','A'> n_a;
	typedef string<'s','t','r','i','n','g'> x1;
	typedef range<bool, short, int, long> x2;

	BOOST_CHECK(std::strcmp(
		eval_if<is_string<x1>, c_str<x1>, c_str<n_a>>::value,
		"string"
	) == 0);

	BOOST_CHECK(std::strcmp(
		eval_if<is_string<x2>, c_str<x2>, c_str<n_a>>::value,
		"N/A"
	) == 0);

	BOOST_CHECK((equal_types<
		eval_if<is_range<x1>, front<x1>, nil_t>,
		nil_t
	>::value));

	BOOST_CHECK((equal_types<
		eval_if<is_range<x2>, front<x2>, nil_t>,
		bool
	>::value));

	BOOST_CHECK((!equal_types<
		eval_if<is_range<x1>, front<x1>, nil_t>,
		bool
	>::value));

	BOOST_CHECK((!equal_types<
		eval_if<is_range<x2>, front<x2>, nil_t>,
		nil_t
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

