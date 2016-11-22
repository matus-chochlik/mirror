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

	static constexpr auto reflects_alias(void) {
		return mirror::reflects_alias<X>{};
	}
	static constexpr auto reflects_global_scope(void) {
		return mirror::reflects_global_scope<X>{};
	}
	static constexpr auto reflects_namespace(void) {
		return mirror::reflects_namespace<X>{};
	}
	static constexpr auto reflects_type(void) {
		return mirror::reflects_type<X>{};
	}
	static constexpr auto reflects_tag_type(void) {
		return mirror::reflects_tag_type<X>{};
	}
	static constexpr auto reflects_enum(void) {
		return mirror::reflects_enum<X>{};
	}
	static constexpr auto reflects_record(void) {
		return mirror::reflects_record<X>{};
	}
	static constexpr auto reflects_class(void) {
		return mirror::reflects_class<X>{};
	}
	static constexpr auto reflects_enum_member(void) {
		return mirror::reflects_enum_member<X>{};
	}
	static constexpr auto reflects_record_member(void) {
		return mirror::reflects_record_member<X>{};
	}
	static constexpr auto reflects_variable(void) {
		return mirror::reflects_variable<X>{};
	}
	static constexpr auto reflects_constant(void) {
		return mirror::reflects_constant<X>{};
	}
	static constexpr auto reflects_specifier(void) {
		return mirror::reflects_specifier<X>{};
	}
	static constexpr auto reflects_inheritance(void) {
		return mirror::reflects_inheritance<X>{};
	}
};

} // namespace dazzle

#endif //include guard

