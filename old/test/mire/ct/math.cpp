/**
 *  .file test/mire/ct/math.cpp
 *  .brief Test case for compile-time math meta-functions
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_math
#include <boost/test/unit_test.hpp>

#include <mire/ct/not.hpp>
#include <mire/ct/and.hpp>
#include <mire/ct/or.hpp>
#include <mire/ct/add.hpp>
#include <mire/ct/subtract.hpp>
#include <mire/ct/multiply.hpp>
#include <mire/ct/divide.hpp>
#include <mire/ct/modulo.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_math)

BOOST_AUTO_TEST_CASE(mire_ct_math_not)
{
	using namespace mire::ct;

	BOOST_CHECK((!not_<true_type>::value));
	BOOST_CHECK(( not_<false_type>::value));

	BOOST_CHECK(( not_<not_<true_type>>::value));
	BOOST_CHECK((!not_<not_<false_type>>::value));

	BOOST_CHECK((!not_<not_<not_<true_type>>>::value));
	BOOST_CHECK(( not_<not_<not_<false_type>>>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_math_and)
{
	using namespace mire::ct;

	BOOST_CHECK(( and_<true_type>::value));
	BOOST_CHECK((!and_<false_type>::value));

	BOOST_CHECK(( and_<true_type, true_type>::value));
	BOOST_CHECK((!and_<false_type, true_type>::value));
	BOOST_CHECK((!and_<true_type, false_type>::value));
	BOOST_CHECK((!and_<false_type, false_type>::value));

	BOOST_CHECK(( and_<
		true_type,
		true_type,
		true_type,
		true_type,
		true_type,
		true_type
	>::value));

	BOOST_CHECK((!and_<
		true_type,
		true_type,
		true_type,
		true_type,
		false_type
	>::value));

	BOOST_CHECK((!and_<
		false_type,
		true_type,
		true_type,
		true_type
	>::value));

	BOOST_CHECK((!and_<
		true_type,
		false_type,
		true_type
	>::value));

	BOOST_CHECK(( and_<and_<true_type, true_type>, true_type>::value));
	BOOST_CHECK(( and_<true_type, and_<true_type, true_type>>::value));

	BOOST_CHECK((!and_<and_<false_type, true_type>, true_type>::value));
	BOOST_CHECK((!and_<and_<true_type, false_type>, true_type>::value));
	BOOST_CHECK((!and_<and_<false_type, false_type>, true_type>::value));
	BOOST_CHECK((!and_<and_<true_type, true_type>, false_type>::value));

	BOOST_CHECK((!and_<and_<false_type, true_type>, false_type>::value));
	BOOST_CHECK((!and_<and_<true_type, false_type>, false_type>::value));
	BOOST_CHECK((!and_<and_<false_type, false_type>, false_type>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_math_or)
{
	using namespace mire::ct;

	BOOST_CHECK(( or_<true_type>::value));
	BOOST_CHECK((!or_<false_type>::value));

	BOOST_CHECK(( or_<true_type, true_type>::value));
	BOOST_CHECK(( or_<false_type, true_type>::value));
	BOOST_CHECK(( or_<true_type, false_type>::value));
	BOOST_CHECK((!or_<false_type, false_type>::value));

	BOOST_CHECK((!or_<
		false_type,
		false_type,
		false_type,
		false_type,
		false_type,
		false_type
	>::value));

	BOOST_CHECK(( or_<
		true_type,
		true_type,
		true_type,
		true_type,
		false_type
	>::value));

	BOOST_CHECK(( or_<
		false_type,
		true_type,
		true_type,
		true_type
	>::value));

	BOOST_CHECK(( or_<
		true_type,
		false_type,
		true_type
	>::value));

	BOOST_CHECK(( or_<or_<false_type, true_type>, true_type>::value));
	BOOST_CHECK(( or_<or_<true_type, false_type>, true_type>::value));
	BOOST_CHECK(( or_<or_<false_type, false_type>, true_type>::value));
	BOOST_CHECK(( or_<or_<true_type, true_type>, false_type>::value));

	BOOST_CHECK(( or_<or_<false_type, true_type>, false_type>::value));
	BOOST_CHECK(( or_<or_<true_type, false_type>, false_type>::value));
	BOOST_CHECK((!or_<or_<false_type, false_type>, false_type>::value));
}

BOOST_AUTO_TEST_CASE(mire_ct_math_add)
{
	using namespace mire::ct;

	typedef integral_constant<int, 0> _0;
	typedef integral_constant<int, 1> _1;
	typedef integral_constant<int, 2> _2;
	typedef integral_constant<int, 3> _3;
	typedef integral_constant<int, 4> _4;
	typedef integral_constant<int, 5> _5;
	typedef integral_constant<int, 6> _6;
	typedef integral_constant<int, 7> _7;
	typedef integral_constant<int, 8> _8;
	typedef integral_constant<int, 9> _9;

	BOOST_CHECK((add<_0>::value == 0));
	BOOST_CHECK((add<_4>::value == 4));
	BOOST_CHECK((add<_5>::value == 5));
	BOOST_CHECK((add<_1>::value == 1));

	BOOST_CHECK((add<_0,_0>::value == 0));
	BOOST_CHECK((add<_1,_0>::value == 1));
	BOOST_CHECK((add<_1,_1>::value == 2));
	BOOST_CHECK((add<_1,_2>::value == 3));
	BOOST_CHECK((add<_2,_2>::value == 4));
	BOOST_CHECK((add<_1,_4>::value == 5));
	BOOST_CHECK((add<_3,_3>::value == 6));
	BOOST_CHECK((add<_4,_3>::value == 7));
	BOOST_CHECK((add<_4,_4>::value == 8));
	BOOST_CHECK((add<_3,_6>::value == 9));
	BOOST_CHECK((add<_5,_5>::value ==10));
	BOOST_CHECK((add<_4,_7>::value ==11));
	BOOST_CHECK((add<_6,_6>::value ==12));
	BOOST_CHECK((add<_9,_4>::value ==13));
	BOOST_CHECK((add<_7,_7>::value ==14));
	BOOST_CHECK((add<_9,_5>::value ==14));
	BOOST_CHECK((add<_8,_8>::value ==16));
	BOOST_CHECK((add<_8,_9>::value ==17));
	BOOST_CHECK((add<_9,_9>::value ==18));

	BOOST_CHECK((add<_0,_0,_0>::value == 0));
	BOOST_CHECK((add<_1,_1,_1>::value == 3));
	BOOST_CHECK((add<_0,_1,_2>::value == 3));
	BOOST_CHECK((add<_1,_2,_3>::value == 6));

	BOOST_CHECK((add<_1,_2,_3,_4>::value == 10));
	BOOST_CHECK((add<_1,_2,_3,_4,_5>::value == 15));
	BOOST_CHECK((add<_1,_2,_3,_4,_5,_6>::value == 21));
	BOOST_CHECK((add<_1,_2,_3,_4,_5,_6,_7>::value == 28));
	BOOST_CHECK((add<_1,_2,_3,_4,_5,_6,_7,_8>::value == 36));
	BOOST_CHECK((add<_1,_2,_3,_4,_5,_6,_7,_8,_9>::value == 45));
}

BOOST_AUTO_TEST_CASE(mire_ct_math_subtract)
{
	using namespace mire::ct;

	typedef integral_constant<int, 0> _0;
	typedef integral_constant<int, 1> _1;
	typedef integral_constant<int, 2> _2;
	typedef integral_constant<int, 3> _3;
	typedef integral_constant<int, 4> _4;
	typedef integral_constant<int, 5> _5;
	typedef integral_constant<int, 6> _6;
	typedef integral_constant<int, 7> _7;
	typedef integral_constant<int, 8> _8;
	typedef integral_constant<int, 9> _9;

	BOOST_CHECK((subtract<_0>::value == 0));
	BOOST_CHECK((subtract<_4>::value == 4));
	BOOST_CHECK((subtract<_5>::value == 5));
	BOOST_CHECK((subtract<_1>::value == 1));

	BOOST_CHECK((subtract<_0,_0>::value == 0));
	BOOST_CHECK((subtract<_1,_0>::value == 1));
	BOOST_CHECK((subtract<_0,_1>::value ==-1));
	BOOST_CHECK((subtract<_1,_1>::value == 0));
	BOOST_CHECK((subtract<_9,_1>::value == 8));
	BOOST_CHECK((subtract<_2,_8>::value ==-6));
	BOOST_CHECK((subtract<_3,_7>::value ==-4));
	BOOST_CHECK((subtract<_4,_6>::value ==-2));
}

BOOST_AUTO_TEST_CASE(mire_ct_math_multiply)
{
	using namespace mire::ct;

	typedef integral_constant<int, 0> _0;
	typedef integral_constant<int, 1> _1;
	typedef integral_constant<int, 2> _2;
	typedef integral_constant<int, 3> _3;
	typedef integral_constant<int, 4> _4;
	typedef integral_constant<int, 5> _5;
	typedef integral_constant<int, 6> _6;
	typedef integral_constant<int, 7> _7;
	typedef integral_constant<int, 8> _8;
	typedef integral_constant<int, 9> _9;

	BOOST_CHECK((multiply<_0,_0>::value ==  0));
	BOOST_CHECK((multiply<_4,_0>::value ==  0));
	BOOST_CHECK((multiply<_5,_0>::value ==  0));
	BOOST_CHECK((multiply<_1,_0>::value ==  0));

	BOOST_CHECK((multiply<_0,_1>::value ==  0));
	BOOST_CHECK((multiply<_4,_1>::value ==  4));
	BOOST_CHECK((multiply<_5,_1>::value ==  5));
	BOOST_CHECK((multiply<_1,_1>::value ==  1));

	BOOST_CHECK((multiply<_2,_2>::value ==  4));
	BOOST_CHECK((multiply<_2,_3>::value ==  6));
	BOOST_CHECK((multiply<_2,_6>::value == 12));
	BOOST_CHECK((multiply<_2,_7>::value == 14));

	BOOST_CHECK((multiply<_1,_3>::value ==  3));
	BOOST_CHECK((multiply<_3,_3>::value ==  9));
	BOOST_CHECK((multiply<_4,_3>::value == 12));
	BOOST_CHECK((multiply<_8,_3>::value == 24));

	BOOST_CHECK((multiply<_4,_2>::value ==  8));
	BOOST_CHECK((multiply<_4,_5>::value == 20));
	BOOST_CHECK((multiply<_4,_8>::value == 32));
	BOOST_CHECK((multiply<_4,_9>::value == 36));

	BOOST_CHECK((multiply<_2,_5>::value == 10));
	BOOST_CHECK((multiply<_3,_5>::value == 15));
	BOOST_CHECK((multiply<_7,_5>::value == 35));
	BOOST_CHECK((multiply<_8,_5>::value == 40));

	BOOST_CHECK((multiply<_1,_1,_1,_1>::value ==  1));
	BOOST_CHECK((multiply<_2,_2,_2,_2,_2>::value == 32));
	BOOST_CHECK((multiply<_1,_2,_3,_4,_5,_6>::value == 720));
}

BOOST_AUTO_TEST_CASE(mire_ct_math_divide)
{
	using namespace mire::ct;

	typedef integral_constant<int, 0> _0;
	typedef integral_constant<int, 1> _1;
	typedef integral_constant<int, 2> _2;
	typedef integral_constant<int, 3> _3;
	typedef integral_constant<int, 4> _4;
	typedef integral_constant<int, 5> _5;
	typedef integral_constant<int, 6> _6;
	typedef integral_constant<int, 7> _7;
	typedef integral_constant<int, 8> _8;
	typedef integral_constant<int, 9> _9;

	BOOST_CHECK((divide<_0,_1>::value ==  0));
	BOOST_CHECK((divide<_3,_1>::value ==  3));
	BOOST_CHECK((divide<_7,_1>::value ==  7));
	BOOST_CHECK((divide<_9,_1>::value ==  9));

	BOOST_CHECK((divide<_4,_3>::value ==  1));
	BOOST_CHECK((divide<_3,_4>::value ==  0));
	BOOST_CHECK((divide<_6,_3>::value ==  2));
	BOOST_CHECK((divide<_7,_3>::value ==  2));

	BOOST_CHECK((divide<_8,_2>::value ==  4));
	BOOST_CHECK((divide<_9,_2>::value ==  4));
	BOOST_CHECK((divide<_9,_3>::value ==  3));
	BOOST_CHECK((divide<_9,_5>::value ==  1));
}

BOOST_AUTO_TEST_CASE(mire_ct_math_modulo)
{
	using namespace mire::ct;

	typedef integral_constant<int, 0> _0;
	typedef integral_constant<int, 1> _1;
	typedef integral_constant<int, 2> _2;
	typedef integral_constant<int, 3> _3;
	typedef integral_constant<int, 4> _4;
	typedef integral_constant<int, 5> _5;
	typedef integral_constant<int, 6> _6;
	typedef integral_constant<int, 7> _7;
	typedef integral_constant<int, 8> _8;
	typedef integral_constant<int, 9> _9;

	BOOST_CHECK((modulo<_0,_1>::value ==  0));
	BOOST_CHECK((modulo<_1,_1>::value ==  0));
	BOOST_CHECK((modulo<_3,_1>::value ==  0));

	BOOST_CHECK((modulo<_1,_2>::value ==  1));
	BOOST_CHECK((modulo<_2,_2>::value ==  0));
	BOOST_CHECK((modulo<_3,_2>::value ==  1));

	BOOST_CHECK((modulo<_1,_3>::value ==  1));
	BOOST_CHECK((modulo<_2,_3>::value ==  2));
	BOOST_CHECK((modulo<_3,_3>::value ==  0));
	BOOST_CHECK((modulo<_5,_3>::value ==  2));
}

BOOST_AUTO_TEST_SUITE_END()

