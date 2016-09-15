/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_int_const_1
template <typename Int, Int I>
constexpr __mirror_int_const<Int, I> int_const = {};

template <bool B>
constexpr __mirror_bool_<B> bool_ = {};

constexpr __mirror_true_ true_ = {};
constexpr __mirror_false_ false_ = {};

template <char C>
constexpr __mirror_char_<C> char_ = {};

template <int I>
constexpr __mirror_int_<I> int_ = {};

template <unsigned U>
constexpr __mirror_unsigned_<U> unsigned_ = {};
//]
//[puddle_int_const_2
template <typename I>
static inline constexpr
__mirror_value<I> value(I)
noexcept;
//]

