/**
 *  .file test/puddle/for_each_r.cpp
 *  .brief Test case for compile-time for_each operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE PUDDLE_for_each
#include <boost/test/unit_test.hpp>

#include <puddle/sequence_ops.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <puddle/range.hpp>
#include <sstream>

BOOST_AUTO_TEST_SUITE(puddle_for_each)

BOOST_AUTO_TEST_CASE(puddle_for_each_1)
{
	using namespace puddle;

	auto s1 = string<'a','b','c','d','e','f','g','h'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value(chr); };

	for_each(s1, func);

	BOOST_CHECK_EQUAL(ss.str(), "abcdefgh");
}

BOOST_AUTO_TEST_CASE(puddle_for_each_2)
{
	using namespace puddle;

	auto s1 = string<'S','t','r','i','n','g','!'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value(chr); };

	for_each(s1, func);

	BOOST_CHECK_EQUAL(ss.str(), "String!");
}


BOOST_AUTO_TEST_CASE(puddle_for_each_3)
{
	using namespace puddle;

	auto s1 = string<'X','Y','Z'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value(chr); };
	auto sepf = [&ss](void) { ss << ","; };

	for_each(s1, func, sepf);

	BOOST_CHECK_EQUAL(ss.str(), "X,Y,Z");
}

BOOST_AUTO_TEST_CASE(puddle_for_each_4)
{
	using namespace puddle;

	auto r1 = make_range(
		string<'A','B','C'>,
		string<'D','E','F','G'>,
		string<'H','I','J','K','L'>,
		string<'M','N','O','P','Q','R'>,
		string<'S','T','U','V','W','X','Y','Z'>
	);

	std::stringstream ss;
	auto func = [&ss](auto str) { ss << c_str(str); };

	for_each(r1, func);

	BOOST_CHECK_EQUAL(ss.str(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

BOOST_AUTO_TEST_CASE(puddle_for_each_5)
{
	using namespace puddle;

	auto r1 = make_range(
		string<'u','s','r'>,
		string<'l','o','c','a','l'>,
		string<'i','n','c','l','u','d','e'>
	);

	std::stringstream ss;
	ss << "/";
	auto func = [&ss](auto str) { ss << c_str(str); };
	auto sepf = [&ss](void) { ss << "/"; };

	for_each(r1, func, sepf);

	BOOST_CHECK_EQUAL(ss.str(), "/usr/local/include");
}

BOOST_AUTO_TEST_SUITE_END()

