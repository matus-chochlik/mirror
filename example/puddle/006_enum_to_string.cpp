/**
 * @example puddle/006_enum_to_string.cpp
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

namespace {

using namespace puddle;

template <typename Enum>
class enum_to_string
{
private:
	static void _eat(bool ...) { }

	template <typename ... MEC>
	static auto _do_make_map(MEC ... mec)
	{
		std::map<Enum, std::string_view> res;
		_eat(res.emplace(
				value(get_constant(mec)),
				string_view(get_base_name(mec))
		).second...);
		return res;
	}

	template <typename ... MEC>
	static auto _make_map(mirror::range<MEC...>)
	{
		return _do_make_map(MEC{}...);
	}

	static auto _make_map(void)
	{
		auto mecs = unpack(get_enumerators(PUDDLED(Enum)));
		return _make_map(mecs);
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
