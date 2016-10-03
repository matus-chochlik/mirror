/**
 * @example reflexpr/003_specifiers.cpp
 * @brief Basic examples of specifier reflection.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>

struct S
{
private:
	int i;
public:
	float f;

	int get_i(void) const { return i; }
};

int main(void)
{
	using namespace std;

	using meta_S = reflexpr(S);
	using meta_S_i = meta::get_element_m<meta::get_data_members_m<meta_S>, 0>;
	using meta_S_f = meta::get_element_m<meta::get_data_members_m<meta_S>, 1>;

	using meta::reflects_same_v;
	using meta::get_access_specifier_m;

	static_assert( reflects_same_v<
		reflexpr(private),
		get_access_specifier_m<meta_S_i>
	>, "");
	static_assert(!reflects_same_v<
		reflexpr(public),
		get_access_specifier_m<meta_S_i>
	>, "");
	static_assert( reflects_same_v<
		reflexpr(public),
		get_access_specifier_m<meta_S_f>
	>, "");

	static_assert( meta::is_private_v<meta_S_i>, "");
	static_assert(!meta::is_public_v<meta_S_i>, "");
	static_assert( meta::is_public_v<meta_S_f>, "");

	return 0;
}
