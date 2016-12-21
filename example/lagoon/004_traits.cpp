/**
 * @example lagoon/004_traits.cpp
 * @brief Metaobject traits
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <lagoon/metaobject_registry.hpp>
#include <lagoon/metaobject.hpp>
#include <puddle/reflection.hpp>
#include <iostream>

enum E { a, b, c };
class C { public: long l; short s; struct X { }; };
struct S { using T = int; T x, y, z; };
union U { float f; double d; };

static int i = 0;


int main(void)
{
	using namespace lagoon;

	metaobject_registry reg;

	auto m_ = reg << PUDDLED(::);
	auto m_std = reg << PUDDLED(std);
	auto m_int = reg << PUDDLED(int);
	auto m_szt = reg << PUDDLED(std::size_t);

	auto m_E = reg << PUDDLED(E);
	auto m_C = reg << PUDDLED(C);
	auto m_S = reg << PUDDLED(S);
	auto m_U = reg << PUDDLED(U);
	auto m_a = reg << PUDDLED(a);
	auto m_i = reg << PUDDLED(i);

	auto m_C_l = reg << PUDDLED(C::l);
	auto m_S_x = reg << PUDDLED(S::x);
	auto m_U_f = reg << PUDDLED(U::f);

	auto m_static = reg << PUDDLED(static);
	auto m_public = reg << PUDDLED(public);

	assert( m_.reflects_global_scope());
	assert( m_.reflects_namespace());
	assert( m_std.reflects_namespace());

	assert( m_int.reflects_type());
	assert( m_szt.reflects_type());
	assert( m_szt.reflects_alias());

	assert( m_E.reflects_tag_type());
	assert( m_C.reflects_tag_type());
	assert( m_S.reflects_tag_type());
	assert( m_U.reflects_tag_type());

	assert( m_E.reflects_enum());

	assert( m_C.reflects_record());
	assert( m_S.reflects_record());
	assert( m_U.reflects_record());

	assert( m_C.reflects_class());
	assert( m_S.reflects_class());

	assert( m_i.reflects_variable());

	assert( m_a.reflects_enum_member());
	assert( m_a.reflects_constant());

	assert( m_C_l.reflects_record_member());
	assert( m_S_x.reflects_record_member());
	assert( m_U_f.reflects_record_member());

	assert( m_C_l.reflects_variable());
	assert( m_S_x.reflects_variable());
	assert( m_U_f.reflects_variable());

	assert( m_static.reflects_specifier());
	assert( m_public.reflects_specifier());

	return i;
}
