/**
 * @file puddle/sequence_ops.hpp
 * @brief Implementation of sequence, range, string operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_SEQUENCE_OPS_1105240825_HPP
#define PUDDLE_SEQUENCE_OPS_1105240825_HPP

#include <mirror/unpack.hpp>
#include <mirror/is_empty.hpp>
#include <mirror/get_empty.hpp>
#include <mirror/get_size.hpp>
#include <mirror/get_element.hpp>
#include <mirror/for_each.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X, typename = enable_if_any_opt_sequence<X>>
static constexpr inline
auto is_empty(X)
noexcept
{
	return mirror::is_empty<X>{};
}

template <typename X, typename = enable_if_opt_eager_sequence<X>>
static constexpr inline
auto get_empty(X)
noexcept
{
	return mirror::get_empty<X>{};
}

template <typename X, typename = enable_if_any_opt_sequence<X>>
static constexpr inline
auto get_size(X)
noexcept
{
	return mirror::get_size<X>{};
}

template <typename X, typename = enable_if_any_opt_sequence<X>>
static constexpr inline
auto size(X)
noexcept
{
	return mirror::size<X>{};
}

template <
	typename X, typename I,
	typename = enable_if_any_opt_sequence<X>,
	typename = enable_if_int_const<I>
> static constexpr inline
auto get_element(X, I)
noexcept
{
	return mirror::get_element<X, I>{};
}

template <typename X, typename = enable_if_opt_metaobject_sequence<X>>
static constexpr inline
auto unpack(X)
noexcept
{
	return mirror::unpack<X>{};
}

template <typename Rng, typename Func>
static constexpr inline
Func for_each(Rng, Func func)
{
	return mirror::for_each<Rng>::apply(func);
}

} // namespace puddle

#endif //include guard

