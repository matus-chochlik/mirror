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

	r.reg(PUDDLED(int));
	r.reg(PUDDLED(bool));
	r.reg(PUDDLED(unsigned));
	r.reg(PUDDLED(float));

	r.reg(PUDDLED(foo));
	r.reg(PUDDLED(foo::A));
	r.reg_data_members(PUDDLED(foo::A));
	//r.reg_member_types(PUDDLED(foo::A));
	r.reg(PUDDLED(foo::B));
	r.reg_data_members(PUDDLED(foo::B));
	//r.reg_member_types(PUDDLED(foo::B));
	r.reg(PUDDLED(foo::bar));
	r.reg(PUDDLED(foo::bar::C));
	r.reg(PUDDLED(foo::bar::D));
	r.reg(PUDDLED(foo::bar::baz));
	r.reg(PUDDLED(foo::bar::baz::E));
	r.reg_enumerators(PUDDLED(foo::bar::baz::E));
	r.reg(PUDDLED(foo::bar::U));
	r.reg_data_members(PUDDLED(foo::bar::U));

	print_members(r.reg(PUDDLED(::)));

	return 0;
}
