/**
 *  .file test/mire/ct/exp.cpp
 *  .brief Test case for compile-time exp10 meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_exp
#include <boost/test/unit_test.hpp>

#include <mire/ct/exp.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_exp)

BOOST_AUTO_TEST_CASE(mire_ct_exp10_test1)
{
	using namespace mire;

	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 0>>::value ==  1));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 1>>::value ==  10));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 2>>::value ==  100));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 3>>::value ==  1000));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 4>>::value ==  10000));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 5>>::value ==  100000));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 6>>::value ==  1000000));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 7>>::value ==  10000000));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 8>>::value ==  100000000));
	BOOST_CHECK((ct::exp10<ct::integral_constant<int, 9>>::value ==  1000000000));
}

BOOST_AUTO_TEST_CASE(mire_ct_exp10_test2)
{
	using namespace mire;

	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 10>>::value==10000000000ll));
	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 11>>::value==100000000000ll));
	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 12>>::value==1000000000000ll));
	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 13>>::value==10000000000000ll));
	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 14>>::value==100000000000000ll));
	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 15>>::value==1000000000000000ll));
	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 16>>::value==10000000000000000ll));
	BOOST_CHECK((ct::exp10<ct::integral_constant<long long, 17>>::value==100000000000000000ll));
}

BOOST_AUTO_TEST_SUITE_END()

