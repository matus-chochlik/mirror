/**
 * @example lagoon/008_string_to_enum.cpp
 * @brief Shows how to implement a string-to-enumerator conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <lagoon/metaobject_registry.hpp>
#include <lagoon/metaobject.hpp>
#include <puddle/reflection.hpp>
#include <stdexcept>
#include <iostream>
#include <map>

enum class E : char
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};

namespace {

using namespace lagoon;

template <typename Enum>
class string_to_enum
{
private:
	static
	std::map<std::string, Enum>
	_make_map(const shared_metaobject& me)
	{
		std::map<std::string, Enum> res;
		for(auto mec : me.get_enumerators())
		{
			auto n = mec.get_base_name();
			res.emplace(
				std::string(n.data(), n.size()),
				mec.get_constant().as<Enum>()
			);
		}
		return res;
	}

	std::map<std::string, Enum> _m;
public:
	string_to_enum(const shared_metaobject& meta_Enum)
	 : _m(_make_map(meta_Enum))
	{ }

	Enum operator()(const std::string& s)
	{
		auto p = _m.find(s);
		if(p == _m.end()) {
			throw std::runtime_error("Invalid enumerator name");
		}
		return p->second;
	}
};

} // namespace

int main(void)
{
	lagoon::metaobject_registry reg;

	reg.reg_enumerators(PUDDLED(E));
	string_to_enum<E> ste(reg.reg(PUDDLED(E)));

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
