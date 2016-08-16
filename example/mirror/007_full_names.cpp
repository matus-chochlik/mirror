/**
 * @example mirror/007_full_names.cpp
 * @brief Example showing the usage of the `get_full_name` operation.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/reflection.hpp>
#include <mirror/get_full_name.hpp>
#include <mirror/c_str.hpp>
#include <iostream>

namespace foo {

struct bar {

	static int baz;
	float qux;
};

} // namespace foo

int main(void)
{
	using namespace mirror;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar::baz)
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar)
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar*)
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(const foo::bar&)
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar const)
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar const* volatile)
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar[])
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar[3][2][1])
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(void())
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(void(*)())
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(double(*)(float, long))
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(const char*(int, long))
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(double(*(float, long, int))(short, bool))
	>> << std::endl;

	std::cout << c_str<get_full_name<
		MIRRORED(foo::bar&(*(*(float, long, int))(short, bool))(char))
	>> << std::endl;

	return 0;
}
