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

template <typename X>
class for_each;

template <>
class for_each<none>
{
public:
	template <typename Func>
	static constexpr inline
	Func apply(Func func)
	{
		return func;
	}
};

template <typename ... P>
class for_each<range<P...>>
{
private:
	static constexpr inline void _eat(bool ...) { }


	template <typename Func, typename Pa>
	static bool _single(Func& func, Pa pa)
	{
		func(pa);
		return true;
	}
public:
	template <typename Func>
	static Func apply(Func func)
	{
		_eat(_single(func, wrap_if_not_special<P>{})...);
		return func;
	}
};

template <typename Char, Char ... C>
class for_each<basic_string<Char, C...>>
{
private:
	static constexpr inline void _eat(bool ...) { }


	template <typename Func, typename Pa>
	static bool _single(Func& func, Pa pa)
	{
		func(pa);
		return true;
	}
public:
	template <typename Func>
	static Func apply(Func func)
	{
		_eat(_single(func, int_const<Char, C>{})...);
		return func;
	}
};

template <typename S>
class for_each<metaobject_sequence<S>>
 : public for_each<unpack<metaobject_sequence<S>>>
{ };

} // namespace mirror

#endif //include guard

