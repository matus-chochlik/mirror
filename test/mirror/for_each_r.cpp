/**
 *  .file test/mirror/for_each_r.cpp
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
#define BOOST_TEST_MODULE MIRROR_for_each
#include <boost/test/unit_test.hpp>

#include <mirror/for_each.hpp>
#include <mirror/value.hpp>
#include <mirror/c_str.hpp>
#include <sstream>

BOOST_AUTO_TEST_SUITE(mirror_for_each)

BOOST_AUTO_TEST_CASE(mirror_for_each_none)
{
	using namespace mirror;

	using n1 = none;

	std::stringstream ss;
	auto func = [&ss](auto x) { ss << value<decltype(x)>; };

	ss << "<";
	for_each<n1>::apply(func);
	ss << ">";

	BOOST_CHECK_EQUAL(ss.str(), "<>");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_str_1)
{
	using namespace mirror;

	using s1 = string<'a','b','c','d','e','f','g','h'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value<decltype(chr)>; };

	for_each<s1>::apply(func);

	BOOST_CHECK_EQUAL(ss.str(), "abcdefgh");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_str_2)
{
	using namespace mirror;

	using s1 = string<'S','t','r','i','n','g','!'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value<decltype(chr)>; };

	for_each<s1>::apply(func);

	BOOST_CHECK_EQUAL(ss.str(), "String!");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_str_3)
{
	using namespace mirror;

	using s1 = string<'X','Y','Z'>;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value<decltype(chr)>; };
	auto sepf = [&ss](void) { ss << ","; };

	for_each<s1>::apply(func, sepf);

	BOOST_CHECK_EQUAL(ss.str(), "X,Y,Z");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_str_4)
{
	using namespace mirror;

	using s1 = empty_string;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value<decltype(chr)>; };

	ss << "[";
	for_each<s1>::apply(func);
	ss << "]";

	BOOST_CHECK_EQUAL(ss.str(), "[]");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_str_5)
{
	using namespace mirror;

	using s1 = empty_string;

	std::stringstream ss;
	auto func = [&ss](auto chr) { ss << value<decltype(chr)>; };
	auto sepf = [&ss](void) { ss << ","; };

	ss << "{";
	for_each<s1>::apply(func, sepf);
	ss << "}";

	BOOST_CHECK_EQUAL(ss.str(), "{}");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_rng_1)
{
	using namespace mirror;

	using r1 = range<
		string<'A','B','C'>,
		string<'D','E','F','G'>,
		string<'H','I','J','K','L'>,
		string<'M','N','O','P','Q','R'>,
		string<'S','T','U','V','W','X','Y','Z'>
	>;

	std::stringstream ss;
	auto func = [&ss](auto str) { ss << c_str<decltype(str)>; };

	for_each<r1>::apply(func);

	BOOST_CHECK_EQUAL(ss.str(), "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_rng_2)
{
	using namespace mirror;

	using r1 = range<
		string<'u','s','r'>,
		string<'l','o','c','a','l'>,
		string<'i','n','c','l','u','d','e'>
	>;

	std::stringstream ss;
	ss << "/";
	auto func = [&ss](auto str) { ss << c_str<decltype(str)>; };
	auto sepf = [&ss](void) { ss << "/"; };

	for_each<r1>::apply(func, sepf);

	BOOST_CHECK_EQUAL(ss.str(), "/usr/local/include");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_rng_3)
{
	using namespace mirror;

	using r1 = empty_range;

	std::stringstream ss;
	auto func = [&ss](auto str) { ss << c_str<decltype(str)>; };

	ss << "`";
	for_each<r1>::apply(func);
	ss << "'";

	BOOST_CHECK_EQUAL(ss.str(), "`'");
}

BOOST_AUTO_TEST_CASE(mirror_for_each_rng_4)
{
	using namespace mirror;

	using r1 = empty_range;

	std::stringstream ss;
	auto func = [&ss](auto str) { ss << c_str<decltype(str)>; };
	auto sepf = [&ss](void) { ss << "|"; };

	ss << "^";
	for_each<r1>::apply(func, sepf);
	ss << "$";

	BOOST_CHECK_EQUAL(ss.str(), "^$");
}

BOOST_AUTO_TEST_SUITE_END()

