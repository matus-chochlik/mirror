/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

//[mirror_example_string_to_enum_1
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
//]
//[mirror_example_string_to_enum_2
enum class E : char
{
	a = 'a', b = 'b', c = 'c', d = 'd', e = 'e'
};
//]
//[mirror_example_string_to_enum_3
namespace mirror {

template <typename Enum>
class string_to_enum
{
private:
	template <typename Rng>
	struct _hlpr;

	template <typename ... MEC>
	struct _hlpr<__range<MEC...>>
	{
		static void _eat(bool ...) { }

		static std::map<std::string, Enum> _make_map(void)
		{
			std::map<std::string, Enum> res;
			_eat(res.emplace(
				__c_str<__get_base_name<MEC>>,
				__value<__get_constant<MEC>>
			).second...);
			return res;
		}
	};
public:
	Enum operator()(const std::string& s) const
	{
		using MECs = __unpack<__get_enumerators<__MIRRORED(Enum)>>;
		static auto m = _hlpr<MECs>::_make_map();
		auto p = m.find(s);
		if(p == m.end()) {
			throw std::runtime_error("Invalid enumerator name");
		}
		return p->second;
	}
};

} // namespace mirror
//]
//[mirror_example_string_to_enum_4
int main(void)
{
	mirror::string_to_enum<E> ste;

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
//[mirror_example_string_to_enum_output
a
b
c
d
e
Invalid enumerator name /*<
printed on ['stderr]
>*/
//]
