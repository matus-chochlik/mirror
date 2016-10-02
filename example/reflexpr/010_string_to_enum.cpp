/**
 * @example reflexpr/010_string_to_enum.cpp
 * @brief Shows how to implement a string-to-enumerator conversion
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <reflexpr>
#include <iostream>
#include <stdexcept>
#include <map>

enum class E : char
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};

template <typename Enum>
class string_to_enum
{
private:
	template <typename ... MEC>
	struct _hlpr
	{
		static void _eat(bool ...) { }

		static auto _make_map(void)
		{
			using namespace std;

			map<string, Enum> res;
			_eat(res.emplace(
				string(meta::get_base_name<MEC>()),
				meta::get_constant_v<MEC>
			).second...);
			return res;
		}
	};

	static auto _make_map(void)
	{
		using namespace std;

		using ME = reflexpr(Enum);
		using hlpr = meta::unpack_sequence_t<
			meta::get_enumerators_m<ME>,
			_hlpr
		>;
		return hlpr::_make_map();
	}

	const std::map<std::string, Enum> _map;
public:
	string_to_enum(void)
	 : _map(_make_map())
	{ }

	Enum operator()(const std::string& s) const
	{
		using namespace std;

		auto p = _map.find(s);
		if(p == _map.end()) {
			throw runtime_error("Invalid enumerator name");
		}
		return p->second;
	}
};

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
