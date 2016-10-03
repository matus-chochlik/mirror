/**
 *  .file test/reflexpr/reflects_same_r.cpp
 *  .brief Test case for compile-time `reflects_same` operation
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLEXPR_reflects_same
#include <boost/test/unit_test.hpp>

#include <reflexpr>
#include <string>

BOOST_AUTO_TEST_SUITE(reflexpr_reflects_same)

BOOST_AUTO_TEST_CASE(mirror_reflects_same_1)
{
	using namespace std::meta;

	BOOST_CHECK(( reflects_same_v<
		reflexpr(),
		reflexpr()
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(::),
		reflexpr()
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(::std),
		reflexpr(std)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(int),
		reflexpr(int)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(float),
		reflexpr(float)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(std::string),
		reflexpr(std::string)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(static),
		reflexpr(static)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(public),
		reflexpr(public)
	>));
}

BOOST_AUTO_TEST_CASE(mirror_reflects_same_2)
{
	using namespace std::meta;

	BOOST_CHECK((!reflects_same_v<
		reflexpr(),
		reflexpr(std)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(),
		reflexpr(int)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(std),
		reflexpr(int)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(float),
		reflexpr(long)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(std::string),
		reflexpr(std::wstring)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(protected),
		reflexpr(private)
	>));
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

