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

template <typename X>
struct W
{
	using T = X;
};

using Z = W<int>;

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
	BOOST_CHECK(( Object<reflexpr(int[10])>));
	BOOST_CHECK(( Object<reflexpr(E)>));
	BOOST_CHECK(( Object<reflexpr(E*)>));
	BOOST_CHECK(( Object<reflexpr(F)>));
	BOOST_CHECK(( Object<reflexpr(C)>));
	BOOST_CHECK(( Object<reflexpr(C&)>));
	BOOST_CHECK(( Object<reflexpr(S)>));
	BOOST_CHECK(( Object<reflexpr(U)>));
	BOOST_CHECK(( Object<reflexpr(V)>));
	BOOST_CHECK(( Object<reflexpr(Z)>));
	BOOST_CHECK(( Object<reflexpr(Z&&)>));

	BOOST_CHECK(( Object<reflexpr(a)>));
	BOOST_CHECK(( Object<reflexpr(F::m)>));
	BOOST_CHECK(( Object<reflexpr(C::s)>));
	BOOST_CHECK(( Object<reflexpr(S::x)>));
	BOOST_CHECK(( Object<reflexpr(U::d)>));

	BOOST_CHECK(( Object<reflexpr(S::T)>));
	BOOST_CHECK(( Object<reflexpr(C::X)>));
	BOOST_CHECK(( Object<reflexpr(Z::T)>));

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
	BOOST_CHECK((!ObjectSequence<reflexpr(int[10])>));
	BOOST_CHECK((!ObjectSequence<reflexpr(E)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(E*)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(F)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(C)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(C&)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(S)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(U)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(V)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(Z)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(Z&&)>));

	BOOST_CHECK((!ObjectSequence<reflexpr(a)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(F::m)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(C::s)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(S::x)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(U::d)>));

	BOOST_CHECK((!ObjectSequence<reflexpr(S::T)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(C::X)>));
	BOOST_CHECK((!ObjectSequence<reflexpr(Z::T)>));

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
	BOOST_CHECK(( Named<reflexpr(int[10])>));
	BOOST_CHECK(( Named<reflexpr(E)>));
	BOOST_CHECK(( Named<reflexpr(E*)>));
	BOOST_CHECK(( Named<reflexpr(F)>));
	BOOST_CHECK(( Named<reflexpr(C)>));
	BOOST_CHECK(( Named<reflexpr(C&)>));
	BOOST_CHECK(( Named<reflexpr(S)>));
	BOOST_CHECK(( Named<reflexpr(U)>));
	BOOST_CHECK(( Named<reflexpr(V)>));
	BOOST_CHECK(( Named<reflexpr(Z)>));
	BOOST_CHECK(( Named<reflexpr(Z&&)>));

	BOOST_CHECK(( Named<reflexpr(a)>));
	BOOST_CHECK(( Named<reflexpr(F::m)>));
	BOOST_CHECK(( Named<reflexpr(C::s)>));
	BOOST_CHECK(( Named<reflexpr(S::x)>));
	BOOST_CHECK(( Named<reflexpr(U::d)>));

	BOOST_CHECK(( Named<reflexpr(S::T)>));
	BOOST_CHECK(( Named<reflexpr(C::X)>));
	BOOST_CHECK(( Named<reflexpr(Z::T)>));

	BOOST_CHECK(( Named<reflexpr(static)>));
	BOOST_CHECK(( Named<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Named<meta_DbA>));
	BOOST_CHECK((!Named<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Alias)
{
	using namespace std::meta;

	BOOST_CHECK((!Alias<reflexpr()>));
	BOOST_CHECK((!Alias<reflexpr(std)>));
	BOOST_CHECK((!Alias<reflexpr(int)>));
	BOOST_CHECK((!Alias<reflexpr(int[10])>));
	BOOST_CHECK((!Alias<reflexpr(E)>));
	BOOST_CHECK((!Alias<reflexpr(E*)>));
	BOOST_CHECK((!Alias<reflexpr(F)>));
	BOOST_CHECK((!Alias<reflexpr(C)>));
	BOOST_CHECK((!Alias<reflexpr(C&)>));
	BOOST_CHECK((!Alias<reflexpr(S)>));
	BOOST_CHECK((!Alias<reflexpr(U)>));
	BOOST_CHECK(( Alias<reflexpr(V)>));
	BOOST_CHECK((!Alias<reflexpr(V**)>));
	BOOST_CHECK(( Alias<reflexpr(Z)>));
	BOOST_CHECK((!Alias<reflexpr(Z&&)>));

	BOOST_CHECK((!Alias<reflexpr(a)>));
	BOOST_CHECK((!Alias<reflexpr(F::m)>));
	BOOST_CHECK((!Alias<reflexpr(C::s)>));
	BOOST_CHECK((!Alias<reflexpr(S::x)>));
	BOOST_CHECK((!Alias<reflexpr(U::d)>));

	BOOST_CHECK(( Alias<reflexpr(S::T)>));
	BOOST_CHECK((!Alias<reflexpr(C::X)>));
	BOOST_CHECK(( Alias<reflexpr(Z::T)>));

	BOOST_CHECK((!Alias<reflexpr(static)>));
	BOOST_CHECK((!Alias<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Alias<meta_DbA>));
	BOOST_CHECK((!Alias<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Typed)
{
	using namespace std::meta;

	BOOST_CHECK((!Typed<reflexpr()>));
	BOOST_CHECK((!Typed<reflexpr(std)>));
	BOOST_CHECK((!Typed<reflexpr(int)>));
	BOOST_CHECK((!Typed<reflexpr(int[10])>));
	BOOST_CHECK((!Typed<reflexpr(E)>));
	BOOST_CHECK((!Typed<reflexpr(E*)>));
	BOOST_CHECK((!Typed<reflexpr(F)>));
	BOOST_CHECK((!Typed<reflexpr(C)>));
	BOOST_CHECK((!Typed<reflexpr(C&)>));
	BOOST_CHECK((!Typed<reflexpr(S)>));
	BOOST_CHECK((!Typed<reflexpr(U)>));
	BOOST_CHECK((!Typed<reflexpr(V)>));
	BOOST_CHECK((!Typed<reflexpr(Z)>));
	BOOST_CHECK((!Typed<reflexpr(Z&&)>));

	BOOST_CHECK(( Typed<reflexpr(a)>));
	BOOST_CHECK(( Typed<reflexpr(F::m)>));
	BOOST_CHECK(( Typed<reflexpr(C::s)>));
	BOOST_CHECK(( Typed<reflexpr(S::x)>));
	BOOST_CHECK(( Typed<reflexpr(U::d)>));

	BOOST_CHECK((!Typed<reflexpr(S::T)>));
	BOOST_CHECK((!Typed<reflexpr(C::X)>));
	BOOST_CHECK((!Typed<reflexpr(Z::T)>));

	BOOST_CHECK((!Typed<reflexpr(static)>));
	BOOST_CHECK((!Typed<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Typed<meta_DbA>));
	BOOST_CHECK((!Typed<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Scope)
{
	using namespace std::meta;

	BOOST_CHECK(( Scope<reflexpr()>));
	BOOST_CHECK(( Scope<reflexpr(std)>));
	BOOST_CHECK((!Scope<reflexpr(int)>));
	BOOST_CHECK((!Scope<reflexpr(int[10])>));
	BOOST_CHECK(( Scope<reflexpr(E)>));
	BOOST_CHECK((!Scope<reflexpr(E*)>));
	BOOST_CHECK(( Scope<reflexpr(F)>));
	BOOST_CHECK(( Scope<reflexpr(C)>));
	BOOST_CHECK((!Scope<reflexpr(C&)>));
	BOOST_CHECK(( Scope<reflexpr(S)>));
	BOOST_CHECK(( Scope<reflexpr(U)>));
	BOOST_CHECK(( Scope<reflexpr(V)>));
	//TODO BOOST_CHECK(( Scope<reflexpr(Z)>));
	BOOST_CHECK((!Scope<reflexpr(Z&&)>));

	BOOST_CHECK((!Scope<reflexpr(a)>));
	BOOST_CHECK((!Scope<reflexpr(F::m)>));
	BOOST_CHECK((!Scope<reflexpr(C::s)>));
	BOOST_CHECK((!Scope<reflexpr(S::x)>));
	BOOST_CHECK((!Scope<reflexpr(U::d)>));

	BOOST_CHECK((!Scope<reflexpr(S::T)>));
	BOOST_CHECK(( Scope<reflexpr(C::X)>));
	BOOST_CHECK((!Scope<reflexpr(Z::T)>));

	BOOST_CHECK((!Scope<reflexpr(static)>));
	BOOST_CHECK((!Scope<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Scope<meta_DbA>));
	BOOST_CHECK((!Scope<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_ScopeMember)
{
	using namespace std::meta;

	BOOST_CHECK(( ScopeMember<reflexpr()>));
	BOOST_CHECK(( ScopeMember<reflexpr(std)>));
	BOOST_CHECK((!ScopeMember<reflexpr(int)>));
	BOOST_CHECK((!ScopeMember<reflexpr(int[10])>));
	BOOST_CHECK(( ScopeMember<reflexpr(E)>));
	BOOST_CHECK((!ScopeMember<reflexpr(E*)>));
	BOOST_CHECK(( ScopeMember<reflexpr(F)>));
	BOOST_CHECK(( ScopeMember<reflexpr(C)>));
	BOOST_CHECK((!ScopeMember<reflexpr(C*)>));
	BOOST_CHECK(( ScopeMember<reflexpr(S)>));
	BOOST_CHECK((!ScopeMember<reflexpr(S&)>));
	BOOST_CHECK(( ScopeMember<reflexpr(U)>));
	BOOST_CHECK(( ScopeMember<reflexpr(V)>));
	BOOST_CHECK((!ScopeMember<reflexpr(V**)>));
	BOOST_CHECK(( ScopeMember<reflexpr(Z)>));
	BOOST_CHECK((!ScopeMember<reflexpr(Z&&)>));

	BOOST_CHECK(( ScopeMember<reflexpr(a)>));
	BOOST_CHECK(( ScopeMember<reflexpr(F::m)>));
	BOOST_CHECK(( ScopeMember<reflexpr(C::s)>));
	BOOST_CHECK(( ScopeMember<reflexpr(S::x)>));
	BOOST_CHECK(( ScopeMember<reflexpr(U::d)>));

	BOOST_CHECK(( ScopeMember<reflexpr(S::T)>));
	BOOST_CHECK(( ScopeMember<reflexpr(C::X)>));
	BOOST_CHECK(( ScopeMember<reflexpr(Z::T)>));

	BOOST_CHECK((!ScopeMember<reflexpr(static)>));
	BOOST_CHECK((!ScopeMember<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!ScopeMember<meta_DbA>));
	BOOST_CHECK((!ScopeMember<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_RecordMember)
{
	using namespace std::meta;

	BOOST_CHECK((!RecordMember<reflexpr()>));
	BOOST_CHECK((!RecordMember<reflexpr(std)>));
	BOOST_CHECK((!RecordMember<reflexpr(int)>));
	BOOST_CHECK((!RecordMember<reflexpr(int[10])>));
	BOOST_CHECK((!RecordMember<reflexpr(E)>));
	BOOST_CHECK((!RecordMember<reflexpr(E*)>));
	BOOST_CHECK((!RecordMember<reflexpr(F)>));
	BOOST_CHECK((!RecordMember<reflexpr(C)>));
	BOOST_CHECK((!RecordMember<reflexpr(C*)>));
	BOOST_CHECK((!RecordMember<reflexpr(S)>));
	BOOST_CHECK((!RecordMember<reflexpr(S&)>));
	BOOST_CHECK((!RecordMember<reflexpr(U)>));
	BOOST_CHECK((!RecordMember<reflexpr(V)>));
	BOOST_CHECK((!RecordMember<reflexpr(V**)>));
	BOOST_CHECK((!RecordMember<reflexpr(Z)>));
	BOOST_CHECK((!RecordMember<reflexpr(Z&&)>));

	BOOST_CHECK((!RecordMember<reflexpr(a)>));
	BOOST_CHECK((!RecordMember<reflexpr(F::m)>));
	BOOST_CHECK(( RecordMember<reflexpr(C::s)>));
	BOOST_CHECK(( RecordMember<reflexpr(S::x)>));
	BOOST_CHECK(( RecordMember<reflexpr(U::d)>));

	BOOST_CHECK(( RecordMember<reflexpr(S::T)>));
	BOOST_CHECK(( RecordMember<reflexpr(C::X)>));
	BOOST_CHECK(( RecordMember<reflexpr(Z::T)>));

	BOOST_CHECK((!RecordMember<reflexpr(static)>));
	BOOST_CHECK((!RecordMember<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!RecordMember<meta_DbA>));
	BOOST_CHECK((!RecordMember<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_EnumMember)
{
	using namespace std::meta;

	BOOST_CHECK((!EnumMember<reflexpr()>));
	BOOST_CHECK((!EnumMember<reflexpr(std)>));
	BOOST_CHECK((!EnumMember<reflexpr(int)>));
	BOOST_CHECK((!EnumMember<reflexpr(int[10])>));
	BOOST_CHECK((!EnumMember<reflexpr(E)>));
	BOOST_CHECK((!EnumMember<reflexpr(E*)>));
	BOOST_CHECK((!EnumMember<reflexpr(F)>));
	BOOST_CHECK((!EnumMember<reflexpr(C)>));
	BOOST_CHECK((!EnumMember<reflexpr(C*)>));
	BOOST_CHECK((!EnumMember<reflexpr(S)>));
	BOOST_CHECK((!EnumMember<reflexpr(S&)>));
	BOOST_CHECK((!EnumMember<reflexpr(U)>));
	BOOST_CHECK((!EnumMember<reflexpr(V)>));
	BOOST_CHECK((!EnumMember<reflexpr(V**)>));
	BOOST_CHECK((!EnumMember<reflexpr(Z)>));
	BOOST_CHECK((!EnumMember<reflexpr(Z&&)>));

	BOOST_CHECK(( EnumMember<reflexpr(a)>));
	BOOST_CHECK(( EnumMember<reflexpr(F::m)>));
	BOOST_CHECK((!EnumMember<reflexpr(C::s)>));
	BOOST_CHECK((!EnumMember<reflexpr(S::x)>));
	BOOST_CHECK((!EnumMember<reflexpr(U::d)>));

	BOOST_CHECK((!EnumMember<reflexpr(S::T)>));
	BOOST_CHECK((!EnumMember<reflexpr(C::X)>));
	BOOST_CHECK((!EnumMember<reflexpr(Z::T)>));

	BOOST_CHECK((!EnumMember<reflexpr(static)>));
	BOOST_CHECK((!EnumMember<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!EnumMember<meta_DbA>));
	BOOST_CHECK((!EnumMember<meta_DbB>));
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

