/**
 *  .file test/reflexpr/reflects_same_r.cpp
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

BOOST_AUTO_TEST_CASE(reflexpr_reflects_same_1)
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
		reflexpr(bool),
		reflexpr(bool)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(float),
		reflexpr(float)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(double),
		reflexpr(double)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(void),
		reflexpr(void)
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

	BOOST_CHECK(( reflects_same_v<
		reflexpr(protected),
		reflexpr(protected)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(private),
		reflexpr(private)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(class),
		reflexpr(class)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(struct),
		reflexpr(struct)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(union),
		reflexpr(union)
	>));

	BOOST_CHECK(( reflects_same_v<
		reflexpr(enum),
		reflexpr(enum)
	>));
}

BOOST_AUTO_TEST_CASE(reflexpr_reflects_same_2)
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
		reflexpr(bool),
		reflexpr(void)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(float),
		reflexpr(long)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(double),
		reflexpr(bool)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(float),
		reflexpr(class)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(double),
		reflexpr(struct)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(short),
		reflexpr(union)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(std),
		reflexpr(static)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(std::string),
		reflexpr(float)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(std::wstring),
		reflexpr(unsigned)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(std::string),
		reflexpr(std::wstring)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(public),
		reflexpr(protected)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(public),
		reflexpr(private)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(protected),
		reflexpr(private)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(class),
		reflexpr(public)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(struct),
		reflexpr(protected)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(static),
		reflexpr(private)
	>));

	BOOST_CHECK((!reflects_same_v<
		reflexpr(static),
		reflexpr(union)
	>));
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

