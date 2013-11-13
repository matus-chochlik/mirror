/**
 *  .file test/mire/ct/fold.cpp
 *  .brief Test case for compile-time fold meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_fold
#include <boost/test/unit_test.hpp>

#include <mire/ct/fold.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/append.hpp>
#include <mire/ct/prepend.hpp>
#include <type_traits>

BOOST_AUTO_TEST_SUITE(mire_ct_fold)

struct mire_ct_fold_range1_func
{
	template <typename Status, typename T>
	struct apply
	 : mire::ct::integral_constant<
		mire::ct::size_t,
		Status::value+sizeof(T)
	>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_fold_range1)
{
	using namespace mire::ct;

	BOOST_CHECK((fold<
		range<char>,
		integral_constant<size_t, 0>,
		mire_ct_fold_range1_func
	>::value == sizeof(char)));

	BOOST_CHECK((fold<
		range<char, char>,
		integral_constant<size_t, 0>,
		mire_ct_fold_range1_func
	>::value == sizeof(char)+sizeof(char)));

	BOOST_CHECK((fold<
		range<bool, char, short, int, long, float>,
		integral_constant<size_t, 0>,
		mire_ct_fold_range1_func
	>::value==sizeof(bool)+sizeof(char)+sizeof(short)+sizeof(int)+sizeof(long)+sizeof(float)));
}

BOOST_AUTO_TEST_CASE(mire_ct_fold_range2)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		fold<
			range<char, short, int, long, float, double>,
			empty_range,
			append<arg<0>, arg<1>>
		>,
		range<char, short, int, long, float, double>
	>::value));

	BOOST_CHECK((equal<
		fold<
			range<char, short, int, long, float, double>,
			empty_range,
			prepend<arg<0>, arg<1>>
		>,
		range<double, float, long, int, short, char>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

