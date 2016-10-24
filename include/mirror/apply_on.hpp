/**
 * @file mirror/apply_on.hpp
 * @brief Implementation of the `apply_on` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_APPLY_ON_1105240825_HPP
#define MIRROR_APPLY_ON_1105240825_HPP

#include "wrap.hpp"
#include "unpack.hpp"

namespace mirror {

template <typename X>
struct apply_on;

template <>
struct apply_on<none>
{
	template <typename Func>
	static constexpr inline
	void apply(Func) { }
};

template <typename ... P>
struct apply_on<range<P...>>
{
	template <typename Func>
	static auto apply(Func func)
	{
		return func(wrap_if_not_special<P>{}...);
	}
};

template <typename Char, Char ... C>
struct apply_on<basic_string<Char, C...>>
{
	template <typename Func>
	static auto apply(Func func)
	{
		return func(int_const<Char, C>{}...);
	}
};

template <typename S>
struct apply_on<metaobject_sequence<S>>
 : apply_on<unpack<metaobject_sequence<S>>>
{ };

} // namespace mirror

#endif //include guard

