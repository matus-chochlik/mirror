/**
 * @example mirror/007_string_to_enum.cpp
 * @brief Shows how to implement a string-to-enumerator conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/get_constant.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_enumerators.hpp>
#include <mirror/c_str.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>
#include <mirror/range.hpp>
#include <mirror/unpack.hpp>
#include <iostream>
#include <stdexcept>
#include <map>

enum class E : char
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};

namespace {

using namespace mirror;

template <typename Enum>
class string_to_enum
{
private:
	template <typename Rng>
	struct _hlpr;

	template <typename ... MEC>
	struct _hlpr<range<MEC...>>
	{
		static void _eat(bool ...) { }

		static auto _make_map(void)
		{
			std::map<std::string, Enum> res;
			_eat(res.emplace(
				c_str<get_base_name<MEC>>,
				value<get_constant<MEC>>
			).second...);
			return res;
		}
	};

	static auto _make_map(void)
	{
		using MECs = unpack<get_enumerators<MIRRORED(Enum)>>;
		return _hlpr<MECs>::_make_map();
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
