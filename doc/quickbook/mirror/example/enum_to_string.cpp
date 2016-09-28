/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[mirror_example_enum_to_string_1
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
//]
//[mirror_example_enum_to_string_2
enum class E
{
	a, b, c, d, e
};
//]
//[mirror_example_enum_to_string_3
namespace mirror {

template <typename Enum>
class enum_to_string
{
private:
	template <typename Rng>
	struct _hlpr;

	template <typename ... MEC>
	struct _hlpr<__range<MEC...>>
	{
		static void _eat(bool ...) { }

		static auto _make_map(void)
		{
			std::map<Enum, std::string_view> res;
			_eat(res.emplace(
				__value<__get_constant<MEC>>,
				__string_view<__get_base_name<MEC>>
			).second...);
			return res;
		}
	};
public:
	std::string_view operator()(Enum e) const
	{
		using MECs = __unpack<__get_enumerators<__MIRRORED(Enum)>>;
		static auto m = _hlpr<MECs>::_make_map();
		return m[e];
	}
};

} // namespace mirror
//]
//[mirror_example_enum_to_string_4
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
//]
//[mirror_example_enum_to_string_output
a
b
c
d
e
//]

