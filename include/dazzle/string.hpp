/**
 * @file dazzle/string.hpp
 * @brief Declaration of compile-time strings
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_STRING_1105240825_HPP
#define DAZZLE_STRING_1105240825_HPP

#include <mirror/string.hpp>
#include <mirror/c_str.hpp>
#include <mirror/string_view.hpp>
#include <mirror/is_empty.hpp>
#include <mirror/get_size.hpp>
#include "sequence_ops.hpp"
#include "int_const.hpp"
#include "envelope.hpp"
#include <string>

namespace dazzle {

template <typename X>
struct wrapped;

template <typename Char, Char ... C>
struct wrapped<mirror::basic_string<Char, C...>>
 : sequence_ops<mirror::basic_string<Char, C...>>
{
	using impl = mirror::basic_string<Char, C...>;
	using sequence_ops<mirror::basic_string<Char, C...>>::size;

	static constexpr auto c_str(void) noexcept {
		return mirror::c_str<impl>;
	}
	static constexpr auto data(void) noexcept {
		return c_str();
	}
	static constexpr auto string_view(void) noexcept {
		return mirror::string_view<impl>;
	}

	static std::string str(void) noexcept {
		return {data(), size()};
	}
	operator std::string (void) const noexcept {
		return str();
	}
};

template <typename Char, Char ... C1, Char ... C2>
static constexpr inline
envelope<mirror::basic_string<Char, C1..., C2...>> operator + (
	wrapped<mirror::basic_string<Char, C1...>>,
	wrapped<mirror::basic_string<Char, C2...>>
) noexcept { return {}; }

template <typename Char, Char ... C>
static constexpr inline
envelope<mirror::true_> operator == (
	wrapped<mirror::basic_string<Char, C...>>,
	wrapped<mirror::basic_string<Char, C...>>
) noexcept { return {}; }

template <typename Char, Char ... C1, Char ... C2>
static constexpr inline
envelope<mirror::false_> operator == (
	wrapped<mirror::basic_string<Char, C1...>>,
	wrapped<mirror::basic_string<Char, C2...>>
) noexcept { return {}; }

template <typename Char, Char ... C>
static constexpr inline
envelope<mirror::false_> operator != (
	wrapped<mirror::basic_string<Char, C...>>,
	wrapped<mirror::basic_string<Char, C...>>
) noexcept { return {}; }

template <typename Char, Char ... C1, Char ... C2>
static constexpr inline
envelope<mirror::true_> operator != (
	wrapped<mirror::basic_string<Char, C1...>>,
	wrapped<mirror::basic_string<Char, C2...>>
) noexcept { return {}; }

template <typename OStream, typename Char, Char ... C>
static inline auto& operator << (
	OStream& out,
	wrapped<mirror::basic_string<Char, C...>> s
) { return out.write(s.data(), s.size()); }

// "constructors"
template <typename Char, Char ... C>
constexpr envelope<mirror::basic_string<Char, C...>> basic_string = {};

template <char ... C>
constexpr envelope<mirror::string<C...>> string = {};

constexpr envelope<mirror::empty_string> empty_string = {};

} // namespace dazzle

#endif //include guard

