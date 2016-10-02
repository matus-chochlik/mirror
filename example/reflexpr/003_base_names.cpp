/**
 * @example reflexpr/003_base_named.cpp
 * @brief Basic examples of the get_base_name operation.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>
#include <vector>
#include <set>
#include <chrono>
#include <future>

using foo = int;
using bar = foo;
namespace baz = std;

typedef foo (*pfoo)(double);

int main(void)
{
	using namespace std;

	cout << meta::get_base_name_v<reflexpr(unsigned)> << endl;
	cout << meta::get_base_name_v<reflexpr(short)> << endl;
	cout << meta::get_base_name_v<reflexpr(long long)> << endl;
	cout << meta::get_base_name_v<reflexpr(signed char)> << endl;
	cout << meta::get_base_name_v<reflexpr(unsigned char)> << endl;
	cout << meta::get_base_name_v<reflexpr(char)> << endl;

	cout << meta::get_base_name_v<reflexpr(foo)> << endl;
	cout << meta::get_base_name_v<reflexpr(bar)> << endl;
	cout << meta::get_base_name_v<reflexpr(baz)> << endl;
	cout << meta::get_base_name_v<reflexpr(pfoo)> << endl;

	cout << meta::get_base_name_v<reflexpr(vector<int>)> << endl;
	cout << meta::get_base_name_v<reflexpr(volatile size_t* [10])> << endl;
	cout << meta::get_base_name_v<reflexpr(set<int>* (*)(vector<double>&))> << endl;
	cout << meta::get_base_name_v<reflexpr(chrono)> << endl;
	cout << meta::get_base_name_v<reflexpr(launch)> << endl;
	cout << meta::get_base_name_v<reflexpr(static)> << endl;
	cout << meta::get_base_name_v<reflexpr(class)> << endl;

	return 0;
}
