/**
 *  .file test/dazzle/for_each_r.cpp
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
#define BOOST_TEST_MODULE DAZZLE_for_each
#include <boost/test/unit_test.hpp>

#include <dazzle/int_const.hpp>
#include <dazzle/string.hpp>
#include <dazzle/range.hpp>
#include <dazzle/type.hpp>
#include <sstream>

BOOST_AUTO_TEST_SUITE(dazzle_for_each)

BOOST_AUTO_TEST_CASE(dazzle_for_each_1)
{
	using namespace dazzle;

	auto s1 = string<'a','b','c','d','e','f','g','h'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << chr; };

	s1.for_each(func);

	BOOST_CHECK_EQUAL(ss.str(), "abcdefgh");
}

BOOST_AUTO_TEST_CASE(dazzle_for_each_2)
{
	using namespace dazzle;

	auto s1 = string<'S','t','r','i','n','g','!'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << chr; };

	s1.for_each(func);

	BOOST_CHECK_EQUAL(ss.str(), "String!");
}


BOOST_AUTO_TEST_CASE(dazzle_for_each_3)
{
	using namespace dazzle;

	auto s1 = string<'X','Y','Z'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << chr; };
	auto sepf = [&ss](void) { ss << ","; };

	s1.for_each(func, sepf);

	BOOST_CHECK_EQUAL(ss.str(), "X,Y,Z");
}

BOOST_AUTO_TEST_CASE(dazzle_for_each_4)
{
	using namespace dazzle;

	auto r1 = make_range(
		string<'A','B','C'>,
		string<'D','E','F','G'>,
		string<'H','I','J','K','L'>,
		string<'M','N','O','P','Q','R'>,
		string<'S','T','U','V','W','X','Y','Z'>
	);

	std::stringstream ss;
	auto func = [&ss](auto str) { ss << str; };

	r1.for_each(func);

	BOOST_CHECK_EQUAL(ss.str(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

BOOST_AUTO_TEST_CASE(dazzle_for_each_5)
{
	using namespace dazzle;

	auto r1 = make_range(
		string<'u','s','r'>,
		string<'l','o','c','a','l'>,
		string<'i','n','c','l','u','d','e'>
	);

	std::stringstream ss;
	ss << "/";
	auto func = [&ss](auto str) { ss << str; };
	auto sepf = [&ss](void) { ss << "/"; };

	r1.for_each(func, sepf);

	BOOST_CHECK_EQUAL(ss.str(), "/usr/local/include");
}

BOOST_AUTO_TEST_SUITE_END()

