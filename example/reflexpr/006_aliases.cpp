/**
 * @example reflexpr/006_aliased.cpp
 * @brief Basic examples of the get_aliased operation.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>

using A = int;
using B = const A;
using C = B*;

template <typename T>
struct S
{
	using X = T&;
};

int main(void)
{
	using namespace std;

	static_assert( meta::Type<reflexpr(A)>, "");
	static_assert( meta::Alias<reflexpr(A)>, "");
	static_assert( meta::Type<meta::get_aliased_m<reflexpr(A)>>, "");
	static_assert(!meta::Alias<meta::get_aliased_m<reflexpr(A)>>, "");

	static_assert( meta::Type<reflexpr(B)>, "");
	static_assert( meta::Alias<reflexpr(B)>, "");
	static_assert( meta::Type<meta::get_aliased_m<reflexpr(B)>>, "");
	static_assert(!meta::Alias<meta::get_aliased_m<reflexpr(B)>>, "");

	static_assert( meta::Type<reflexpr(C)>, "");
	static_assert( meta::Alias<reflexpr(C)>, "");
	static_assert( meta::Type<meta::get_aliased_m<reflexpr(C)>>, "");
	static_assert(!meta::Alias<meta::get_aliased_m<reflexpr(C)>>, "");

	static_assert(meta::reflects_same_v<
		meta::get_aliased_m<reflexpr(A)>,
		reflexpr(int)
	>, "");

	static_assert(meta::reflects_same_v<
		meta::get_aliased_m<reflexpr(B)>,
		reflexpr(const int)
	>, "");

	static_assert(meta::reflects_same_v<
		meta::get_aliased_m<reflexpr(C)>,
		reflexpr(const int *)
	>, "");

	static_assert(meta::reflects_same_v<
		meta::get_aliased_m<reflexpr(S<A>::X)>,
		reflexpr(int &)
	>, "");

	static_assert(meta::reflects_same_v<
		meta::get_aliased_m<reflexpr(S<B>::X)>,
		reflexpr(const int &)
	>, "");

	static_assert(meta::reflects_same_v<
		meta::get_aliased_m<reflexpr(S<C>::X)>,
		reflexpr(const int * &)
	>, "");

	cout << meta::get_base_name_v<reflexpr(S<C>::X)> << endl;
	cout << meta::get_base_name_v<reflexpr(S<B>::X)> << endl;
	cout << meta::get_base_name_v<reflexpr(S<A>::X)> << endl;
	cout << meta::get_base_name_v<reflexpr(C)> << endl;
	cout << meta::get_base_name_v<reflexpr(B)> << endl;
	cout << meta::get_base_name_v<reflexpr(A)> << endl;

	cout << meta::get_base_name_v<meta::get_aliased_m<reflexpr(S<C>::X)>> << endl;
	cout << meta::get_base_name_v<meta::get_aliased_m<reflexpr(S<B>::X)>> << endl;
	cout << meta::get_base_name_v<meta::get_aliased_m<reflexpr(S<A>::X)>> << endl;
	cout << meta::get_base_name_v<meta::get_aliased_m<reflexpr(C)>> << endl;
	cout << meta::get_base_name_v<meta::get_aliased_m<reflexpr(B)>> << endl;
	cout << meta::get_base_name_v<meta::get_aliased_m<reflexpr(A)>> << endl;

	return 0;
}
