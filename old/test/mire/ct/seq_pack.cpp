/**
 *  .file test/mire/ct/seq_pack.cpp
 *  .brief Test case for compile-time seq_pack meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_seq_pack
#include <boost/test/unit_test.hpp>

#include <mire/ct/seq_pack.hpp>
#include <mire/ct/string.hpp>
#include <mire/ct/compare.hpp>
#include <cstring>

BOOST_AUTO_TEST_SUITE(mire_ct_seq_pack)

template <size_t U>
struct mire_ct_seq_pack_rng_fn
{
	template <size_t ... I>
	struct apply
	 : mire::ct::range<mire::ct::integral_constant<size_t, U+I>...>
	{ };
};

template <char C>
struct mire_ct_seq_pack_str_fn
{
	template <size_t ... I>
	struct apply
	 : mire::ct::string<char(C+I)...>
	{ };
};

BOOST_AUTO_TEST_CASE(mire_ct_seq_pack_range)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> _0;
	typedef integral_constant<size_t, 1> _1;
	typedef integral_constant<size_t, 2> _2;
	typedef integral_constant<size_t, 3> _3;
	typedef integral_constant<size_t, 4> _4;
	typedef integral_constant<size_t, 5> _5;
	typedef integral_constant<size_t, 6> _6;
	typedef integral_constant<size_t, 7> _7;
	typedef integral_constant<size_t, 8> _8;
	typedef integral_constant<size_t, 9> _9;

	BOOST_CHECK((equal<
		apply_on_seq_pack<mire_ct_seq_pack_rng_fn<0>, _0>,
		range<>
	>::value));

	BOOST_CHECK((equal<
		apply_on_seq_pack<mire_ct_seq_pack_rng_fn<0>, _4>,
		range<_0, _1, _2, _3>
	>::value));

	BOOST_CHECK((equal<
		apply_on_seq_pack<mire_ct_seq_pack_rng_fn<2>, _6>,
		range<_2, _3, _4, _5, _6, _7>
	>::value));

	BOOST_CHECK((equal<
		apply_on_seq_pack<mire_ct_seq_pack_rng_fn<1>, _9>,
		range<_1, _2, _3, _4, _5, _6, _7, _8, _9>
	>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_seq_pack_string)
{
	using namespace mire::ct;

	BOOST_CHECK((equal<
		apply_on_seq_pack_c<mire_ct_seq_pack_str_fn<'A'>, 0>,
		string<>
	>::value));

	BOOST_CHECK((equal<
		apply_on_seq_pack_c<mire_ct_seq_pack_str_fn<'A'>, 3>,
		string<'A','B','C'>
	>::value));

	BOOST_CHECK((equal<
		apply_on_seq_pack_c<mire_ct_seq_pack_str_fn<'C'>, 9>,
		string<'C','D','E','F','G','H','I','J','K'>
	>::value));

	BOOST_CHECK((equal<
		apply_on_seq_pack_c<mire_ct_seq_pack_str_fn<'E'>, 15>,
		string<'E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S'>
	>::value));
}

BOOST_AUTO_TEST_SUITE_END()

