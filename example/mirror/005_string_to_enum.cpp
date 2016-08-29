/**
 * @example lagoon/005_string_to_enum.cpp
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
#include <map>

enum class E : char
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};

namespace mirror {

template <typename Enum>
struct string_to_enum
{
	template <typename Rng>
	struct _hlpr;

	template <typename ... MEC>
	struct _hlpr<range<MEC...>>
	{
		static void _eat(bool ...) { }

		static std::map<std::string, Enum> _make_map(void)
		{
			std::map<std::string, Enum> res;
			_eat(res.emplace(
					c_str<get_base_name<MEC>>,
					value<get_constant<MEC>>
			).second...);
			return res;
		}
	};

	Enum operator()(const std::string& s) const
	{
		using MECs = unpack<get_enumerators<MIRRORED(Enum)>>;
		static auto m = _hlpr<MECs>::_make_map();
		return m[s];
	}
};

} // namespace mirror

int main(void)
{
	mirror::string_to_enum<E> ste;

	std::cout << char(ste("a")) << std::endl;
	std::cout << char(ste("b")) << std::endl;
	std::cout << char(ste("c")) << std::endl;
	std::cout << char(ste("d")) << std::endl;
	std::cout << char(ste("e")) << std::endl;

	return 0;
}
