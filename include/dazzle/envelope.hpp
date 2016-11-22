/**
 * @file dazzle/envelope.hpp
 * @brief Declaration of the envelope template
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_ENVELOPE_1105240825_HPP
#define DAZZLE_ENVELOPE_1105240825_HPP

#include <mirror/traits.hpp>

namespace dazzle {

template <typename X>
struct wrapped;

template <typename X>
struct envelope
 : wrapped<X>
{
	static constexpr auto is_int_const(void) {
		return mirror::is_int_const<X>{};
	}
	static constexpr auto is_string(void) {
		return mirror::is_string<X>{};
	}
	static constexpr auto is_range(void) {
		return mirror::is_range<X>{};
	}
	static constexpr auto is_none(void) {
		return mirror::is_none<X>{};
	}
	static constexpr auto is_metaobject(void) {
		return mirror::is_metaobject<X>{};
	}
	static constexpr auto is_metaobject_sequence(void) {
		return mirror::is_metaobject_sequence<X>{};
	}
};

} // namespace dazzle

#endif //include guard

