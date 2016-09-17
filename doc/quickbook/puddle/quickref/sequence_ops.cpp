/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_is_empty
template <typename X>
static constexpr inline
__mirror_is_empty<X> is_empty(X)
noexcept;
//]
//[puddle_op_get_size
template <typename X>
static constexpr inline
__mirror_get_size<X> get_size(X)
noexcept;

template <typename X>
static constexpr inline
__mirror_size<X> size(X)
noexcept;
//]
//[puddle_op_get_element
template <typename X, typename I>
static constexpr inline
__mirror_get_element<X, I> get_element(X, I)
noexcept;
//]
//[puddle_op_unpack
template <typename X, typename = enable_if_opt_metaobject_sequence<X>>
static constexpr inline
__mirror_unpack<X> unpack(X)
noexcept;
//]
