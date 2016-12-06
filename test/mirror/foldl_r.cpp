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
#include <mirror/minimum.hpp>
#include <mirror/push_back.hpp>
#include <reflbase/type_traits_fixes.hpp>

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

template <typename A, typename B>
using mirror_pick_bigger = std::conditional_t<(sizeof(A) > sizeof(B)), A, B>;

BOOST_AUTO_TEST_CASE(mirror_foldl_2)
{
	using namespace mirror;

	BOOST_CHECK((value<std::is_same<
		foldl<
			mirror_pick_bigger,
			range<char[4], char[7], char[9], char[2], char[5]>
		>, char[9]
	>>));

	BOOST_CHECK((value<std::is_same<
		foldl<
			mirror_pick_bigger,
			range<char[1], char[2], char[3], char[4], char[5]>
		>, char[5]
	>>));

	BOOST_CHECK((value<std::is_same<
		foldl<
			mirror_pick_bigger,
			range<char[8], char[6], char[4], char[2], char[1]>
		>, char[8]
	>>));

	BOOST_CHECK((value<std::is_same<
		foldl<
			mirror_pick_bigger,
			range<char[4], char[4], char[4], char[4]>
		>, char[4]
	>>));
};

BOOST_AUTO_TEST_CASE(mirror_foldl_3)
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

BOOST_AUTO_TEST_CASE(mirror_foldl_4)
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

BOOST_AUTO_TEST_CASE(mirror_foldl_5)
{
	using namespace mirror;

	BOOST_CHECK((value<equal<
		foldl<
			minimum,
			string<'A','B','C','D'>
		>, char_<'A'>
	>>));
}

BOOST_AUTO_TEST_SUITE_END()

