/**
 * @example puddle/006_string_to_enum.cpp
 * @brief Shows how to implement a string-to-enumerator conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <puddle/metaobject_ops.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/reflection.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <iostream>
#include <stdexcept>
#include <map>

enum class E
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};

namespace puddle {

template <typename Enum>
struct string_to_enum
{
	static void _eat(bool ...) { }

	template <typename ... MEC>
	static
	std::map<std::string, Enum> _do_make_map(MEC ... mec)
	{
		std::map<std::string, Enum> res;
		_eat(res.emplace(
				c_str(get_base_name(mec)),
				value(get_constant(mec))
		).second...);
		return res;
	}

	template <typename ... MEC>
	static
	std::map<std::string, Enum> _make_map(mirror::range<MEC...>)
	{
		return _do_make_map(MEC{}...);
	}

	Enum operator()(const std::string& s) const
	{
		auto MECs = unpack(get_enumerators(PUDDLED(Enum)));
		static auto m = _make_map(MECs);
		auto p = m.find(s);
		if(p == m.end()) {
			throw std::runtime_error("Invalid enumerator name");
		}
		return p->second;
	}
};

} // namespace puddle

int main(void)
{
	puddle::string_to_enum<E> ste;

	try {
		std::cout << char(ste("a")) << std::endl;
		std::cout << char(ste("b")) << std::endl;
		std::cout << char(ste("c")) << std::endl;
		std::cout << char(ste("d")) << std::endl;
		std::cout << char(ste("e")) << std::endl;
		std::cout << char(ste("f")) << std::endl;
	} catch(std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	return 0;
}
