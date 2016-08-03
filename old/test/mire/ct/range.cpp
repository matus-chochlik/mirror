/**
 *  .file test/mire/ct/range.cpp
 *  .brief Test case for compile-time ranges
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_range
#include <boost/test/unit_test.hpp>

#include <mire/ct/range.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_range)

BOOST_AUTO_TEST_CASE(mire_ct_range_test1)
{
	using namespace mire;

	typedef ct::empty_range er;
	typedef ct::range<> r0;
	typedef ct::range<bool> r1;
	typedef ct::range<bool, char> r2;
	typedef ct::range<char, wchar_t, short> r3;
	typedef ct::range<wchar_t, short, int, long> r4;
	typedef ct::range<short, int, long, long long, float> r5;
	typedef ct::range<int, long, long long, float, double, long double> r6;
}

BOOST_AUTO_TEST_SUITE_END()

