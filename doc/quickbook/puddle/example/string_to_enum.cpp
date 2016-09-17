/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[puddle_example_string_to_enum_1
#include <puddle/metaobject_ops.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/reflection.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <iostream>
#include <stdexcept>
#include <map>
//]
//[puddle_example_string_to_enum_2
enum class E : char
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};
//]
//[puddle_example_string_to_enum_3
namespace puddle {

template <typename Enum>
class string_to_enum
{
private:
	static void _eat(bool ...) { }

	template <typename ... MEC>
	static
	std::map<std::string, Enum> _do_make_map(MEC ... mec)
	{
		std::map<std::string, Enum> res;
		_eat(res.emplace(
				__c_str(__get_base_name(mec)),
				__value(__get_constant(mec))
		).second...);
		return res;
	}

	template <typename ... MEC>
	static
	std::map<std::string, Enum> _make_map(__mirror_range<MEC...>)
	{
		return _do_make_map(MEC{}...);
	}
public:
	Enum operator()(const std::string& s) const
	{
		auto MECs = __unpack(__get_enumerators(__PUDDLED(Enum)));
		static auto m = _make_map(MECs);
		auto p = m.find(s);
		if(p == m.end()) {
			throw std::runtime_error("Invalid enumerator name");
		}
		return p->second;
	}
};

} // namespace puddle
//]
//[puddle_example_string_to_enum_4
int main(void)
{
	puddle::string_to_enum<E> ste;

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
//[puddle_example_string_to_enum_output
a
b
c
d
e
Invalid enumerator name /*<
printed on ['stderr]
>*/
//]
