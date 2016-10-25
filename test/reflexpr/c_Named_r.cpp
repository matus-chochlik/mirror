/**
 *  .file test/reflexpr/c_Named_r.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLEXPR_c_Named
#include <boost/test/unit_test.hpp>

#include <reflexpr>

BOOST_AUTO_TEST_SUITE(reflexpr_c_Named)

struct A { };
struct B { };
struct D : A, B { };

enum E { a, b, c };
enum class F { m, n, o };
using G = F;

class C { public: long l; short s; struct X { }; using Y = X; };
struct S { using T = int; T x, y, z; union U {int i; float f;}; using V = U; };
union U { float f; double d; enum E {g,h,i}; using F = E; };

using V = U;

template <typename X>
struct W
{
	using T = X;
};

using Z = W<int>;

static const int i = 123;

BOOST_AUTO_TEST_CASE(reflexpr_dummy)
{
	BOOST_CHECK_EQUAL(i, 123);
}


BOOST_AUTO_TEST_CASE(reflexpr_get_base_name)
{
	using namespace std::meta;

	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr()>), "");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(::)>), "");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(std)>), "std");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(int)>), "int");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(int[10])>), "int");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(E)>), "E");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(E*)>), "E");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(F)>), "F");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(G)>), "G");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(C)>), "C");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(C&)>), "C");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(S)>), "S");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(U)>), "U");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(V)>), "V");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(Z)>), "Z");

	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(a)>), "a");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(F::m)>), "m");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(C::s)>), "s");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(S::x)>), "x");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(U::d)>), "d");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(i)>), "i");

	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(S::T)>), "T");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(S::U)>), "U");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(S::V)>), "V");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(C::X)>), "X");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(C::Y)>), "Y");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(U::E)>), "E");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(U::F)>), "F");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(Z::T)>), "T");

	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(static)>), "static");
	BOOST_CHECK_EQUAL((get_base_name_v<reflexpr(public)>), "public");
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

