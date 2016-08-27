/**
 * @file puddle/string.hpp
 * @brief Declaration of basic_string and string
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_STRING_1105240825_HPP
#define PUDDLE_STRING_1105240825_HPP

#include <mirror/string.hpp>
#include <mirror/string_ops.hpp>
#include <mirror/string_view.hpp>
#include <mirror/c_str.hpp>

namespace puddle {

template <typename Char, Char ... C>
constexpr mirror::basic_string<Char, C...> basic_string = {};

template <char ... C>
constexpr mirror::string<C...> string = {};

constexpr mirror::empty_string empty_string = {};

template <typename S>
static inline constexpr
auto c_str(S)
noexcept
{
	return ::mirror::c_str<S>;
}

template <typename S>
static inline constexpr
auto string_view(S)
noexcept
{
	return ::mirror::string_view<S>;
}

} // namespace puddle

#endif //include guard

