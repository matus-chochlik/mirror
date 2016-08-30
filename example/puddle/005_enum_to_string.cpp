/**
 * @example puddle/005_enum_to_string.cpp
 * @brief Shows how to implement a enumerator-to-string conversion
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
#include <map>

enum class E
{
	a, b, c, d, e
};

namespace puddle {

template <typename Enum>
class enum_to_string
{
private:
	static void _eat(bool ...) { }

	template <typename ... MEC>
	static
	std::map<Enum, std::string_view> _do_make_map(MEC ... mec)
	{
		std::map<Enum, std::string_view> res;
		_eat(res.emplace(
				value(get_constant(mec)),
				string_view(get_base_name(mec))
		).second...);
		return res;
	}

	template <typename ... MEC>
	static
	std::map<Enum, std::string_view> _make_map(mirror::range<MEC...>)
	{
		return _do_make_map(MEC{}...);
	}
public:
	std::string_view operator()(Enum e) const
	{
		auto MECs = unpack(get_enumerators(PUDDLED(Enum)));
		static auto m = _make_map(MECs);
		return m[e];
	}
};

} // namespace puddle

int main(void)
{
	puddle::enum_to_string<E> ets;

	std::cout << ets(E::a) << std::endl;
	std::cout << ets(E::b) << std::endl;
	std::cout << ets(E::c) << std::endl;
	std::cout << ets(E::d) << std::endl;
	std::cout << ets(E::e) << std::endl;

	return 0;
}
