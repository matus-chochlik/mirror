/**
 * @file mirror/for_each.hpp
 * @brief Implementation of the `for_each` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_FOR_EACH_1105240825_HPP
#define MIRROR_FOR_EACH_1105240825_HPP

#include "wrap.hpp"
#include "unpack.hpp"

namespace mirror {
namespace _aux {

struct op_for_each
{
protected:
	static constexpr inline void _eat(bool ...) { }

	template <typename Func, typename Pa>
	static bool _single(Func& func, Pa pa)
	{
		func(pa);
		return true;
	}

	template <typename Func, typename SepFn, typename Pa>
	static bool _single(Func& func, SepFn& sepfn, Pa pa)
	{
		sepfn();
		func(pa);
		return true;
	}
};

} // namespace _aux

template <typename X>
struct for_each;

template <>
struct for_each<none>
{
	template <typename Func>
	static constexpr inline
	Func apply(Func func)
	{
		return func;
	}

	template <typename Func, typename SepFunc>
	static constexpr inline
	Func apply(Func func, SepFunc)
	{
		return func;
	}
};

template <typename H, typename ... T>
struct for_each<range<H, T...>>
 : _aux::op_for_each
{
public:
	template <typename Func>
	static Func apply(Func func)
	{
		_eat(
			_single(func, wrap_if_not_special<H>{}),
			_single(func, wrap_if_not_special<T>{})...
		);
		return func;
	}

	template <typename Func, typename SepFunc>
	static Func apply(Func func, SepFunc sep_func)
	{
		_eat(
			_single(func, wrap_if_not_special<H>{}),
			_single(func, sep_func, wrap_if_not_special<T>{})...
		);
		return func;
	}
};

template <>
struct for_each<range<>>
 : for_each<none>
{ };

template <typename Char, Char H, Char ... T>
struct for_each<basic_string<Char, H, T...>>
 : _aux::op_for_each
{
public:
	template <typename Func>
	static Func apply(Func func)
	{
		_eat(
			_single(func, int_const<Char, H>{}),
			_single(func, int_const<Char, T>{})...
		);
		return func;
	}

	template <typename Func, typename SepFunc>
	static Func apply(Func func, SepFunc sep_func)
	{
		_eat(
			_single(func, int_const<Char, H>{}),
			_single(func, sep_func, int_const<Char, T>{})...
		);
		return func;
	}
};

template <typename Char>
struct for_each<basic_string<Char>>
 : for_each<none>
{ };

template <typename S>
struct for_each<metaobject_sequence<S>>
 : for_each<unpack<metaobject_sequence<S>>>
{ };

} // namespace mirror

#endif //include guard

