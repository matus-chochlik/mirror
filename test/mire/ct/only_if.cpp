/**
 *  .file test/mire/ct/only_if.cpp
 *  .brief Test case for compile-time if_ meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_if
#include <boost/test/unit_test.hpp>

#include <mire/ct/only_if.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/not.hpp>
#include <type_traits>

BOOST_AUTO_TEST_SUITE(mire_ct_only_if)

BOOST_AUTO_TEST_CASE(mire_ct_only_if1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		only_if<
			range<bool, char, short, float, double, int>,
			std::is_integral<arg<0>>
		>,
		range<bool, char, short, int>
	>::value));

	BOOST_CHECK((equal<
		only_if<
			range<bool, char, short, float, double, int>,
			std::is_floating_point<arg<0>>
		>,
		range<float, double>
	>::value));

	BOOST_CHECK((equal<
		only_if<
			range<bool, char*, short, float*, double, int>,
			not_<std::is_pointer<arg<0>>>
		>,
		range<bool, short, double, int>
	>::value));

	BOOST_CHECK((equal<
		only_if<
			range<bool, char*, short, float*, double, int>,
			and_<not_<std::is_pointer<arg<0>>>,not_<std::is_integral<arg<0>>>>
		>,
		range<double>
	>::value));
}

struct mire_ct_only_if2_func
{
	template <typename Char, Char C>
	struct apply_c
	 : mire::ct::integral_constant<bool, C != ' '>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_only_if2)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		only_if<
			string<'S',' ','t',' ','r',' ','i',' ','n',' ','g'>,
			mire_ct_only_if2_func
		>,
		string<'S','t','r','i','n','g'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

