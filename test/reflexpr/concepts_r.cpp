/**
 *  .file test/reflexpr/concepts.cpp
 *
 *  .author Matus Chochlik
 *
 *  Copyright Matus Chochlik.
 *  Distributed under the Boost Software License, Version 1.0.
 *  See accompanying file LICENSE_1_0.txt or copy at
 *   http://www.boost.org/LICENSE_1_0.txt
 */
#define BOOST_TEST_DYN_LINK
#define BOOST_TEST_MODULE REFLEXPR_concepts
#include <boost/test/unit_test.hpp>

#include <reflexpr>

BOOST_AUTO_TEST_SUITE(reflexpr_reflects_same)

struct A { };
struct B { };
struct D : A, B { };

enum E { a, b, c };
enum class F { m, n, o };
class C { public: long l; short s; struct X { }; };
struct S { using T = int; T x, y, z; };
union U { float f; double d; };

using V = U;

BOOST_AUTO_TEST_CASE(mirror_concepts_not_Object)
{
	using namespace std::meta;

	BOOST_CHECK((!Object<int>));
	BOOST_CHECK((!Object<E>));
	BOOST_CHECK((!Object<F>));
	BOOST_CHECK((!Object<C>));
	BOOST_CHECK((!Object<S>));
	BOOST_CHECK((!Object<U>));
	BOOST_CHECK((!Object<V>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Object)
{
	using namespace std::meta;

	BOOST_CHECK(( Object<reflexpr()>));
	BOOST_CHECK(( Object<reflexpr(std)>));
	BOOST_CHECK(( Object<reflexpr(int)>));
	BOOST_CHECK(( Object<reflexpr(E)>));
	BOOST_CHECK(( Object<reflexpr(F)>));
	BOOST_CHECK(( Object<reflexpr(C)>));
	BOOST_CHECK(( Object<reflexpr(S)>));
	BOOST_CHECK(( Object<reflexpr(U)>));
	BOOST_CHECK(( Object<reflexpr(V)>));

	BOOST_CHECK(( Object<reflexpr(a)>));
	BOOST_CHECK(( Object<reflexpr(F::m)>));
	BOOST_CHECK(( Object<reflexpr(C::s)>));
	BOOST_CHECK(( Object<reflexpr(S::x)>));
	BOOST_CHECK(( Object<reflexpr(U::d)>));

	BOOST_CHECK(( Object<reflexpr(static)>));
	BOOST_CHECK(( Object<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK(( Object<meta_DbA>));
	BOOST_CHECK(( Object<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_ObjectSequence)
{
	using namespace std::meta;

	BOOST_CHECK((!ObjectSequence<reflexpr()>));
	BOOST_CHECK((!ObjectSequence<reflexpr(std)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(int)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(E)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(F)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(C)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(S)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(U)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(V)>));

	BOOST_CHECK((!ObjectSequence<reflexpr(a)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(F::m)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(C::s)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(S::x)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(U::d)>));

	BOOST_CHECK((!ObjectSequence<reflexpr(static)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(public)>));

	BOOST_CHECK(( ObjectSequence<get_enumerators_m<reflexpr(E)>>));
	BOOST_CHECK(( ObjectSequence<get_enumerators_m<reflexpr(F)>>));

	BOOST_CHECK(( ObjectSequence<get_data_members_m<reflexpr(A)>>));
	BOOST_CHECK(( ObjectSequence<get_data_members_m<reflexpr(D)>>));
	BOOST_CHECK(( ObjectSequence<get_data_members_m<reflexpr(C)>>));
	BOOST_CHECK(( ObjectSequence<get_data_members_m<reflexpr(S)>>));
	BOOST_CHECK(( ObjectSequence<get_data_members_m<reflexpr(U)>>));

	BOOST_CHECK(( ObjectSequence<get_base_classes_m<reflexpr(D)>>));
	BOOST_CHECK(( ObjectSequence<get_base_classes_m<reflexpr(S)>>));

	using meta_Db = get_base_classes_m<reflexpr(D)>;

	BOOST_CHECK(( ObjectSequence<meta_Db>));

	BOOST_CHECK((!ObjectSequence<get_element_m<meta_Db, 0>>));
	BOOST_CHECK((!ObjectSequence<get_element_m<meta_Db, 1>>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Named)
{
	using namespace std::meta;

	BOOST_CHECK(( Named<reflexpr()>));
	BOOST_CHECK(( Named<reflexpr(std)>));
	BOOST_CHECK(( Named<reflexpr(int)>));
	BOOST_CHECK(( Named<reflexpr(E)>));
	BOOST_CHECK(( Named<reflexpr(F)>));
	BOOST_CHECK(( Named<reflexpr(C)>));
	BOOST_CHECK(( Named<reflexpr(S)>));
	BOOST_CHECK(( Named<reflexpr(U)>));
	BOOST_CHECK(( Named<reflexpr(V)>));

	BOOST_CHECK(( Named<reflexpr(a)>));
	BOOST_CHECK(( Named<reflexpr(F::m)>));
	BOOST_CHECK(( Named<reflexpr(C::s)>));
	BOOST_CHECK(( Named<reflexpr(S::x)>));
	BOOST_CHECK(( Named<reflexpr(U::d)>));

	BOOST_CHECK(( Named<reflexpr(static)>));
	BOOST_CHECK(( Named<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Named<meta_DbA>));
	BOOST_CHECK((!Named<meta_DbB>));
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

