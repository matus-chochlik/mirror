/**
 * @example lagoon/012_member_tree.cpp
 * @brief Recursively lists namespace members
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

namespace foo {

struct A {
	using a_t = int;
	a_t a;
};

struct B
{
	using b_t = bool;
	b_t b;
};

namespace bar {

class C { };
class D { };

namespace baz {

enum E { x, y, z };

} // namespace baz

union U {
	float f;
	unsigned u;
};

} // namespace bar

} // namespace foo

void print_members(const lagoon::shared_metaobject& mo, std::size_t indent = 0)
{
	std::cout
		<< std::string(indent, ' ')
		<< mo.get_base_name();

	auto mseq = mo.get_members();
	if(!mseq.empty()) {
		std::cout
			<< " {"
			<< std::endl;

		for(auto mmo : mseq) {
			print_members(mmo, indent + 2);
		}

		std::cout
			<< std::string(indent, ' ')
			<< "}";
	}
	std::cout << std::endl;
}

int main(void)
{
	using namespace lagoon;

	metaobject_registry r;

	r << PUDDLED(int);
	r << PUDDLED(bool);
	r << PUDDLED(unsigned);
	r << PUDDLED(float);

	r << PUDDLED(foo);
	r << PUDDLED(foo::A);
	r.data_members << PUDDLED(foo::A);
	r << PUDDLED(foo::B);
	r.data_members << PUDDLED(foo::B);
	r << PUDDLED(foo::bar);
	r << PUDDLED(foo::bar::C);
	r << PUDDLED(foo::bar::D);
	r << PUDDLED(foo::bar::baz);
	r << PUDDLED(foo::bar::baz::E);
	r.enumerators << PUDDLED(foo::bar::baz::E);
	r << PUDDLED(foo::bar::U);
	r.data_members << PUDDLED(foo::bar::U);

	print_members(r << PUDDLED(::));

	return 0;
}
