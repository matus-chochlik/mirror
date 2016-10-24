/**
 * @example mirror/004_traits.cpp
 * @brief Metaobject categorization traits
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/reflection.hpp>
#include <mirror/traits.hpp>
#include <mirror/value.hpp>

enum E { a, b, c };
class C { public: long l; short s; struct X { }; };
struct S { using T = int; T x, y, z; };
union U { float f; double d; };

static int i = 0;

int main(void)
{
	using namespace mirror;

	static_assert( value<reflects_global_scope<MIRRORED()>>);
	static_assert( value<reflects_global_scope<MIRRORED(::)>>);
	static_assert( value<reflects_namespace<MIRRORED()>>);
	static_assert( value<reflects_namespace<MIRRORED(std)>>);

	static_assert( value<reflects_type<MIRRORED(int)>>);
	static_assert( value<reflects_type<MIRRORED(std::size_t)>>);
	static_assert( value<reflects_alias<MIRRORED(std::size_t)>>);

	static_assert( value<reflects_type<MIRRORED(C::X)>>);
	static_assert( value<reflects_record_member<MIRRORED(C::X)>>);

	static_assert( value<reflects_type<MIRRORED(S::T)>>);
	static_assert( value<reflects_alias<MIRRORED(S::T)>>);
	static_assert( value<reflects_record_member<MIRRORED(S::T)>>);

	static_assert( value<reflects_tag_type<MIRRORED(E)>>);
	static_assert( value<reflects_tag_type<MIRRORED(C)>>);
	static_assert( value<reflects_tag_type<MIRRORED(S)>>);
	static_assert( value<reflects_tag_type<MIRRORED(U)>>);

	static_assert( value<reflects_enum<MIRRORED(E)>>);
	static_assert( value<reflects_record<MIRRORED(C)>>);
	static_assert( value<reflects_record<MIRRORED(S)>>);
	static_assert( value<reflects_record<MIRRORED(U)>>);

	static_assert( value<reflects_class<MIRRORED(C)>>);
	static_assert( value<reflects_class<MIRRORED(S)>>);

	static_assert( value<reflects_variable<MIRRORED(i)>>);

	static_assert( value<reflects_enum_member<MIRRORED(a)>>);
	static_assert( value<reflects_constant<MIRRORED(a)>>);

	static_assert( value<reflects_record_member<MIRRORED(C::l)>>);
	static_assert( value<reflects_record_member<MIRRORED(S::x)>>);
	static_assert( value<reflects_record_member<MIRRORED(U::f)>>);

	static_assert( value<reflects_variable<MIRRORED(C::l)>>);
	static_assert( value<reflects_variable<MIRRORED(S::x)>>);
	static_assert( value<reflects_variable<MIRRORED(U::f)>>);

	static_assert( value<reflects_specifier<MIRRORED(static)>>);
	static_assert( value<reflects_specifier<MIRRORED(private)>>);

	return i;
}
