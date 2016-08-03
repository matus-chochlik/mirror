/**
 *  .file test/mire/ct/slice.cpp
 *  .brief Test case for compile-time slice meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_slice
#include <boost/test/unit_test.hpp>

#include <mire/ct/slice.hpp>
#include <mire/ct/compare.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_slice)

BOOST_AUTO_TEST_CASE(mire_ct_slice_range)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> _0;
	typedef integral_constant<size_t, 1> _1;
	typedef integral_constant<size_t, 2> _2;
	typedef integral_constant<size_t, 3> _3;
	typedef integral_constant<size_t, 4> _4;
	typedef integral_constant<size_t, 5> _5;

	typedef range<bool, char, short, int, long, float> r0_6;
	typedef range<bool, char, short, int, long> r0_5;
	typedef range<bool, char, short, int> r0_4;
	typedef range<bool, char, short> r0_3;
	typedef range<bool, char> r0_2;
	typedef range<bool> r0_1;
	typedef range<> r0_0;
	typedef range<char, short, int, long, float> r1_5;
	typedef range<char, short, int, long> r1_4;
	typedef range<char, short, int> r1_3;
	typedef range<char, short> r1_2;
	typedef range<char> r1_1;
	typedef range<short, int, long, float> r2_4;
	typedef range<short, int, long> r2_3;
	typedef range<short, int> r2_2;
	typedef range<short> r2_1;
	typedef range<int, long, float> r3_3;
	typedef range<int, long> r3_2;
	typedef range<int> r3_1;
	typedef range<long, float> r4_2;
	typedef range<long> r4_1;
	typedef range<float> r5_1;

	BOOST_CHECK((equal<slice<r0_6, _0, _5>, r0_5>::value));
	BOOST_CHECK((equal<slice<r0_6, _0, _4>, r0_4>::value));
	BOOST_CHECK((equal<slice<r0_6, _0, _3>, r0_3>::value));
	BOOST_CHECK((equal<slice<r0_6, _0, _2>, r0_2>::value));
	BOOST_CHECK((equal<slice<r0_6, _0, _1>, r0_1>::value));
	BOOST_CHECK((equal<slice<r0_6, _0, _0>, r0_0>::value));

	BOOST_CHECK((equal<slice<r0_6, _1, _5>, r1_5>::value));
	BOOST_CHECK((equal<slice<r0_6, _1, _4>, r1_4>::value));
	BOOST_CHECK((equal<slice<r0_6, _1, _3>, r1_3>::value));
	BOOST_CHECK((equal<slice<r0_6, _1, _2>, r1_2>::value));
	BOOST_CHECK((equal<slice<r0_6, _1, _1>, r1_1>::value));

	BOOST_CHECK((equal<slice<r0_6, _2, _4>, r2_4>::value));
	BOOST_CHECK((equal<slice<r0_6, _2, _3>, r2_3>::value));
	BOOST_CHECK((equal<slice<r0_6, _2, _2>, r2_2>::value));
	BOOST_CHECK((equal<slice<r0_6, _2, _1>, r2_1>::value));

	BOOST_CHECK((equal<slice<r0_6, _3, _3>, r3_3>::value));
	BOOST_CHECK((equal<slice<r0_6, _3, _2>, r3_2>::value));
	BOOST_CHECK((equal<slice<r0_6, _3, _1>, r3_1>::value));

	BOOST_CHECK((equal<slice<r0_6, _4, _2>, r4_2>::value));
	BOOST_CHECK((equal<slice<r0_6, _4, _1>, r4_1>::value));

	BOOST_CHECK((equal<slice<r0_6, _5, _1>, r5_1>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_slice_string)
{
	using namespace mire::ct;

	typedef integral_constant<size_t, 0> _0;
	typedef integral_constant<size_t, 1> _1;
	typedef integral_constant<size_t, 2> _2;
	typedef integral_constant<size_t, 3> _3;
	typedef integral_constant<size_t, 4> _4;
	typedef integral_constant<size_t, 5> _5;

	typedef string<'s','t','r','i','n','g'> s0_6;
	typedef string<'s','t','r','i','n'> s0_5;
	typedef string<'s','t','r','i'> s0_4;
	typedef string<'s','t','r'> s0_3;
	typedef string<'s','t'> s0_2;
	typedef string<'s'> s0_1;
	typedef string<> s0_0;
	typedef string<'t','r','i','n','g'> s1_5;
	typedef string<'t','r','i','n'> s1_4;
	typedef string<'t','r','i'> s1_3;
	typedef string<'t','r'> s1_2;
	typedef string<'t'> s1_1;
	typedef string<'r','i','n','g'> s2_4;
	typedef string<'r','i','n'> s2_3;
	typedef string<'r','i'> s2_2;
	typedef string<'r'> s2_1;
	typedef string<'i','n','g'> s3_3;
	typedef string<'i','n'> s3_2;
	typedef string<'i'> s3_1;
	typedef string<'n','g'> s4_2;
	typedef string<'n'> s4_1;
	typedef string<'g'> s5_1;

	BOOST_CHECK((equal<slice<s0_6, _0, _5>, s0_5>::value));
	BOOST_CHECK((equal<slice<s0_6, _0, _4>, s0_4>::value));
	BOOST_CHECK((equal<slice<s0_6, _0, _3>, s0_3>::value));
	BOOST_CHECK((equal<slice<s0_6, _0, _2>, s0_2>::value));
	BOOST_CHECK((equal<slice<s0_6, _0, _1>, s0_1>::value));
	BOOST_CHECK((equal<slice<s0_6, _0, _0>, s0_0>::value));

	BOOST_CHECK((equal<slice<s0_6, _1, _5>, s1_5>::value));
	BOOST_CHECK((equal<slice<s0_6, _1, _4>, s1_4>::value));
	BOOST_CHECK((equal<slice<s0_6, _1, _3>, s1_3>::value));
	BOOST_CHECK((equal<slice<s0_6, _1, _2>, s1_2>::value));
	BOOST_CHECK((equal<slice<s0_6, _1, _1>, s1_1>::value));

	BOOST_CHECK((equal<slice<s0_6, _2, _4>, s2_4>::value));
	BOOST_CHECK((equal<slice<s0_6, _2, _3>, s2_3>::value));
	BOOST_CHECK((equal<slice<s0_6, _2, _2>, s2_2>::value));
	BOOST_CHECK((equal<slice<s0_6, _2, _1>, s2_1>::value));

	BOOST_CHECK((equal<slice<s0_6, _3, _3>, s3_3>::value));
	BOOST_CHECK((equal<slice<s0_6, _3, _2>, s3_2>::value));
	BOOST_CHECK((equal<slice<s0_6, _3, _1>, s3_1>::value));

	BOOST_CHECK((equal<slice<s0_6, _4, _2>, s4_2>::value));
	BOOST_CHECK((equal<slice<s0_6, _4, _1>, s4_1>::value));

	BOOST_CHECK((equal<slice<s0_6, _5, _1>, s5_1>::value));
}

BOOST_AUTO_TEST_SUITE_END()

