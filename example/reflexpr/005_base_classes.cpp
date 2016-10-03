/**
 * @example reflexpr/005_base_classes.cpp
 * @brief Basic examples of base class reflection.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>

struct A { int a; };
struct B : virtual A { bool b; };
struct C : virtual A { char c; };

class D
 : virtual private A
 , protected B
 , public C
{ };


int main(void)
{
	using namespace std;

	using meta_D = reflexpr(D);

	using meta::get_base_name_v;
	using meta::get_base_class_m;
	using meta::get_base_classes_m;
	using meta::get_access_specifier_m;
	using meta::is_virtual_v;
	using meta::get_element_m;

	using meta_D_base = get_base_classes_m<meta_D>;

	cout << get_base_name_v<get_base_class_m<get_element_m<meta_D_base, 0>>> << endl;
	cout << get_base_name_v<get_base_class_m<get_element_m<meta_D_base, 1>>> << endl;
	cout << get_base_name_v<get_base_class_m<get_element_m<meta_D_base, 2>>> << endl;

	cout << get_base_name_v<get_access_specifier_m<get_element_m<meta_D_base, 0>>> << endl;
	cout << get_base_name_v<get_access_specifier_m<get_element_m<meta_D_base, 1>>> << endl;
	cout << get_base_name_v<get_access_specifier_m<get_element_m<meta_D_base, 2>>> << endl;

	cout << is_virtual_v<get_element_m<meta_D_base, 0>> << endl;
	cout << is_virtual_v<get_element_m<meta_D_base, 1>> << endl;
	cout << is_virtual_v<get_element_m<meta_D_base, 2>> << endl;

	return 0;
}
