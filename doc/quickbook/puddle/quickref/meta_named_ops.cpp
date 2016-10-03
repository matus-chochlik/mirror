/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_is_anonymous
template <typename X>
static constexpr inline
__mirror_is_anonymous<X> is_anonymous(X)
noexcept;
//]
//[puddle_op_get_base_name
template <typename X>
static constexpr inline
__mirror_get_base_name<X> get_base_name(X)
noexcept;
//]
//[puddle_op_get_full_name
template <typename X>
static constexpr inline
__mirror_get_full_name<X> get_full_name(X)
noexcept;
//]
//[puddle_op_get_display_name
template <typename X>
static constexpr inline
__mirror_get_display_name<X> get_display_name(X)
noexcept;
//]

