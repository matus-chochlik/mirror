/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[reflexpr_example_enum_to_string_1
#include <reflexpr>
#include <iostream>
#include <string>
#include <map>
//]
//[reflexpr_example_enum_to_string_2
enum class E
{
	a, b, c, d, e
};
//]
//[reflexpr_example_enum_to_string_3
template <typename Enum>
class enum_to_string
{
private:
	template <typename ... MEC>
	struct _hlpr
	{
		static void _eat(bool ...) { }

		static std::map<Enum, std::string> _make_map(void)
		{
			using namespace std;

			map<Enum, string> res;
			_eat(res.emplace(
				__meta_get_constant_v<MEC>,
				__meta_get_base_name_v<MEC>
			).second...);
			return res;
		}
	};
public:
	const std::string& operator()(Enum e) const
	{
		using namespace std;

		using ME = reflexpr(Enum);
		using hlpr = __meta_unpack_sequence_t<
			__meta_get_enumerators_m<ME>,
			_hlpr
		>;
		static auto m = hlpr::_make_map();
		return m[e];
	}
};
//]
//[reflexpr_example_enum_to_string_4
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
//]
//[reflexpr_example_enum_to_string_output
a
b
c
d
e
//]
