/**
 *  .file test/mire/ct_counter/basic.cpp
 *  .brief Test case for basic compile-time counter usage
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2014 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_COUNTER_basic
#include <boost/test/unit_test.hpp>

#include <mire/ct_counter.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_counter_basic)

MIRE_CT_COUNTER_ENABLE()

struct test_1 { };
MIRE_CT_COUNTER_CREATE(test_1)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_1)
{
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 0));
}

MIRE_CT_COUNTER_INCREMENT(test_1)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_2)
{
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_1)::value== 0));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 1));
}

struct test_2 { };
MIRE_CT_COUNTER_CREATE(test_2)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_3)
{
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_1)::value== 0));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 1));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_2)::value == 0));
}

MIRE_CT_COUNTER_INCREMENT(test_2)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_4)
{
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_1)::value== 0));
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_2)::value== 0));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 1));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_2)::value == 1));
}

MIRE_CT_COUNTER_INCREMENT(test_2)
MIRE_CT_COUNTER_INCREMENT(test_1)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_5)
{
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_1)::value== 1));
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_2)::value== 1));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 2));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_2)::value == 2));
}

MIRE_CT_COUNTER_INCREMENT(test_1)
MIRE_CT_COUNTER_INCREMENT(test_2)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_6)
{
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_1)::value== 2));
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_2)::value== 2));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 3));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_2)::value == 3));
}

MIRE_CT_COUNTER_INCREMENT(test_2)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_7)
{
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_1)::value== 2));
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_2)::value== 3));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 3));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_2)::value == 4));
}

MIRE_CT_COUNTER_INCREMENT(test_1)

BOOST_AUTO_TEST_CASE(mire_ct_counter_basic_8)
{
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_1)::value== 3));
	BOOST_CHECK((MIRE_CT_COUNTER_PREVIOUS(test_2)::value== 3));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_1)::value == 4));
	BOOST_CHECK((MIRE_CT_COUNTER_CURRENT(test_2)::value == 4));
}

BOOST_AUTO_TEST_SUITE_END()

