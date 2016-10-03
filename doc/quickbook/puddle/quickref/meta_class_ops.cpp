/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_get_base_classes
template <typename X>
static constexpr inline
__mirror_get_base_classes<X> get_base_classes(X)
noexcept;
//]
//[puddle_op_get_public_base_classes
template <typename X>
static constexpr inline
__mirror_get_public_base_classes<X> get_public_base_classes(X)
noexcept;
//]

