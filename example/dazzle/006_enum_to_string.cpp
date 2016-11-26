/**
 * @example dazzle/006_enum_to_string.cpp
 * @brief Shows how to implement a enumerator-to-string conversion
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
#include <map>

enum class E
{
	a, b, c, d, e
};

namespace {

using namespace dazzle;

template <typename Enum>
class enum_to_string
{
private:
	static void _eat(bool ...) { }

	static auto _make_map(void)
	{
		auto do_make_map = [](auto ... mec) {
			std::map<Enum, std::string_view> res;
			_eat(res.emplace(
					mec.get_constant().value(),
					mec.get_base_name().string_view()
			).second...);
			return res;
		};
		auto mecs = DAZZLED(Enum).get_enumerators();
		return mecs.apply(do_make_map);
	}

	const std::map<Enum, std::string_view> _map;
public:
	enum_to_string(void)
	 : _map(_make_map())
	{ }

	std::string_view operator()(Enum e) const
	{
		return _map.find(e)->second;
	}
};

} // namespace

int main(void)
{
	enum_to_string<E> ets;

	std::cout << ets(E::a) << std::endl;
	std::cout << ets(E::b) << std::endl;
	std::cout << ets(E::c) << std::endl;
	std::cout << ets(E::d) << std::endl;
	std::cout << ets(E::e) << std::endl;

	return 0;
}
