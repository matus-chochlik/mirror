/**
 *  .file test/dazzle/get_front_r.cpp
 *  .brief Test case for compile-time get_front operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE DAZZLE_get_front
#include <boost/test/unit_test.hpp>

#include <dazzle/sequence_ops.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>
#include <dazzle/none.hpp>
#include <dazzle/type.hpp>

BOOST_AUTO_TEST_SUITE(dazzle_get_front)

BOOST_AUTO_TEST_CASE(dazzle_get_front_range)
{
	using namespace dazzle;

	BOOST_CHECK((empty_range.get_front().is_none()));
	BOOST_CHECK((range<long>.get_front() == type<long>));
	BOOST_CHECK((range<char>.get_front() == type<char>));
	BOOST_CHECK((range<int>.get_front() == type<int>));
	BOOST_CHECK((range<int, bool>.get_front() == type<int>));
	BOOST_CHECK((range<int, int, int>.get_front() == type<int>));
	BOOST_CHECK((range<double, float>.get_front() == type<double>));
	BOOST_CHECK((range<char, int, bool>.get_front() == type<char>));

	BOOST_CHECK((range<int, bool>.get_front() != type<bool>));
	BOOST_CHECK((range<double, float>.get_front() != type<float>));
	BOOST_CHECK((range<char, int, bool>.get_front() != type<long>));
}

BOOST_AUTO_TEST_CASE(dazzle_get_front_string)
{
	using namespace dazzle;

	BOOST_CHECK((empty_string.get_front().is_none()));
	BOOST_CHECK((string<'x'>.get_front() == char_<'x'>));
	BOOST_CHECK((string<'y'>.get_front() == char_<'y'>));
	BOOST_CHECK((string<'x','y','z'>.get_front() == char_<'x'>));
	BOOST_CHECK((string<'a','b','c','d'>.get_front() == char_<'a'>));

	BOOST_CHECK((string<'x','y','z'>.get_front() != char_<'w'>));
	BOOST_CHECK((string<'x','y','z'>.get_front() != char_<'y'>));
	BOOST_CHECK((string<'x','y','z'>.get_front() != char_<'z'>));
}

BOOST_AUTO_TEST_SUITE_END()

