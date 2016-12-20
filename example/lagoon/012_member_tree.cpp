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

	r.add(PUDDLED(int));
	r.add(PUDDLED(bool));
	r.add(PUDDLED(unsigned));
	r.add(PUDDLED(float));

	r.add(PUDDLED(foo));
	r.add(PUDDLED(foo::A));
	r.add_data_members(PUDDLED(foo::A));
	//r.add_member_types(PUDDLED(foo::A));
	r.add(PUDDLED(foo::B));
	r.add_data_members(PUDDLED(foo::B));
	//r.add_member_types(PUDDLED(foo::B));
	r.add(PUDDLED(foo::bar));
	r.add(PUDDLED(foo::bar::C));
	r.add(PUDDLED(foo::bar::D));
	r.add(PUDDLED(foo::bar::baz));
	r.add(PUDDLED(foo::bar::baz::E));
	r.add_enumerators(PUDDLED(foo::bar::baz::E));
	r.add(PUDDLED(foo::bar::U));
	r.add_data_members(PUDDLED(foo::bar::U));

	print_members(r.add(PUDDLED(::)));

	return 0;
}
