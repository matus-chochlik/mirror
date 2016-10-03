/**
 * @example reflexpr/005_class_members.cpp
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
private:
	typedef int _attr_t;
	_attr_t _a, _b, _c;
public:
	foo(void) : _a(0), _b(1), _c(2) { }
	int get(void) { return _a + _b + _c; }

	typedef float value_type;
	typedef size_t size_type;
	value_type d;
};

int main(void)
{
	using namespace std;

	using meta_foo = reflexpr(foo);

	using meta::get_size_v;
	using meta::get_base_name_v;
	using meta::get_element_m;
	using meta::get_data_members_m;
	using meta::get_public_data_members_m;
	using meta::get_member_types_m;
	using meta::get_public_member_types_m;

	cout << get_size_v<get_data_members_m<meta_foo>> << endl;
	cout << get_size_v<get_public_data_members_m<meta_foo>> << endl;

	cout << get_size_v<get_member_types_m<meta_foo>> << endl;
	cout << get_size_v<get_public_member_types_m<meta_foo>> << endl;

	cout << get_base_name_v<get_element_m<get_data_members_m<meta_foo>, 0>> << endl;
	cout << get_base_name_v<get_element_m<get_data_members_m<meta_foo>, 1>> << endl;
	cout << get_base_name_v<get_element_m<get_data_members_m<meta_foo>, 2>> << endl;
	cout << get_base_name_v<get_element_m<get_public_data_members_m<meta_foo>, 0>> << endl;

	cout << get_base_name_v<get_element_m<get_member_types_m<meta_foo>, 0>> << endl;
	cout << get_base_name_v<get_element_m<get_public_member_types_m<meta_foo>, 0>> << endl;
	cout << get_base_name_v<get_element_m<get_public_member_types_m<meta_foo>, 1>> << endl;

	return 0;
}
