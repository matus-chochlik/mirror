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
#include <mirror/is_empty.hpp>
#include <mirror/get_size.hpp>
#include "envelope.hpp"

namespace dazzle {

template <typename X>
struct wrapped;

template <typename Char, Char ... C>
struct wrapped<mirror::basic_string<Char, C...>>
{
	using impl = mirror::basic_string<Char, C...>;

	static constexpr auto c_str(void) {
		return mirror::c_str<impl>;
	}
	static constexpr auto data(void) {
		return c_str();
	}

	static constexpr auto is_empty(void) {
		return envelope<mirror::is_empty<impl>>{};
	}
	static constexpr auto empty(void) {
		return envelope<mirror::is_empty<impl>>{};
	}

	static constexpr auto get_size(void) {
		return envelope<mirror::get_size<impl>>{};
	}
	static constexpr auto size(void) {
		return envelope<mirror::size<impl>>{};
	}
};

} // namespace dazzle

#endif //include guard

