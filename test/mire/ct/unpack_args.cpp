/**
 *  .file test/mire/ct/unpack_args.cpp
 *  .brief Test case for compile-time unpack_args meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_unpack_args
#include <boost/test/unit_test.hpp>

#include <mire/ct/unpack_args.hpp>
#include <mire/ct/compare.hpp>
#include <mire/ct/lambda.hpp>
#include <mire/ct/add.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_unpack_args)

struct mire_ct_unpack_args_test1_func
{
	template <typename ... T>
	struct apply
	 : mire::ct::integral_constant<size_t, sizeof...(T)>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_unpack_args_test1)
{
	using namespace mire::ct;

	BOOST_CHECK((
		unpack_args<mire_ct_unpack_args_test1_func>::
		apply<empty_range>::value == 0
	));

	BOOST_CHECK((
		unpack_args<mire_ct_unpack_args_test1_func>::
		apply<range<unsigned>>::value == 1
	));

	BOOST_CHECK((
		unpack_args<mire_ct_unpack_args_test1_func>::
		apply<range<short, unsigned>>::value == 2
	));

	BOOST_CHECK((
		unpack_args<mire_ct_unpack_args_test1_func>::
		apply<range<short, long, unsigned>>::value == 3
	));

	BOOST_CHECK((
		unpack_args<mire_ct_unpack_args_test1_func>::
		apply<range<char, short, long, unsigned>>::value == 4
	));

	BOOST_CHECK((
		unpack_args<mire_ct_unpack_args_test1_func>::
		apply<range<char, short, int, long, unsigned>>::value == 5
	));
}

BOOST_AUTO_TEST_CASE(mire_ct_unpack_args_test2)
{
	using namespace mire::ct;

	BOOST_CHECK((apply<
		unpack_args<mire_ct_unpack_args_test1_func>,
		empty_range
	>::value == 0));

	BOOST_CHECK((apply<
		unpack_args<mire_ct_unpack_args_test1_func>,
		range<long>
	>::value == 1));

	BOOST_CHECK((apply<
		unpack_args<mire_ct_unpack_args_test1_func>,
		range<int, long>
	>::value == 2));

	BOOST_CHECK((apply<
		unpack_args<mire_ct_unpack_args_test1_func>,
		range<char, int, long>
	>::value == 3));

	BOOST_CHECK((apply<
		unpack_args<mire_ct_unpack_args_test1_func>,
		range<char, short, int, long>
	>::value == 4));

	BOOST_CHECK((apply<
		unpack_args<mire_ct_unpack_args_test1_func>,
		range<char, short, int, long, unsigned>
	>::value == 5));
}

struct mire_ct_unpack_args_test3_func
{
	template <typename ... T>
	struct apply
	 : mire::ct::add<mire::ct::integral_constant<size_t, sizeof(T)>...>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_unpack_args_test3)
{
	using namespace mire::ct;

	BOOST_CHECK((apply<
		unpack_args<mire_ct_unpack_args_test3_func>,
		range<char, short, int, long>
	>::value == sizeof(char)+sizeof(short)+sizeof(int)+sizeof(long)));
}

struct mire_ct_unpack_args_test4_func
{
	template <typename Char, Char ... C>
	struct apply_c
	 : mire::ct::basic_string<wchar_t, wchar_t(C)...>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_unpack_args_test4)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		apply_c<
			unpack_args_c<mire_ct_unpack_args_test4_func>,
			string<'A','B','C','D','E'>
		>,
		basic_string<wchar_t,L'A',L'B',L'C',L'D',L'E'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

