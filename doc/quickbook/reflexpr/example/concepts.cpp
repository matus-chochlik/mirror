/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[reflexpr_example_concepts_1
#include <reflexpr>
#include <cstdint>
//]
//[reflexpr_example_concepts_2
enum E { a, b, c };
class C { public: long l; short s; struct X { }; };
struct S { using T = int; T x, y, z; };
union U { float f; double d; };

static int i = 0;
//]
//[reflexpr_example_concepts_3
int main(void)
{
	using namespace std::meta;

//]
//[reflexpr_example_concepts_4
	static_assert( __GlobalScope<__reflexpr()>);
	static_assert( GlobalScope<reflexpr(::)>); /*<
	The global scope can be reflected with either of these two expressions.
	>*/
	static_assert( __Namespace<reflexpr()>); /*<
	The global scope is also considered to be a namespace.
	>*/
	static_assert( Namespace<reflexpr(std)>);

	static_assert( __Type<reflexpr(int)>);
	static_assert( Type<reflexpr(std::size_t)>);
	static_assert( __Alias<reflexpr(std::size_t)>); /*<
	The reflection of [^size_t] is both a [^__Type] and an [^__Alias].
	>*/

	static_assert( Type<reflexpr(C::X)>);
	static_assert( __RecordMember<reflexpr(C::X)>); /*<
	Public record members can be reflected directly.
	>*/

	static_assert( Type<reflexpr(S::T)>);
	static_assert( Alias<reflexpr(S::T)>);
	static_assert( RecordMember<reflexpr(S::T)>);

	static_assert( __TagType<reflexpr(E)>);
	static_assert( TagType<reflexpr(C)>);
	static_assert( TagType<reflexpr(S)>);
	static_assert( TagType<reflexpr(U)>);

	static_assert( __Enum<reflexpr(E)>);
	static_assert( __Record<reflexpr(C)>);
	static_assert( Record<reflexpr(S)>);
	static_assert( Record<reflexpr(U)>);
	static_assert( __Class<reflexpr(C)>);
	static_assert( Class<reflexpr(S)>);

	static_assert( __Variable<reflexpr(i)>); /*<
	Namespace-level variables can be reflected directly.
	>*/

	static_assert( __EnumMember<reflexpr(a)>);
	static_assert( __Constant<reflexpr(a)>); /*<
	Enumerators can be reflected directly.
	>*/

	static_assert( __RecordMember<reflexpr(C::l)>);
	static_assert( RecordMember<reflexpr(S::x)>);
	static_assert( RecordMember<reflexpr(U::f)>);

	static_assert( __Variable<reflexpr(C::l)>);
	static_assert( Variable<reflexpr(S::x)>);
	static_assert( Variable<reflexpr(U::f)>);

	static_assert( __Specifier<reflexpr(static)>);
	static_assert( Specifier<reflexpr(private)>); /*<
	Specifier reflection.
>*/
//]
//[reflexpr_example_concepts_end

	return i;
}
//]
