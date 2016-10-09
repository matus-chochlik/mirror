/**
 * @example reflexpr/002_concepts.cpp
 * @brief Metaobject concepts
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <cstdint>

enum E { a, b, c };
class C { public: long l; short s; struct X { }; };
struct S { using T = int; T x, y, z; };
union U { float f; double d; };

static int i = 0;

int main(void)
{
	using namespace std::meta;

	static_assert( GlobalScope<reflexpr()>);
	static_assert( GlobalScope<reflexpr(::)>);
	static_assert( Namespace<reflexpr()>);
	static_assert( Namespace<reflexpr(std)>);

	static_assert( Type<reflexpr(int)>);
	static_assert( Type<reflexpr(std::size_t)>);
	static_assert( Alias<reflexpr(std::size_t)>);

	static_assert( Type<reflexpr(C::X)>);
	static_assert( RecordMember<reflexpr(C::X)>);

	static_assert( Type<reflexpr(S::T)>);
	static_assert( Alias<reflexpr(S::T)>);
	static_assert( RecordMember<reflexpr(S::T)>);

	static_assert( TagType<reflexpr(E)>);
	static_assert( TagType<reflexpr(C)>);
	static_assert( TagType<reflexpr(S)>);
	static_assert( TagType<reflexpr(U)>);

	static_assert( Enum<reflexpr(E)>);
	static_assert( Record<reflexpr(C)>);
	static_assert( Record<reflexpr(S)>);
	static_assert( Record<reflexpr(U)>);
	static_assert( Class<reflexpr(C)>);
	static_assert( Class<reflexpr(S)>);

	static_assert( Variable<reflexpr(i)>);

	static_assert( EnumMember<reflexpr(a)>);
	static_assert( Constant<reflexpr(a)>);

	static_assert( RecordMember<reflexpr(C::l)>);
	static_assert( RecordMember<reflexpr(S::x)>);
	static_assert( RecordMember<reflexpr(U::f)>);

	static_assert( Variable<reflexpr(C::l)>);
	static_assert( Variable<reflexpr(S::x)>);
	static_assert( Variable<reflexpr(U::f)>);

	static_assert( Specifier<reflexpr(static)>);
	static_assert( Specifier<reflexpr(private)>);

	return i;
}
