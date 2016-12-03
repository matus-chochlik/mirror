/**
 *  .file test/mirror/foldl_r.cpp
 *  .brief Test case for compile-time foldl operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE MIRROR_foldl
#include <boost/test/unit_test.hpp>

#include <mirror/foldl.hpp>
#include <mirror/value.hpp>
#include <mirror/equal.hpp>
#include <mirror/add.hpp>
#include <mirror/push_back.hpp>

BOOST_AUTO_TEST_SUITE(mirror_foldl)

template <typename A, typename B>
using mirror_foldl_1_op = mirror::add<A, mirror::sizeof_<B>>;


BOOST_AUTO_TEST_CASE(mirror_foldl_1)
{
	using namespace mirror;

	BOOST_CHECK_EQUAL((value<
		foldl<
			mirror_foldl_1_op,
			empty_range,
			size_t_<1234>
		>
	>), 1234);

	BOOST_CHECK_EQUAL((value<
		foldl<
			mirror_foldl_1_op,
			range<bool, short, int, long, char>,
			size_t_<9>
		>
	>),9+sizeof(bool)+sizeof(short)+sizeof(int)+sizeof(long)+sizeof(char));

	BOOST_CHECK_EQUAL((value<
		foldl<
			mirror_foldl_1_op,
			range<float, unsigned, wchar_t, double>,
			size_t_<11>
		>
	>),11+sizeof(float)+sizeof(unsigned)+sizeof(wchar_t)+sizeof(double));
}

BOOST_AUTO_TEST_CASE(mirror_foldl_2)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			empty_range,
			range<char, double, void>
		>, range<char, double, void>
	>>));

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			range<char, double, void>,
			empty_range
		>, range<char, double, void>
	>>));

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			range<double, int>,
			range<unsigned, float, short>
		>, range<unsigned, float, short, double, int>
	>>));

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			range<unsigned, float, short>,
			range<double, int>
		>, range<double, int, unsigned, float, short>
	>>));
}

BOOST_AUTO_TEST_CASE(mirror_foldl_3)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			empty_string,
			string<'A','B','C','D'>
		>, string<'A','B','C','D'>
	>>));

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			string<'A','B','C','D'>,
			empty_string
		>, string<'A','B','C','D'>
	>>));

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			string<'E','F','G','H'>,
			string<'A','B','C','D'>
		>, string<'A','B','C','D','E','F','G','H'>
	>>));

	BOOST_CHECK((value<equal<
		foldl<
			push_back,
			string<'A','B','C','D'>,
			string<'E','F','G','H'>
		>, string<'E','F','G','H','A','B','C','D'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

