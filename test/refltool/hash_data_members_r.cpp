/**
 *  .file test/refltool/hash_data_members.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLTOOL_hash_data_members
#include <boost/test/unit_test.hpp>

#include <refltool/hash_data_members.hpp>

BOOST_AUTO_TEST_SUITE(refltool_hash_data_members)

struct S
{
	volatile int a;
	bool b;
	const volatile char c;
	const double d;
	float e;
};

BOOST_AUTO_TEST_CASE(refltool_hash_data_members_S)
{
	using namespace refltool;

	S s1{0,true,'2',45.67,8.9f};
	S s2{1,true,'2',45.67,8.9f};
	S s3{0,false,'2',45.67,8.9f};
	S s4{0,true,'3',45.67,8.9f};
	S s5{0,true,'2',56.78,8.9f};
	S s6{0,true,'2',45.67,9.0f};
	S s7{0,true,'2',45.67,8.9f};

	std::size_t hs1 = hash_data_members(s1);
	std::size_t hs2 = hash_data_members(s2);
	std::size_t hs3 = hash_data_members(s3);
	std::size_t hs4 = hash_data_members(s4);
	std::size_t hs5 = hash_data_members(s5);
	std::size_t hs6 = hash_data_members(s6);
	std::size_t hs7 = hash_data_members(s7);

	BOOST_CHECK(hs1 != hs2);
	BOOST_CHECK(hs1 != hs3);
	BOOST_CHECK(hs1 != hs4);
	BOOST_CHECK(hs1 != hs5);
	BOOST_CHECK(hs1 != hs6);
	BOOST_CHECK(hs1 == hs7);

	BOOST_CHECK(hs2 != hs3);
	BOOST_CHECK(hs2 != hs4);
	BOOST_CHECK(hs2 != hs5);
	BOOST_CHECK(hs2 != hs6);

	BOOST_CHECK(hs3 != hs4);
	BOOST_CHECK(hs3 != hs5);
	BOOST_CHECK(hs3 != hs6);

	BOOST_CHECK(hs4 != hs5);
	BOOST_CHECK(hs4 != hs6);

	BOOST_CHECK(hs5 != hs6);
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

