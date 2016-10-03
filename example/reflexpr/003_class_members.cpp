/**
 * @example reflexpr/003_class_members.cpp
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
	typedef int attr_t;
	attr_t a, b, c, d;
};

struct bar : foo
{
	float e, f;
};

int main(void)
{
	using namespace std;

	using meta_foo = reflexpr(foo);
	using meta_bar = reflexpr(bar);

	using meta::get_size_v;
	using meta::get_data_members_m;
	using meta::get_member_types_m;

	cout << get_size_v<get_data_members_m<meta_foo>> << endl;
	cout << get_size_v<get_data_members_m<meta_bar>> << endl;

	cout << get_size_v<get_member_types_m<meta_foo>> << endl;
	cout << get_size_v<get_member_types_m<meta_bar>> << endl;

	return 0;
}
