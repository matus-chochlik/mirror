/**
 * @example lagoon/005_enum_to_string.cpp
 * @brief Shows how to implement a enumerator-to-string conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/get_constant.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_enumerators.hpp>
#include <mirror/string_view.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>
#include <mirror/range.hpp>
#include <mirror/unpack.hpp>
#include <iostream>
#include <map>

enum class E
{
	a, b, c, d, e
};

namespace mirror {

template <typename Enum>
struct enum_to_string
{
	template <typename Rng>
	struct _hlpr;

	template <typename ... MEC>
	struct _hlpr<range<MEC...>>
	{
		static void _eat(bool ...) { }

		static std::map<Enum, std::string_view> _make_map(void)
		{
			std::map<Enum, std::string_view> res;
			_eat(res.emplace(
					value<get_constant<MEC>>,
					string_view<get_base_name<MEC>>
			).second...);
			return res;
		}
	};

	std::string_view operator()(Enum e) const
	{
		using MECs = unpack<get_enumerators<MIRRORED(Enum)>>;
		static auto m = _hlpr<MECs>::_make_map();
		return m[e];
	}
};

} // namespace mirror

int main(void)
{
	mirror::enum_to_string<E> ets;

	std::cout << ets(E::a) << std::endl;
	std::cout << ets(E::b) << std::endl;
	std::cout << ets(E::c) << std::endl;
	std::cout << ets(E::d) << std::endl;
	std::cout << ets(E::e) << std::endl;

	return 0;
}
