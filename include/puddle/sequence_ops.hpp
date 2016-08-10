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
#include <mirror/get_size.hpp>
#include <mirror/get_element.hpp>
#include <mirror/enable_if.hpp>
#include <mirror/traits.hpp>

namespace puddle {

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object_sequence<X>,
		mirror::is_string<X>,
		mirror::is_range<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto is_empty(X)
noexcept
{
	return mirror::is_empty<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object_sequence<X>,
		mirror::is_string<X>,
		mirror::is_range<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_size(X)
noexcept
{
	return mirror::get_size<X>{};
}

template <
	typename X, typename I,
	typename = mirror::enable_if_any<
		mirror::is_meta_object_sequence<X>,
		mirror::is_string<X>,
		mirror::is_range<X>,
		mirror::is_none<X>
	>, typename = mirror::enable_if_any<
		mirror::is_int_const<I>
	>
> static constexpr inline
auto get_element(X, I)
noexcept
{
	return mirror::get_element<X, I>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object_sequence<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto unpack(X)
noexcept
{
	return mirror::unpack<X>{};
}

} // namespace puddle

#endif //include guard

