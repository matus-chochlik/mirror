/**
 *  .file test/mirror/traits_r.cpp
 *  .brief Test case for traits
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_traits
#include <boost/test/unit_test.hpp>

#include <mirror/traits.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>

BOOST_AUTO_TEST_SUITE(mirror_traits)

BOOST_AUTO_TEST_CASE(mirror_traits_is_range)
{
	using namespace mirror;

	BOOST_CHECK((!value<is_range<int>>));
	BOOST_CHECK(( value<is_range<empty_range>>));
	BOOST_CHECK(( value<is_range<range<int>>>));
	BOOST_CHECK(( value<is_range<range<long, char, bool>>>));
	BOOST_CHECK((!value<is_range<none>>));
	BOOST_CHECK((!value<is_range<string<'a','b','c'>>>));
	BOOST_CHECK((!value<is_range<MIRRORED(int)>>));
	BOOST_CHECK((!value<is_range<int_<0>>>));
}

BOOST_AUTO_TEST_CASE(mirror_traits_is_string)
{
	using namespace mirror;

	BOOST_CHECK((!value<is_string<const char*>>));
	BOOST_CHECK((!value<is_string<int>>));
	BOOST_CHECK(( value<is_string<empty_string>>));
	BOOST_CHECK(( value<is_string<string<'a','b','c'>>>));
	BOOST_CHECK((!value<is_string<none>>));
	BOOST_CHECK((!value<is_string<unsigned_<1>>>));
	BOOST_CHECK((!value<is_string<empty_range>>));
	BOOST_CHECK((!value<is_string<range<int, bool, char>>>));
	BOOST_CHECK((!value<is_string<MIRRORED(int)>>));
}

BOOST_AUTO_TEST_CASE(mirror_traits_is_none)
{
	using namespace mirror;

	BOOST_CHECK((!value<is_none<int>>));
	BOOST_CHECK(( value<is_none<none>>));
	BOOST_CHECK((!value<is_none<empty_range>>));
	BOOST_CHECK((!value<is_none<range<long, bool, char>>>));
	BOOST_CHECK((!value<is_none<MIRRORED(int)>>));
	BOOST_CHECK((!value<is_none<unsigned_<2>>>));
	BOOST_CHECK((!value<is_none<empty_string>>));
	BOOST_CHECK((!value<is_none<string<'a','b','c'>>>));
}

BOOST_AUTO_TEST_CASE(mirror_traits_is_meta_object)
{
	using namespace mirror;

	BOOST_CHECK((!value<is_meta_object<int>>));
	BOOST_CHECK((!value<is_meta_object<none>>));
	BOOST_CHECK((!value<is_meta_object<empty_string>>));
	BOOST_CHECK((!value<is_meta_object<string<'x','y','z'>>>));
	BOOST_CHECK((!value<is_meta_object<empty_range>>));
	BOOST_CHECK((!value<is_meta_object<range<float, int, short>>>));
	BOOST_CHECK((!value<is_meta_object<bool_<true>>>));
	BOOST_CHECK(( value<is_meta_object<MIRRORED(int)>>));
}

BOOST_AUTO_TEST_SUITE_END()

