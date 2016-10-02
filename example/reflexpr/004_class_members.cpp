/**
 * @example reflexpr/004_class_members.cpp
 * @brief Basic examples of class member reflection.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>

struct foo
{
	typedef int t1;
	typedef float t2;

	t1 a, b, c;
	t2 d;
};

int main(void)
{
	using namespace std;

	using meta_foo = reflexpr(foo);

	using meta::get_base_name_v;
	using meta::get_element_m;
	using meta::get_data_members_m;
	using meta::get_member_types_m;

	cout << get_base_name_v<get_element_m<get_member_types_m<meta_foo>, 0>> << endl;
	cout << get_base_name_v<get_element_m<get_member_types_m<meta_foo>, 1>> << endl;

	cout << get_base_name_v<get_element_m<get_data_members_m<meta_foo>, 0>> << endl;
	cout << get_base_name_v<get_element_m<get_data_members_m<meta_foo>, 1>> << endl;
	cout << get_base_name_v<get_element_m<get_data_members_m<meta_foo>, 2>> << endl;
	cout << get_base_name_v<get_element_m<get_data_members_m<meta_foo>, 3>> << endl;

	return 0;
}
