/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[reflexpr_example_string_to_enum_1
#include <reflexpr>
#include <iostream>
#include <string>
#include <map>
//]
//[reflexpr_example_string_to_enum_2
enum class E
{
	a, b, c, d, e
};
//]
//[reflexpr_example_string_to_enum_3
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
				__meta_get_base_name_v<MEC>,
				__meta_get_constant_v<MEC>
			).second...);
			return res;
		}
	};
public:
	Enum operator()(const std::string& s) const
	{
		using namespace std;

		using ME = reflexpr(Enum);
		using hlpr = __meta_unpack_sequence_t<
			__meta_get_enumerators_m<ME>,
			_hlpr
		>;
		static auto m = hlpr::_make_map();
		auto p = m.find(s);
		if(p == m.end()) {
			throw runtime_error("Invalid enumerator name");
		}
		return p->second;
	}
};
//]
//[reflexpr_example_string_to_enum_4
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
//]
//[reflexpr_example_string_to_enum_output
a
b
c
d
e
Invalid enumerator name /*<
printed on ['stderr]
>*/
//]
