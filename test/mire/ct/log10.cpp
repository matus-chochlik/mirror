/**
 *  .file test/mire/ct/log10.cpp
 *  .brief Test case for compile-time log10 meta-function
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_log10
#include <boost/test/unit_test.hpp>

#include <mire/ct/log10.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_log10)

BOOST_AUTO_TEST_CASE(mire_ct_log10_test1)
{
	using namespace mire;

	BOOST_CHECK((ct::log10<ct::integral_constant<int,       1>>::value ==  0));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,       2>>::value ==  0));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,       4>>::value ==  0));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,       8>>::value ==  0));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,      10>>::value ==  1));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,      13>>::value ==  1));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,      35>>::value ==  1));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,      57>>::value ==  1));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,      79>>::value ==  1));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,      99>>::value ==  1));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,     100>>::value ==  2));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,     123>>::value ==  2));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,     999>>::value ==  2));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,    1000>>::value ==  3));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,    1234>>::value ==  3));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,    9999>>::value ==  3));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,    9999>>::value ==  3));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,   10000>>::value ==  4));
	BOOST_CHECK((ct::log10<ct::integral_constant<int,  100000>>::value ==  5));
	BOOST_CHECK((ct::log10<ct::integral_constant<int, 1000000>>::value ==  6));
}

BOOST_AUTO_TEST_CASE(mire_ct_log10_test2)
{
	using namespace mire;
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 1000000>>::value ==  6));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 10000000>>::value ==  7));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 100000000>>::value ==  8));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 1000000000>>::value ==  9));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 10000000000>>::value == 10));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 100000000000>>::value == 11));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 1000000000000>>::value == 12));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 10000000000000>>::value == 13));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 100000000000000>>::value == 14));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 1000000000000000>>::value == 15));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 10000000000000000>>::value == 16));
	BOOST_CHECK((ct::log10<ct::integral_constant<long long, 100000000000000000>>::value == 17));
}

BOOST_AUTO_TEST_SUITE_END()

