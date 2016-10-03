/**
 * @example lagoon/010_list_data_members.cpp
 * @brief Lists all data members of a class
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

struct A
{
	int a;
};

struct B
{
	bool b;
};

struct C
{
	char c;
};

struct D
{
	double d;
};

struct ABCDE
 : A, B, C, D
{
	float e;
};

int main(void)
{
	using namespace lagoon;

	metaobject_registry r;

	r.reg(PUDDLED(public));
	r.reg(PUDDLED(int));
	r.reg(PUDDLED(bool));
	r.reg(PUDDLED(char));
	r.reg(PUDDLED(double));
	r.reg(PUDDLED(float));
	r.reg(PUDDLED(A));
	r.reg(PUDDLED(B));
	r.reg(PUDDLED(C));
	r.reg(PUDDLED(D));

	r.reg_data_members(PUDDLED(A));
	r.reg_data_members(PUDDLED(B));
	r.reg_data_members(PUDDLED(C));
	r.reg_data_members(PUDDLED(D));
	r.reg_base_classes(PUDDLED(ABCDE));
	r.reg_data_members(PUDDLED(ABCDE));

	auto m_abcde = r.reg(PUDDLED(ABCDE));

	for(auto m_b : m_abcde.get_base_classes())
	{
		for(auto m_dm : m_b.get_base_class().get_data_members())
		{
			std::cout
				<< m_dm.get_type().get_full_name()
				<< " "
				<< m_dm.get_full_name()
				<< std::endl;
		}
	}
	for(auto m_dm : m_abcde.get_data_members())
	{
		std::cout
			<< m_dm.get_type().get_full_name()
			<< " "
			<< m_dm.get_full_name()
			<< std::endl;
	}

	return 0;
}
