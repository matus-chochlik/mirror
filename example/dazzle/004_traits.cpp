/**
 * @example dazzle/004_traits.cpp
 * @brief Metaobject categorization traits
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/reflection.hpp>
#include <dazzle/metaobject.hpp>

enum E { a, b, c };
class C { public: long l; short s; struct X { }; };
struct S { using T = int; T x, y, z; };
union U { float f; double d; };

static int i = 0;

int main(void)
{
	using namespace dazzle;

	static_assert( DAZZLED().reflects_global_scope());
	static_assert( DAZZLED(::).reflects_global_scope());
	static_assert( DAZZLED().reflects_namespace());
	static_assert( DAZZLED(std).reflects_namespace());

	static_assert( DAZZLED(int).reflects_type());
	static_assert( DAZZLED(std::size_t).reflects_type());
	static_assert( DAZZLED(std::size_t).reflects_alias());

	static_assert( DAZZLED(C::X).reflects_type());
	static_assert( DAZZLED(C::X).reflects_record_member());

	static_assert( DAZZLED(S::T).reflects_type());
	static_assert( DAZZLED(S::T).reflects_alias());
	static_assert( DAZZLED(S::T).reflects_record_member());

	static_assert( DAZZLED(E).reflects_tag_type());
	static_assert( DAZZLED(C).reflects_tag_type());
	static_assert( DAZZLED(S).reflects_tag_type());
	static_assert( DAZZLED(U).reflects_tag_type());

	static_assert( DAZZLED(E).reflects_enum());
	static_assert( DAZZLED(C).reflects_record());
	static_assert( DAZZLED(S).reflects_record());
	static_assert( DAZZLED(U).reflects_record());

	static_assert( DAZZLED(C).reflects_class());
	static_assert( DAZZLED(S).reflects_class());

	static_assert( DAZZLED(i).reflects_variable());

	static_assert( DAZZLED(a).reflects_enum_member());
	static_assert( DAZZLED(a).reflects_constant());

	static_assert( DAZZLED(C::l).reflects_record_member());
	static_assert( DAZZLED(S::x).reflects_record_member());
	static_assert( DAZZLED(U::f).reflects_record_member());

	static_assert( DAZZLED(C::l).reflects_variable());
	static_assert( DAZZLED(S::x).reflects_variable());
	static_assert( DAZZLED(U::f).reflects_variable());

	static_assert( DAZZLED(static).reflects_specifier());
	static_assert( DAZZLED(private).reflects_specifier());

	return i;
}
