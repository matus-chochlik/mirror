/**
 *  .file test/dazzle/transform.cpp
 *  .brief Test case for compile-time type operations
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_transform
#include <boost/test/unit_test.hpp>

#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>
#include <reflbase/type_traits_fixes.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_transform)

BOOST_AUTO_TEST_CASE(dazzle_transform_range_1)
{
	using namespace dazzle;

	auto ro = range<int, float, double, long>;
	auto rt = range<int*, float*, double*, long*>;

	BOOST_CHECK((ro.transform<std::add_pointer_t>() == rt));
}

BOOST_AUTO_TEST_CASE(dazzle_transform_range_2)
{
	using namespace dazzle;

	auto ro = range<int&, float&, double&, long&>;
	auto rt = range<int, float, double, long>;

	BOOST_CHECK((ro.transform<std::remove_reference_t>() == rt));
}

template <typename C>
struct test_to_upper;

template <typename Char, Char C>
struct test_to_upper<mirror::int_const<Char, C>>
 : mirror::int_const<Char, (C>='a' && C<='z')?(C-'a'+'A'):C> 
{ };

BOOST_AUTO_TEST_CASE(dazzle_transform_string_1)
{
	using namespace dazzle;

	auto so = string<'a','b','c','d','e','f'>;
	auto st = string<'A','B','C','D','E','F'>;

	BOOST_CHECK((so.transform<test_to_upper>() == st));
}

BOOST_AUTO_TEST_SUITE_END()

