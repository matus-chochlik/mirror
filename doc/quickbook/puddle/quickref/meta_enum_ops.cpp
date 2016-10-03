/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_op_is_enum
template <typename X>
static constexpr inline
__mirror_is_enum<X> is_enum(X)
noexcept;
//]
//[puddle_op_is_scoped_enum
template <typename X>
static constexpr inline
__mirror_is_scoped_enum<X> is_scoped_enum(X)
noexcept;
//]
//[puddle_op_get_enumerators
template <typename X>
static constexpr inline
__mirror_get_enumerators<X> get_enumerators(X)
noexcept;
//]

