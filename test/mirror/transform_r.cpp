/**
 *  .file test/mirror/transform.cpp
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
#define BOOST_TEST_MODULE MIRROR_transform
#include <boost/test/unit_test.hpp>

#include <mirror/transform.hpp>
#include <mirror/int_const.hpp>
#include <mirror/equal.hpp>
#include <mirror/value.hpp>
#include <reflbase/type_traits_fixes.hpp>

BOOST_AUTO_TEST_SUITE(mirror_transform)

BOOST_AUTO_TEST_CASE(mirror_transform_range_1)
{
	using namespace mirror;

	using ro = range<int, float, double, long>;
	using rt = range<int*, float*, double*, long*>;

	BOOST_CHECK((value<equal<
		transform<ro, std::add_pointer_t>, rt
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_transform_range_2)
{
	using namespace mirror;

	using ro = range<int&, float&, double&, long&>;
	using rt = range<int, float, double, long>;

	BOOST_CHECK((value<equal<
		transform<ro, std::remove_reference_t>, rt
	>>));
}

template <typename C>
struct test_to_upper;

template <typename Char, Char C>
struct test_to_upper<mirror::int_const<Char, C>>
 : mirror::int_const<Char, (C>='a' && C<='z')?(C-'a'+'A'):C> 
{ };

BOOST_AUTO_TEST_CASE(mirror_transform_string_1)
{
	using namespace mirror;

	using so = string<'a','b','c','d','e','f'>;
	using st = string<'A','B','C','D','E','F'>;

	BOOST_CHECK((value<equal<
		transform<so, test_to_upper>, st
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

