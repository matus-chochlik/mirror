/**
 * @example reflexpr/040_full_type_name.cpp
 * @brief Shows how to portably print full type names using reflection
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
#include <reflexpr>
#include <iostream>
#include <string>

template <typename T>
std::string get_full_type_name(void);

template <typename T>
void print_name(void)
{
	std::cout << get_full_type_name<T>() << std::endl;
}

int main(void)
{
	print_name<bool>();
	print_name<char const*>();
	print_name<char *const>();
	print_name<int&>();
	print_name<float[128]>();
	print_name<double const * volatile * [][3][2][1]>();

	print_name<decltype(nullptr)>();

	return 0;
}

namespace {

template <typename T> struct type { };

template <typename MT>
std::string get_scope_spec(MT)
{
	using namespace std::meta;

	std::string result;

	if constexpr (ScopeMember<MT> && !GlobalScope<MT>)
	{
		using MS = get_scope_m<MT>;
		if constexpr (Named<MS>)
		{
			if constexpr (is_anonymous_v<MS>) {
				result = get_scope_spec(get_scope_m<MS>{});
			} else {
				result = get_scope_spec(MS{});
			}
		}
		else if constexpr (Enum<MS>) {
			if constexpr (is_scoped_enum_v<MS>) {
				result = get_scope_spec(MS{});
			} else {
				result = get_scope_spec(get_scope_m<MS>{});
			}
		}
		else { result = get_scope_spec(MS{}); }
		result += "::";
	}
	result += get_base_name<MT>{};
	return result;
}

template <typename T>
void make_type_name(
	type<T>,
	std::string& /*left*/,
	std::string& base,
	std::string& /*right*/,
	std::string& /*extent*/,
	std::string& /*params*/
)
{
	using namespace std::meta;
	base = get_scope_spec(get_aliased_m<reflexpr(T)>{});
}

template <typename T>
void make_type_name(
	type<const T>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	right += " const";
}

template <typename T>
void make_type_name(
	type<volatile T>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	right += " volatile";
}

template <typename T>
void make_type_name(
	type<const volatile T>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	right += " const volatile";
}

template <typename T>
void make_type_name(
	type<T*>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	right += "*";
}

template <typename T>
void make_type_name(
	type<T&>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	right += "&";
}

template <typename T>
void make_type_name(
	type<T&&>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	right += "&&";
}

template <typename T, std::size_t N>
void make_type_name(
	type<T[N]>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	extent = '[' + std::to_string(N) + ']' + extent;
}

template <typename T>
void make_type_name(
	type<T[]>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	make_type_name(type<T>{}, left, base, right, extent, params);
	extent = "[]" + extent;
}

/* TODO

template <typename R, typename ... P>
void make_type_name(
	type<R(P...)>,
	std::string& left,
	std::string& base,
	std::string& right,
	std::string& extent,
	std::string& params
)
{
	std::string rleft, rbase, rright, rextent, rparam;
	make_type_name(type<R>{}, rleft, rbase, rright, rextent, rparam);

	
}
*/

} // anonymous namespace

template <typename T>
std::string get_full_type_name(void)
{
	std::string left, base, right, extent, param;
	make_type_name(type<T>{}, left, base, right, extent, param);
	return left + base + right + extent + param;
}

