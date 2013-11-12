/**
 *  .file test/mire/ct/lambda.cpp
 *  .brief Test case for compile-time lambda expressions
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_lambda
#include <boost/test/unit_test.hpp>

#include <mire/ct/lambda.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/and.hpp>
#include <mire/ct/not.hpp>

#include <type_traits>

BOOST_AUTO_TEST_SUITE(mire_ct_lambda)

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test1)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		apply<arg<0>, bool, char, short, int, long, float>,
		bool
	>::value));

	BOOST_CHECK((equal_types<
		apply<arg<1>, bool, char, short, int, long, float>,
		char
	>::value));

	BOOST_CHECK((equal_types<
		apply<arg<2>, bool, char, short, int, long, float>,
		short
	>::value));

	BOOST_CHECK((equal_types<
		apply<arg<3>, bool, char, short, int, long, float>,
		int
	>::value));

	BOOST_CHECK((equal_types<
		apply<arg<4>, bool, char, short, int, long, float>,
		long
	>::value));

	BOOST_CHECK((equal_types<
		apply<arg<5>, bool, char, short, int, long, float>,
		float
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test2)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		apply<std::add_pointer<arg<0>>, char, short, long, float>,
		char*
	>::value));

	BOOST_CHECK((equal_types<
		apply<std::add_const<arg<3>>, char, short, long, float>,
		float const
	>::value));

	BOOST_CHECK((equal_types<
		apply<std::add_pointer<std::add_const<arg<2>>>, char, short, long, float>,
		long const *
	>::value));

	BOOST_CHECK((equal_types<
		apply<std::add_const<std::add_pointer<arg<1>>>, char, short, long, float>,
		short * const
	>::value));

	BOOST_CHECK((equal_types<
		apply<std::add_const<std::add_pointer<std::add_volatile<arg<0>>>>, char, short>,
		char volatile * const
	>::value));

	BOOST_CHECK((equal_types<
		apply<std::add_const<char>, bool, short, long, float>,
		char const
	>::value));
}

struct mire_ct_lambda_test3_hlpr
{
	template <typename T>
	struct apply
	{
		typedef T const * const * type;
	};
};

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test3)
{
	using namespace mire::ct;

	BOOST_CHECK((equal_types<
		apply<mire_ct_lambda_test3_hlpr, double>,
		double const * const *
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test4)
{
	using namespace mire::ct;

	BOOST_CHECK((apply<
		equal_types<
			std::add_pointer<arg<0>>,
			std::remove_pointer<arg<1>>,
			std::remove_const<arg<2>>
		>,
		double,
		double**,
		double* const
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test5)
{
	using namespace mire::ct;

	BOOST_CHECK((apply<
		and_<
			equal_types<arg<0>, std::add_pointer<arg<1>>>,
			equal_types<arg<0>, std::remove_pointer<arg<2>>>,
			equal_types<arg<0>, std::remove_const<arg<3>>>,
			equal_types<arg<1>, std::remove_reference<arg<4>>>,
			equal_types<arg<1>, std::remove_volatile<arg<5>>>
		>,
		long*
		long,
		long**,
		long* const,
		long&,
		long volatile
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test6)
{
	using namespace mire::ct;

	BOOST_CHECK((
		apply_c<arg<0>, char, 'A', 'B', 'C', 'D', 'E', 'F'>::value == 'A'
	));

	BOOST_CHECK((
		apply_c<arg<1>, char, 'A', 'B', 'C', 'D', 'E', 'F'>::value == 'B'
	));

	BOOST_CHECK((
		apply_c<arg<2>, char, 'A', 'B', 'C', 'D', 'E', 'F'>::value == 'C'
	));

	BOOST_CHECK((
		apply_c<arg<3>, char, 'A', 'B', 'C', 'D', 'E', 'F'>::value == 'D'
	));

	BOOST_CHECK((
		apply_c<arg<4>, char, 'A', 'B', 'C', 'D', 'E', 'F'>::value == 'E'
	));

	BOOST_CHECK((
		apply_c<arg<5>, char, 'A', 'B', 'C', 'D', 'E', 'F'>::value == 'F'
	));
}

template <int Shift>
struct mire_ct_lambda_test7_func
{
	template <typename Char, Char C>
	struct apply_c
	 : mire::ct::integral_constant<Char, Char(C+Shift)>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test7)
{
	using namespace mire::ct;

	BOOST_CHECK((
		apply_c<mire_ct_lambda_test7_func< 0>, char, 'A'>::value == 'A'
	));

	BOOST_CHECK((
		apply_c<mire_ct_lambda_test7_func< 1>, char, 'A'>::value == 'B'
	));

	BOOST_CHECK((
		apply_c<mire_ct_lambda_test7_func<-1>, char, 'B'>::value == 'A'
	));
}

struct mire_ct_lambda_test8_func
{
	template <typename Char, Char C1, Char C2>
	struct apply_c
	 : mire::ct::integral_constant<bool, C1 == C2>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_lambda_test8)
{
	using namespace mire::ct;

	BOOST_CHECK((apply_c<mire_ct_lambda_test8_func, char, 'A', 'A'>::value));

	typedef integral_constant<char, 'X'> _X;
	typedef integral_constant<char, 'Y'> _Y;
	typedef integral_constant<char, 'Z'> _Z;

	BOOST_CHECK((apply_c<
		bind_c<mire_ct_lambda_test8_func, arg<0>, _X>, char, 'X'
	>::value));

	BOOST_CHECK((apply_c<
		not_<bind_c<mire_ct_lambda_test8_func, arg<0>, _X>>, char, 'Y'
	>::value));

	BOOST_CHECK((apply_c<
		and_<
			bind_c<mire_ct_lambda_test8_func, arg<0>, _X>,
			bind_c<mire_ct_lambda_test8_func, arg<1>, _Y>,
			bind_c<mire_ct_lambda_test8_func, arg<2>, _Z>
		>, char, 'X', 'Y', 'Z'
	>::value));

	BOOST_CHECK((apply_c<
		and_<
			not_<bind_c<mire_ct_lambda_test8_func, arg<0>, _X>>,
			not_<bind_c<mire_ct_lambda_test8_func, arg<1>, _Y>>,
			not_<bind_c<mire_ct_lambda_test8_func, arg<2>, _Z>>
		>, char, 'A', 'B', 'C'
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

