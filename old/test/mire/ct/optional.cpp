/**
 *  .file test/mire/ct/optional.cpp
 *  .brief Test case for compile-time optional values
 *
 *  .author Matus Chochlik
 *
 *  Copyright 2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRE_CT_optional
#include <boost/test/unit_test.hpp>

#include <mire/ct/optional.hpp>

BOOST_AUTO_TEST_SUITE(mire_ct_optional)

BOOST_AUTO_TEST_CASE(mire_ct_optional_test1)
{
	using namespace mire;

	typedef ct::nil_optional on;
	typedef ct::empty_optional oe;
	typedef ct::optional<int> oi;
	typedef ct::optional<float> of;
	typedef ct::optional<double> od;
}

BOOST_AUTO_TEST_SUITE_END()

