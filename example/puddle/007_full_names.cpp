/**
 * @example puddle/007_full_names.cpp
 * @brief Hello world example
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <puddle/string.hpp>
#include <puddle/metaobject_ops.hpp>
#include <puddle/reflection.hpp>
#include <iostream>
#include <string>

namespace foo {

struct bar {

	static int baz;
	float qux;
};

} // namespace foo

int main(void)
{
	using namespace puddle;

	std::cout << get_full_name(
		PUDDLED(foo::bar::baz)
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(foo::bar)
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(foo::bar*)
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(const foo::bar&)
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(foo::bar const)
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(foo::bar const* volatile)
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(foo::bar[])
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(foo::bar[3][2][1])
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(void())
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(void(*)())
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(double(*)(float, long))
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(const char*(int, long))
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(double(*(float, long, int))(short, bool))
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(foo::bar&(*(*(float, long, int))(short, bool))(char))
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(std::basic_string<char>)
	) << std::endl;

	std::cout << get_full_name(
		PUDDLED(const std::basic_string<char>&)
	) << std::endl;

	return 0;
}
