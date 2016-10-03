/*
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */
//[puddle_string_1
template <typename Char, Char ... C>
constexpr __mirror_basic_string<Char, C...> basic_string;

template <char ... C>
constexpr __mirror_string<C...> string;

constexpr __mirror_empty_string empty_string;
//]
//[puddle_string_2
template <typename S>
static inline constexpr
__mirror_c_str<S> c_str(S)
noexcept;

template <typename S>
static inline constexpr
__mirror_string_view string_view(S)
noexcept;
//]

