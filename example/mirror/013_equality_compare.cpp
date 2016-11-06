/**
 * @example mirror/013_equality_compare.cpp
 * @brief Shows how to do generic structure equality comparison
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#include <mirror/get_pointer.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/is_static.hpp>
#include <mirror/value.hpp>
#include <mirror/reflection.hpp>
#include <mirror/range.hpp>
#include <mirror/unpack.hpp>
#include <mirror/enable_if.hpp>
#include <iostream>

template <typename T>
static bool generic_are_equal(T& a, T& b);

struct Point
{
	int x, y, z;
};

struct Triangle
{
	Point a, b, c;
};

struct Tetrahedron
{
	Triangle base;
	Point apex;
};

int main(void)
{
	Tetrahedron a{{{0,0,0},{1,0,0},{0,1,0}},{0,0,1}};
	Tetrahedron b{{{0,0,0},{1,0,0},{0,1,0}},{0,0,1}};
	Tetrahedron c{{{0,0,0},{2,0,0},{0,2,0}},{0,0,2}};

	std::cout << generic_are_equal(a, b) << std::endl;
	std::cout << generic_are_equal(b, a) << std::endl;
	std::cout << generic_are_equal(a, c) << std::endl;
	std::cout << generic_are_equal(b, c) << std::endl;

	return 0;
}

namespace {

using namespace mirror;

template <typename T>
class field_equality_comparator
{
private:
	template <typename R>
	struct _hlpr;

	template <typename ... MDMs>
	struct _hlpr<range<MDMs...>>
	{
		template <typename MDM>
		static bool _cmp_field(T& a, T& b)
		{
			if constexpr(value<is_static<MDM>>) {
				return true;
			} else {
				return generic_are_equal(
					a.*value<get_pointer<MDM>>,
					b.*value<get_pointer<MDM>>
				);
			}
		}

		static bool compare(T& a, T& b)
		{
			return (... && _cmp_field<MDMs>(a, b));
		}
	};
public:
	bool operator()(T& a, T& b) const
	{
		using MDMs = unpack<get_data_members<MIRRORED(T)>>;
		return _hlpr<MDMs>::compare(a, b);
	}
};

template<typename T, typename = void>
struct has_operator_equal
 : false_
{ };

template <typename T>
struct has_operator_equal<T,
	std::enable_if_t<
		true,
		decltype(std::declval<T&>() == std::declval<T&>(), (void)0)
	>
> : true_
{ };

} // namespace

template <typename T>
static bool generic_are_equal(T& a, T& b)
{
	using namespace mirror;

	if constexpr (value<has_operator_equal<T>>) {
		return a == b;
	} else {
		field_equality_comparator<T> cmp;
		return cmp(a, b);
	}
}

