/**
 * @example reflexpr/003_unpack_sequence.cpp
 * @brief Unpack sequence
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>
#include <tuple>

struct foo
{
	int a;
    	bool b;
	char c;
	double d;
};

template <typename ... MDM>
using helper = std::tuple<
	std::meta::get_reflected_type_t<std::meta::get_type_m<MDM>>...
>;

int main(void)
{
	using namespace std;

	using X = meta::unpack_sequence_t<
		meta::get_data_members_m<reflexpr(foo)>,
		helper
	>;

	static_assert(is_same<X, tuple<int, bool, char, double>>::value, "");

	return 0;
}
