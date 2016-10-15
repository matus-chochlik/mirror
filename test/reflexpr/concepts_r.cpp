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

static const int i = 123;

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

	BOOST_CHECK_EQUAL(i, 123); // unused variable
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Object)
{
	using namespace std::meta;

	BOOST_CHECK(( Object<reflexpr()>));
	BOOST_CHECK(( Object<reflexpr(::)>));
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
	BOOST_CHECK(( Object<reflexpr(i)>));

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
	BOOST_CHECK((!ObjectSequence<reflexpr(::)>));
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
	BOOST_CHECK((!ObjectSequence<reflexpr(i)>));

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
	BOOST_CHECK(( Named<reflexpr(::)>));
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
	BOOST_CHECK(( Named<reflexpr(i)>));

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
	BOOST_CHECK((!Alias<reflexpr(::)>));
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
	BOOST_CHECK((!Alias<reflexpr(i)>));

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
	BOOST_CHECK((!Typed<reflexpr(::)>));
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
	BOOST_CHECK(( Typed<reflexpr(i)>));

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
	BOOST_CHECK(( Scope<reflexpr(::)>));
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
	BOOST_CHECK((!Scope<reflexpr(i)>));

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
	BOOST_CHECK(( ScopeMember<reflexpr(::)>));
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
	BOOST_CHECK(( ScopeMember<reflexpr(i)>));

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
	BOOST_CHECK((!RecordMember<reflexpr(::)>));
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
	BOOST_CHECK((!RecordMember<reflexpr(i)>));

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
	BOOST_CHECK((!EnumMember<reflexpr(::)>));
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
	BOOST_CHECK((!EnumMember<reflexpr(i)>));

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

BOOST_AUTO_TEST_CASE(mirror_concepts_Namespace)
{
	using namespace std::meta;

	BOOST_CHECK(( Namespace<reflexpr()>));
	BOOST_CHECK(( Namespace<reflexpr(::)>));
	BOOST_CHECK(( Namespace<reflexpr(std)>));
	BOOST_CHECK((!Namespace<reflexpr(int)>));
	BOOST_CHECK((!Namespace<reflexpr(int[10])>));
	BOOST_CHECK((!Namespace<reflexpr(E)>));
	BOOST_CHECK((!Namespace<reflexpr(E*)>));
	BOOST_CHECK((!Namespace<reflexpr(F)>));
	BOOST_CHECK((!Namespace<reflexpr(C)>));
	BOOST_CHECK((!Namespace<reflexpr(C*)>));
	BOOST_CHECK((!Namespace<reflexpr(S)>));
	BOOST_CHECK((!Namespace<reflexpr(S&)>));
	BOOST_CHECK((!Namespace<reflexpr(U)>));
	BOOST_CHECK((!Namespace<reflexpr(V)>));
	BOOST_CHECK((!Namespace<reflexpr(V**)>));
	BOOST_CHECK((!Namespace<reflexpr(Z)>));
	BOOST_CHECK((!Namespace<reflexpr(Z&&)>));

	BOOST_CHECK((!Namespace<reflexpr(a)>));
	BOOST_CHECK((!Namespace<reflexpr(F::m)>));
	BOOST_CHECK((!Namespace<reflexpr(C::s)>));
	BOOST_CHECK((!Namespace<reflexpr(S::x)>));
	BOOST_CHECK((!Namespace<reflexpr(U::d)>));
	BOOST_CHECK((!Namespace<reflexpr(i)>));

	BOOST_CHECK((!Namespace<reflexpr(S::T)>));
	BOOST_CHECK((!Namespace<reflexpr(C::X)>));
	BOOST_CHECK((!Namespace<reflexpr(Z::T)>));

	BOOST_CHECK((!Namespace<reflexpr(static)>));
	BOOST_CHECK((!Namespace<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Namespace<meta_DbA>));
	BOOST_CHECK((!Namespace<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_GlobalScope)
{
	using namespace std::meta;

	BOOST_CHECK(( GlobalScope<reflexpr()>));
	BOOST_CHECK(( GlobalScope<reflexpr(::)>));
	BOOST_CHECK((!GlobalScope<reflexpr(std)>));
	BOOST_CHECK((!GlobalScope<reflexpr(int)>));
	BOOST_CHECK((!GlobalScope<reflexpr(int[10])>));
	BOOST_CHECK((!GlobalScope<reflexpr(E)>));
	BOOST_CHECK((!GlobalScope<reflexpr(E*)>));
	BOOST_CHECK((!GlobalScope<reflexpr(F)>));
	BOOST_CHECK((!GlobalScope<reflexpr(C)>));
	BOOST_CHECK((!GlobalScope<reflexpr(C*)>));
	BOOST_CHECK((!GlobalScope<reflexpr(S)>));
	BOOST_CHECK((!GlobalScope<reflexpr(S&)>));
	BOOST_CHECK((!GlobalScope<reflexpr(U)>));
	BOOST_CHECK((!GlobalScope<reflexpr(V)>));
	BOOST_CHECK((!GlobalScope<reflexpr(V**)>));
	BOOST_CHECK((!GlobalScope<reflexpr(Z)>));
	BOOST_CHECK((!GlobalScope<reflexpr(Z&&)>));

	BOOST_CHECK((!GlobalScope<reflexpr(a)>));
	BOOST_CHECK((!GlobalScope<reflexpr(F::m)>));
	BOOST_CHECK((!GlobalScope<reflexpr(C::s)>));
	BOOST_CHECK((!GlobalScope<reflexpr(S::x)>));
	BOOST_CHECK((!GlobalScope<reflexpr(U::d)>));
	BOOST_CHECK((!GlobalScope<reflexpr(i)>));

	BOOST_CHECK((!GlobalScope<reflexpr(S::T)>));
	BOOST_CHECK((!GlobalScope<reflexpr(C::X)>));
	BOOST_CHECK((!GlobalScope<reflexpr(Z::T)>));

	BOOST_CHECK((!GlobalScope<reflexpr(static)>));
	BOOST_CHECK((!GlobalScope<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!GlobalScope<meta_DbA>));
	BOOST_CHECK((!GlobalScope<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Type)
{
	using namespace std::meta;

	BOOST_CHECK((!Type<reflexpr()>));
	BOOST_CHECK((!Type<reflexpr(::)>));
	BOOST_CHECK((!Type<reflexpr(std)>));
	BOOST_CHECK(( Type<reflexpr(int)>));
	BOOST_CHECK(( Type<reflexpr(int[10])>));
	BOOST_CHECK(( Type<reflexpr(E)>));
	BOOST_CHECK(( Type<reflexpr(E*)>));
	BOOST_CHECK(( Type<reflexpr(F)>));
	BOOST_CHECK(( Type<reflexpr(C)>));
	BOOST_CHECK(( Type<reflexpr(C*)>));
	BOOST_CHECK(( Type<reflexpr(S)>));
	BOOST_CHECK(( Type<reflexpr(S&)>));
	BOOST_CHECK(( Type<reflexpr(U)>));
	BOOST_CHECK(( Type<reflexpr(V)>));
	BOOST_CHECK(( Type<reflexpr(V**)>));
	BOOST_CHECK(( Type<reflexpr(Z)>));
	BOOST_CHECK(( Type<reflexpr(Z&&)>));

	BOOST_CHECK((!Type<reflexpr(a)>));
	BOOST_CHECK((!Type<reflexpr(F::m)>));
	BOOST_CHECK((!Type<reflexpr(C::s)>));
	BOOST_CHECK((!Type<reflexpr(S::x)>));
	BOOST_CHECK((!Type<reflexpr(U::d)>));
	BOOST_CHECK((!Type<reflexpr(i)>));

	BOOST_CHECK(( Type<reflexpr(S::T)>));
	BOOST_CHECK(( Type<reflexpr(C::X)>));
	BOOST_CHECK(( Type<reflexpr(Z::T)>));

	BOOST_CHECK((!Type<reflexpr(static)>));
	BOOST_CHECK((!Type<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Type<meta_DbA>));
	BOOST_CHECK((!Type<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Record)
{
	using namespace std::meta;

	BOOST_CHECK((!Record<reflexpr()>));
	BOOST_CHECK((!Record<reflexpr(::)>));
	BOOST_CHECK((!Record<reflexpr(std)>));
	BOOST_CHECK((!Record<reflexpr(int)>));
	BOOST_CHECK((!Record<reflexpr(int[10])>));
	BOOST_CHECK((!Record<reflexpr(E)>));
	BOOST_CHECK((!Record<reflexpr(E*)>));
	BOOST_CHECK((!Record<reflexpr(F)>));
	BOOST_CHECK(( Record<reflexpr(C)>));
	BOOST_CHECK((!Record<reflexpr(C*)>));
	BOOST_CHECK(( Record<reflexpr(S)>));
	BOOST_CHECK((!Record<reflexpr(S&)>));
	BOOST_CHECK(( Record<reflexpr(U)>));
	BOOST_CHECK(( Record<reflexpr(V)>));
	BOOST_CHECK((!Record<reflexpr(V**)>));
	// TODO BOOST_CHECK(( Record<reflexpr(Z)>));
	BOOST_CHECK((!Record<reflexpr(Z&&)>));

	BOOST_CHECK((!Record<reflexpr(a)>));
	BOOST_CHECK((!Record<reflexpr(F::m)>));
	BOOST_CHECK((!Record<reflexpr(C::s)>));
	BOOST_CHECK((!Record<reflexpr(S::x)>));
	BOOST_CHECK((!Record<reflexpr(U::d)>));
	BOOST_CHECK((!Record<reflexpr(i)>));

	BOOST_CHECK((!Record<reflexpr(S::T)>));
	BOOST_CHECK(( Record<reflexpr(C::X)>));
	BOOST_CHECK((!Record<reflexpr(Z::T)>));

	BOOST_CHECK((!Record<reflexpr(static)>));
	BOOST_CHECK((!Record<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Record<meta_DbA>));
	BOOST_CHECK((!Record<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Class)
{
	using namespace std::meta;

	BOOST_CHECK((!Class<reflexpr()>));
	BOOST_CHECK((!Class<reflexpr(::)>));
	BOOST_CHECK((!Class<reflexpr(std)>));
	BOOST_CHECK((!Class<reflexpr(int)>));
	BOOST_CHECK((!Class<reflexpr(int[10])>));
	BOOST_CHECK((!Class<reflexpr(E)>));
	BOOST_CHECK((!Class<reflexpr(E*)>));
	BOOST_CHECK((!Class<reflexpr(F)>));
	BOOST_CHECK(( Class<reflexpr(C)>));
	BOOST_CHECK((!Class<reflexpr(C*)>));
	BOOST_CHECK(( Class<reflexpr(S)>));
	BOOST_CHECK((!Class<reflexpr(S&)>));
	// TODO BOOST_CHECK((!Class<reflexpr(U)>));
	BOOST_CHECK((!Class<reflexpr(V)>));
	BOOST_CHECK((!Class<reflexpr(V**)>));
	// TODO BOOST_CHECK(( Class<reflexpr(Z)>));
	BOOST_CHECK((!Class<reflexpr(Z&&)>));

	BOOST_CHECK((!Class<reflexpr(a)>));
	BOOST_CHECK((!Class<reflexpr(F::m)>));
	BOOST_CHECK((!Class<reflexpr(C::s)>));
	BOOST_CHECK((!Class<reflexpr(S::x)>));
	BOOST_CHECK((!Class<reflexpr(U::d)>));
	BOOST_CHECK((!Class<reflexpr(i)>));

	BOOST_CHECK((!Class<reflexpr(S::T)>));
	BOOST_CHECK(( Class<reflexpr(C::X)>));
	BOOST_CHECK((!Class<reflexpr(Z::T)>));

	BOOST_CHECK((!Class<reflexpr(static)>));
	BOOST_CHECK((!Class<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Class<meta_DbA>));
	BOOST_CHECK((!Class<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Enum)
{
	using namespace std::meta;

	BOOST_CHECK((!Enum<reflexpr()>));
	BOOST_CHECK((!Enum<reflexpr(::)>));
	BOOST_CHECK((!Enum<reflexpr(std)>));
	BOOST_CHECK((!Enum<reflexpr(int)>));
	BOOST_CHECK((!Enum<reflexpr(int[10])>));
	BOOST_CHECK(( Enum<reflexpr(E)>));
	BOOST_CHECK((!Enum<reflexpr(E*)>));
	BOOST_CHECK(( Enum<reflexpr(F)>));
	BOOST_CHECK((!Enum<reflexpr(C)>));
	BOOST_CHECK((!Enum<reflexpr(C*)>));
	BOOST_CHECK((!Enum<reflexpr(S)>));
	BOOST_CHECK((!Enum<reflexpr(S&)>));
	BOOST_CHECK((!Enum<reflexpr(U)>));
	BOOST_CHECK((!Enum<reflexpr(V)>));
	BOOST_CHECK((!Enum<reflexpr(V**)>));
	BOOST_CHECK((!Enum<reflexpr(Z)>));
	BOOST_CHECK((!Enum<reflexpr(Z&&)>));

	BOOST_CHECK((!Enum<reflexpr(a)>));
	BOOST_CHECK((!Enum<reflexpr(F::m)>));
	BOOST_CHECK((!Enum<reflexpr(C::s)>));
	BOOST_CHECK((!Enum<reflexpr(S::x)>));
	BOOST_CHECK((!Enum<reflexpr(U::d)>));
	BOOST_CHECK((!Enum<reflexpr(i)>));

	BOOST_CHECK((!Enum<reflexpr(S::T)>));
	BOOST_CHECK((!Enum<reflexpr(C::X)>));
	BOOST_CHECK((!Enum<reflexpr(Z::T)>));

	BOOST_CHECK((!Enum<reflexpr(static)>));
	BOOST_CHECK((!Enum<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Enum<meta_DbA>));
	BOOST_CHECK((!Enum<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Constant)
{
	using namespace std::meta;

	BOOST_CHECK((!Constant<reflexpr()>));
	BOOST_CHECK((!Constant<reflexpr(::)>));
	BOOST_CHECK((!Constant<reflexpr(std)>));
	BOOST_CHECK((!Constant<reflexpr(int)>));
	BOOST_CHECK((!Constant<reflexpr(int[10])>));
	BOOST_CHECK((!Constant<reflexpr(E)>));
	BOOST_CHECK((!Constant<reflexpr(E*)>));
	BOOST_CHECK((!Constant<reflexpr(F)>));
	BOOST_CHECK((!Constant<reflexpr(C)>));
	BOOST_CHECK((!Constant<reflexpr(C*)>));
	BOOST_CHECK((!Constant<reflexpr(S)>));
	BOOST_CHECK((!Constant<reflexpr(S&)>));
	BOOST_CHECK((!Constant<reflexpr(U)>));
	BOOST_CHECK((!Constant<reflexpr(V)>));
	BOOST_CHECK((!Constant<reflexpr(V**)>));
	BOOST_CHECK((!Constant<reflexpr(Z)>));
	BOOST_CHECK((!Constant<reflexpr(Z&&)>));

	BOOST_CHECK(( Constant<reflexpr(a)>));
	BOOST_CHECK(( Constant<reflexpr(F::m)>));
	BOOST_CHECK((!Constant<reflexpr(C::s)>));
	BOOST_CHECK((!Constant<reflexpr(S::x)>));
	BOOST_CHECK((!Constant<reflexpr(U::d)>));
	BOOST_CHECK((!Constant<reflexpr(i)>));

	BOOST_CHECK((!Constant<reflexpr(S::T)>));
	BOOST_CHECK((!Constant<reflexpr(C::X)>));
	BOOST_CHECK((!Constant<reflexpr(Z::T)>));

	BOOST_CHECK((!Constant<reflexpr(static)>));
	BOOST_CHECK((!Constant<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Constant<meta_DbA>));
	BOOST_CHECK((!Constant<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Variable)
{
	using namespace std::meta;

	BOOST_CHECK((!Variable<reflexpr()>));
	BOOST_CHECK((!Variable<reflexpr(::)>));
	BOOST_CHECK((!Variable<reflexpr(std)>));
	BOOST_CHECK((!Variable<reflexpr(int)>));
	BOOST_CHECK((!Variable<reflexpr(int[10])>));
	BOOST_CHECK((!Variable<reflexpr(E)>));
	BOOST_CHECK((!Variable<reflexpr(E*)>));
	BOOST_CHECK((!Variable<reflexpr(F)>));
	BOOST_CHECK((!Variable<reflexpr(C)>));
	BOOST_CHECK((!Variable<reflexpr(C*)>));
	BOOST_CHECK((!Variable<reflexpr(S)>));
	BOOST_CHECK((!Variable<reflexpr(S&)>));
	BOOST_CHECK((!Variable<reflexpr(U)>));
	BOOST_CHECK((!Variable<reflexpr(V)>));
	BOOST_CHECK((!Variable<reflexpr(V**)>));
	BOOST_CHECK((!Variable<reflexpr(Z)>));
	BOOST_CHECK((!Variable<reflexpr(Z&&)>));

	BOOST_CHECK((!Variable<reflexpr(a)>));
	BOOST_CHECK((!Variable<reflexpr(F::m)>));
	BOOST_CHECK(( Variable<reflexpr(C::s)>));
	BOOST_CHECK(( Variable<reflexpr(S::x)>));
	BOOST_CHECK(( Variable<reflexpr(U::d)>));
	BOOST_CHECK(( Variable<reflexpr(i)>));

	BOOST_CHECK((!Variable<reflexpr(S::T)>));
	BOOST_CHECK((!Variable<reflexpr(C::X)>));
	BOOST_CHECK((!Variable<reflexpr(Z::T)>));

	BOOST_CHECK((!Variable<reflexpr(static)>));
	BOOST_CHECK((!Variable<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Variable<meta_DbA>));
	BOOST_CHECK((!Variable<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Specifier)
{
	using namespace std::meta;

	BOOST_CHECK((!Specifier<reflexpr()>));
	BOOST_CHECK((!Specifier<reflexpr(::)>));
	BOOST_CHECK((!Specifier<reflexpr(std)>));
	BOOST_CHECK((!Specifier<reflexpr(int)>));
	BOOST_CHECK((!Specifier<reflexpr(int[10])>));
	BOOST_CHECK((!Specifier<reflexpr(E)>));
	BOOST_CHECK((!Specifier<reflexpr(E*)>));
	BOOST_CHECK((!Specifier<reflexpr(F)>));
	BOOST_CHECK((!Specifier<reflexpr(C)>));
	BOOST_CHECK((!Specifier<reflexpr(C*)>));
	BOOST_CHECK((!Specifier<reflexpr(S)>));
	BOOST_CHECK((!Specifier<reflexpr(S&)>));
	BOOST_CHECK((!Specifier<reflexpr(U)>));
	BOOST_CHECK((!Specifier<reflexpr(V)>));
	BOOST_CHECK((!Specifier<reflexpr(V**)>));
	BOOST_CHECK((!Specifier<reflexpr(Z)>));
	BOOST_CHECK((!Specifier<reflexpr(Z&&)>));

	BOOST_CHECK((!Specifier<reflexpr(a)>));
	BOOST_CHECK((!Specifier<reflexpr(F::m)>));
	BOOST_CHECK((!Specifier<reflexpr(C::s)>));
	BOOST_CHECK((!Specifier<reflexpr(S::x)>));
	BOOST_CHECK((!Specifier<reflexpr(U::d)>));
	BOOST_CHECK((!Specifier<reflexpr(i)>));

	BOOST_CHECK((!Specifier<reflexpr(S::T)>));
	BOOST_CHECK((!Specifier<reflexpr(C::X)>));
	BOOST_CHECK((!Specifier<reflexpr(Z::T)>));

	BOOST_CHECK(( Specifier<reflexpr(static)>));
	BOOST_CHECK(( Specifier<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK((!Specifier<meta_DbA>));
	BOOST_CHECK((!Specifier<meta_DbB>));
}

BOOST_AUTO_TEST_CASE(mirror_concepts_Inheritance)
{
	using namespace std::meta;

	BOOST_CHECK((!Inheritance<reflexpr()>));
	BOOST_CHECK((!Inheritance<reflexpr(::)>));
	BOOST_CHECK((!Inheritance<reflexpr(std)>));
	BOOST_CHECK((!Inheritance<reflexpr(int)>));
	BOOST_CHECK((!Inheritance<reflexpr(int[10])>));
	BOOST_CHECK((!Inheritance<reflexpr(E)>));
	BOOST_CHECK((!Inheritance<reflexpr(E*)>));
	BOOST_CHECK((!Inheritance<reflexpr(F)>));
	BOOST_CHECK((!Inheritance<reflexpr(C)>));
	BOOST_CHECK((!Inheritance<reflexpr(C*)>));
	BOOST_CHECK((!Inheritance<reflexpr(S)>));
	BOOST_CHECK((!Inheritance<reflexpr(S&)>));
	BOOST_CHECK((!Inheritance<reflexpr(U)>));
	BOOST_CHECK((!Inheritance<reflexpr(V)>));
	BOOST_CHECK((!Inheritance<reflexpr(V**)>));
	BOOST_CHECK((!Inheritance<reflexpr(Z)>));
	BOOST_CHECK((!Inheritance<reflexpr(Z&&)>));

	BOOST_CHECK((!Inheritance<reflexpr(a)>));
	BOOST_CHECK((!Inheritance<reflexpr(F::m)>));
	BOOST_CHECK((!Inheritance<reflexpr(C::s)>));
	BOOST_CHECK((!Inheritance<reflexpr(S::x)>));
	BOOST_CHECK((!Inheritance<reflexpr(U::d)>));
	BOOST_CHECK((!Inheritance<reflexpr(i)>));

	BOOST_CHECK((!Inheritance<reflexpr(S::T)>));
	BOOST_CHECK((!Inheritance<reflexpr(C::X)>));
	BOOST_CHECK((!Inheritance<reflexpr(Z::T)>));

	BOOST_CHECK((!Inheritance<reflexpr(static)>));
	BOOST_CHECK((!Inheritance<reflexpr(public)>));

	using meta_DbA = get_element_m<get_base_classes_m<reflexpr(D)>, 0>; 
	using meta_DbB = get_element_m<get_base_classes_m<reflexpr(D)>, 1>; 

	BOOST_CHECK(( Inheritance<meta_DbA>));
	BOOST_CHECK(( Inheritance<meta_DbB>));
}

// TODO

BOOST_AUTO_TEST_SUITE_END()

