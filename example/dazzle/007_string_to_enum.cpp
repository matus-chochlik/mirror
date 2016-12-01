/**
 * @example dazzle/007_string_to_enum.cpp
 * @brief Shows how to implement a string-to-enumerator conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <dazzle/metaobject.hpp>
#include <dazzle/reflection.hpp>
#include <dazzle/string.hpp>
#include <iostream>
#include <stdexcept>
#include <map>

enum class E : char
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};

namespace {

using namespace dazzle;

template <typename Enum>
class string_to_enum
{
private:
	static void _eat(bool ... ) { }

	static auto _make_map(void)
	{
		auto do_make_map = [](auto ... mec) {
			std::map<std::string, Enum> res;
			_eat(res.emplace(
				mec.get_base_name(),
				mec.get_constant()
			).second...);
			return res;
		};
		auto mecs = DAZZLED(Enum).get_enumerators();
		return mecs.apply(do_make_map);
	}

	const std::map<std::string, Enum> _map;
public:
	string_to_enum(void)
	 : _map(_make_map())
	{ }

	Enum operator()(const std::string& s) const
	{
		auto p = _map.find(s);
		if(p == _map.end()) {
			throw std::runtime_error("Invalid enumerator name");
		}
		return p->second;
	}
};

} // namespace

int main(void)
{
	string_to_enum<E> ste;

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
