/**
 *  .file test/mire/ct/transform.cpp
 *  .brief Test case for compile-time transform meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013-2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_transform
#include <boost/test/unit_test.hpp>

#include <mire/ct/transform.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/quote.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/instead.hpp>
#include <type_traits>
#include <memory>

BOOST_AUTO_TEST_SUITE(mire_ct_transform)

BOOST_AUTO_TEST_CASE(mire_ct_transform_range1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		transform<
			range<char, short, int const, volatile long, float*>,
			std::add_pointer<arg<0>>
		>,
		range<char*, short*, int const*, volatile long*, float**>
	>::value));

	BOOST_CHECK((equal<
		transform<
			range<char*, short*, int const*, volatile long*, float**>,
			std::remove_cv<std::remove_pointer<arg<0>>>
		>,
		range<char, short, int, long, float*>
	>::value));
}

struct mire_ct_transf_rng2_func
{
	template <typename T>
	struct apply
	{
		typedef std::shared_ptr<T> type;
	};
};

BOOST_AUTO_TEST_CASE(mire_ct_transform_range2)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		transform<
			range<char, short, int>,
			mire_ct_transf_rng2_func
		>,
		range<std::shared_ptr<char>, std::shared_ptr<short>, std::shared_ptr<int>>
	>::value));

	BOOST_CHECK((equal<
		transform<
			range<unsigned, long, float>,
			bind<mire_ct_transf_rng2_func, arg<0>>
		>,
		range<std::shared_ptr<unsigned>, std::shared_ptr<long>, std::shared_ptr<float>>
	>::value));
}

template <int Shift>
struct mire_ct_transf_str1_func
{
	template <typename Char, Char C>
	struct apply_c
	 : mire::ct::integral_constant<Char, C+Shift>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_transform_range3)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		transform<
			range<char, short, int const, volatile long, float*>,
			instead<arg<0>, void>
		>,
		range<void, void, void, void, void>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_transform_string1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		transform_c<
			string<'a','b','c','d','e','f'>,
			mire_ct_transf_str1_func<+1>
		>,
		string<'b','c','d','e','f','g'>
	>::value));

	BOOST_CHECK((equal<
		transform_c<
			string<'d','e','f','g','h','i'>,
			mire_ct_transf_str1_func<-3>
		>,
		string<'a','b','c','d','e','f'>
	>::value));
}

struct mire_ct_transf_str2_func
{
	template <typename Char, Char C>
	struct apply_c
	 : mire::ct::integral_constant<Char, C+('A'-'a')>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_transform_string2)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		transform_c<
			string<'s','t','r','i','n','g'>,
			mire_ct_transf_str2_func
		>,
		string<'S','T','R','I','N','G'>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_transform_string3)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		transform_c<
			string<'s','t','r','i','n','g'>,
			bind_c<
				quote_c<instead_c>,
				arg<0>,
				integral_constant<char, 'X'>
			>
		>,
		string<'X','X','X','X','X','X'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

