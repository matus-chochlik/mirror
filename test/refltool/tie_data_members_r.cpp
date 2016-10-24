/**
 *  .file test/refltool/tie_data_members.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLTOOL_tie_data_members
#include <boost/test/unit_test.hpp>

#include <refltool/tie_data_members.hpp>

BOOST_AUTO_TEST_SUITE(refltool_tie_data_members)

struct S
{
	volatile int a;
	bool b;
	const volatile char c;
	const double d;
	float e;
	static long l;

	S(void) : a(0), b(true), c('2'), d(34.5), e(6.7f) { }
};

long S::l = 123;

class C
{
private:
	long x;
protected:
	int y;
public:
	short z;

	C(void) : x(12345), y(678), z(90) { }

	long* px(void) { return &x; }
	int* py(void) { return &y; }
	short* pz(void) { return &z; }

};

BOOST_AUTO_TEST_CASE(refltool_tie_data_members_S)
{
	using namespace refltool;

	S s;

	using T = std::tuple<
		volatile int&,
		bool&,
		const volatile char&,
		const double&,
		float&,
		long&
	>;
	T t = tie_data_members(s);

	BOOST_CHECK_EQUAL(&std::get<0>(t), &s.a);
	BOOST_CHECK_EQUAL(&std::get<1>(t), &s.b);
	BOOST_CHECK_EQUAL(&std::get<2>(t), &s.c);
	BOOST_CHECK_EQUAL(&std::get<3>(t), &s.d);
	BOOST_CHECK_EQUAL(&std::get<4>(t), &s.e);
	BOOST_CHECK_EQUAL(&std::get<5>(t), &s.l);

}

BOOST_AUTO_TEST_CASE(refltool_tie_data_members_C_all)
{
	using namespace refltool;

	C c;

	using T = std::tuple<long&, int&, short&>;
	T t = tie_data_members(c);

	BOOST_CHECK_EQUAL(&std::get<0>(t), c.px());
	BOOST_CHECK_EQUAL(&std::get<1>(t), c.py());
	BOOST_CHECK_EQUAL(&std::get<2>(t), c.pz());
}

BOOST_AUTO_TEST_CASE(refltool_tie_data_members_C_pub)
{
	using namespace refltool;

	C c;

	using T = std::tuple<short&>;
	T t = tie_public_data_members(c);

	BOOST_CHECK_EQUAL(&std::get<0>(t), c.pz());
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

