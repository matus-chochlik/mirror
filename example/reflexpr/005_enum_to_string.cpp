/**
 * @example reflexpr/005_enum_to_string.cpp
 * @brief Shows how to implement a enumerator-to-string conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <reflexpr>
#include <iostream>
#include <string>
#include <map>

enum class E
{
	a, b, c, d, e
};

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
				meta::get_constant_v<MEC>,
				string(meta::get_base_name<MEC>())
			).second...);
			return res;
		}
	};
public:
	const std::string& operator()(Enum e) const
	{
		using namespace std;

		using ME = reflexpr(Enum);
		using hlpr = meta::unpack_sequence_t<
			meta::get_enumerators_m<ME>,
			_hlpr
		>;
		static auto m = hlpr::_make_map();
		return m[e];
	}
};

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
