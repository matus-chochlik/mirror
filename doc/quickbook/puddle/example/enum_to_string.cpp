/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[puddle_example_enum_to_string_1
#include <puddle/metaobject_ops.hpp>
#include <puddle/sequence_ops.hpp>
#include <puddle/reflection.hpp>
#include <puddle/int_const.hpp>
#include <puddle/string.hpp>
#include <iostream>
#include <map>
//]
//[puddle_example_enum_to_string_2
enum class E
{
	a, b, c, d, e
};
//]
//[puddle_example_enum_to_string_3
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
				__value(__get_constant(mec)),
				__string_view(__get_base_name(mec))
		).second...);
		return res;
	}

	template <typename ... MEC>
	static auto _make_map(__mirror_range<MEC...>)
	{
		return _do_make_map(MEC{}...);
	}
public:
	std::string_view operator()(Enum e) const
	{
		auto MECs = __unpack(__get_enumerators(__PUDDLED(Enum)));
		static auto m = _make_map(MECs);
		return m[e];
	}
};

} // namespace
//]
//[puddle_example_enum_to_string_4
int main(void)
{
	enum_to_string<E> ets;

	std::cout << ets(E::a) << std::endl;
	std::cout << ets(E::b) << std::endl;
	std::cout << ets(E::c) << std::endl;
	std::cout << ets(E::d) << std::endl;
	std::cout << ets(E::e) << std::endl;

	return 0;
}//]
//[puddle_example_enum_to_string_output
a
b
c
d
e
//]

