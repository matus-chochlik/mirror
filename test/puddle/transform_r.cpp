/**
 *  .file test/puddle/transform.cpp
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
#define BOOST_TEST_MODULE PUDDLE_transform
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <reflbase/type_traits_fixes.hpp>

BOOST_AUTO_TEST_SUITE(puddle_transform)

BOOST_AUTO_TEST_CASE(puddle_transform_range_1)
{
	using namespace puddle;

	auto ro = range<int, float, double, long>;
	auto rt = range<int*, float*, double*, long*>;

	BOOST_CHECK((value(
		transform<std::add_pointer_t>(ro) == rt
	)));
}

BOOST_AUTO_TEST_CASE(puddle_transform_range_2)
{
	using namespace puddle;

	auto ro = range<int&, float&, double&, long&>;
	auto rt = range<int, float, double, long>;

	BOOST_CHECK((value(
		transform<std::remove_reference_t>(ro) == rt
	)));
}

template <typename C>
struct test_to_upper;

template <typename Char, Char C>
struct test_to_upper<mirror::int_const<Char, C>>
 : mirror::int_const<Char, (C>='a' && C<='z')?(C-'a'+'A'):C> 
{ };

BOOST_AUTO_TEST_CASE(puddle_transform_string_1)
{
	using namespace puddle;

	auto so = string<'a','b','c','d','e','f'>;
	auto st = string<'A','B','C','D','E','F'>;

	BOOST_CHECK((value(
		transform<test_to_upper>(so) == st
	)));
}

BOOST_AUTO_TEST_SUITE_END()

