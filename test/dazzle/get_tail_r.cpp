/**
 *  .file test/dazzle/get_tail_r.cpp
 *  .brief Test case for compile-time get_tail operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_get_tail
#include <boost/test/unit_test.hpp>

#include <dazzle/sequence_ops.hpp>
#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_get_tail)

BOOST_AUTO_TEST_CASE(dazzle_get_tail_range)
{
	using namespace dazzle;

	BOOST_CHECK((
		empty_range.get_tail(size_t_<0>) ==
		empty_range
	));

	BOOST_CHECK((
		empty_range.get_tail(size_t_<10>) ==
		empty_range
	));

	BOOST_CHECK((
		range<long, int, char, bool>.get_tail(size_t_<0>) ==
		empty_range
	));

	BOOST_CHECK((
		range<long, int, char, bool>.get_tail(size_t_<1>) ==
		range<bool>
	));

	BOOST_CHECK((
		range<long, int, char, bool>.get_tail(size_t_<2>) ==
		range<char, bool>
	));

	BOOST_CHECK((
		range<long, int, char, bool>.get_tail(size_t_<3>) ==
		range<int, char, bool>
	));

	BOOST_CHECK((
		range<long, int, char, bool>.get_tail(size_t_<4>) ==
		range<long, int, char, bool>
	));

	BOOST_CHECK((
		range<long, int, char, bool>.get_tail(size_t_<5>) ==
		range<long, int, char, bool>
	));

	BOOST_CHECK((
		range<long, int, char, bool>.get_tail(size_t_<100>) ==
		range<long, int, char, bool>
	));
}

BOOST_AUTO_TEST_CASE(dazzle_get_tail_string)
{
	using namespace dazzle;

	BOOST_CHECK((
		empty_string.get_tail(size_t_<0>) ==
		empty_string
	));

	BOOST_CHECK((
		empty_string.get_tail(size_t_<12>) ==
		empty_string
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<0>) ==
		empty_string
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<1>) ==
		string<'e'>
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<2>) ==
		string<'d','e'>
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<3>) ==
		string<'c','d','e'>
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<4>) ==
		string<'b','c','d','e'>
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<5>) ==
		string<'a','b','c','d','e'>
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<6>) ==
		string<'a','b','c','d','e'>
	));

	BOOST_CHECK((
		string<'a','b','c','d','e'>.get_tail(size_t_<100>) ==
		string<'a','b','c','d','e'>
	));

}

BOOST_AUTO_TEST_SUITE_END()

