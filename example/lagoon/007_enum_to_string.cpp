/**
 * @example lagoon/007_enum_to_string.cpp
 * @brief Shows how to implement a enumerator-to-string conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <lagoon/metaobject_registry.hpp>
#include <lagoon/metaobject.hpp>
#include <puddle/reflection.hpp>
#include <puddle/string.hpp>
#include <iostream>
#include <map>

enum class E
{
	a, b, c, d, e
};

namespace {

using namespace lagoon;

template <typename Enum>
class enum_to_string
{
private:
	static
	std::map<Enum, std::string_view>
	_make_map(const shared_metaobject& me)
	{
		std::map<Enum, std::string_view> res;
		for(auto mec : me.get_enumerators())
		{
			res.emplace(
				mec.get_constant().as<Enum>(),
				mec.get_base_name()
			);
		}
		return res;
	}

	std::map<Enum, std::string_view> _m;
public:
	enum_to_string(const shared_metaobject& meta_Enum)
	 : _m(_make_map(meta_Enum))
	{ }

	std::string_view operator()(Enum e)
	{
		return _m[e];
	}
};

} // namespace

int main(void)
{
	lagoon::metaobject_registry reg;

	reg.reg_enumerators(PUDDLED(E));
	enum_to_string<E> ets(reg.reg(PUDDLED(E)));

	std::cout << ets(E::a) << std::endl;
	std::cout << ets(E::b) << std::endl;
	std::cout << ets(E::c) << std::endl;
	std::cout << ets(E::d) << std::endl;
	std::cout << ets(E::e) << std::endl;

	return 0;
}
