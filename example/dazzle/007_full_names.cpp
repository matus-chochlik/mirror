/**
 * @example dazzle/007_full_names.cpp
 * @brief Hello world example
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/string.hpp>
#include <dazzle/metaobject.hpp>
#include <dazzle/reflection.hpp>
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
	using namespace dazzle;

	auto prn = [](auto mo) {
		std::cout << mo.get_full_name() << std::endl;
	};

	prn(DAZZLED(foo::bar::baz));

	prn(DAZZLED(foo::bar));

	prn(DAZZLED(foo::bar*));

	prn(DAZZLED(const foo::bar&));

	prn(DAZZLED(foo::bar const));

	prn(DAZZLED(foo::bar const* volatile));

	prn(DAZZLED(foo::bar[]));

	prn(DAZZLED(foo::bar[3][2][1]));

	prn(DAZZLED(void()));

	prn(DAZZLED(void(*)()));

	prn(DAZZLED(double(*)(float, long)));

	prn(DAZZLED(const char*(int, long)));

	prn(DAZZLED(double(*(float, long, int))(short, bool)));

	prn(DAZZLED(foo::bar&(*(*(float, long, int))(short, bool))(char)));

	prn(DAZZLED(std::string));

	prn(DAZZLED(std::basic_string<char>));

	prn(DAZZLED(const std::basic_string<char>&));

	return 0;
}
