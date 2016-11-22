/**
 * @file dazzle/metaobject.hpp
 * @brief Declaration of metaobject and metaobject sequences
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef DAZZLE_METAOBJECT_1105240825_HPP
#define DAZZLE_METAOBJECT_1105240825_HPP

#include <mirror/metaobject.hpp>
#include <mirror/traits.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_full_name.hpp>
#include <mirror/get_scope.hpp>

#include <mirror/is_empty.hpp>
#include <mirror/get_size.hpp>
#include "envelope.hpp"

namespace dazzle {

template <typename MO>
struct wrapped<mirror::metaobject<MO>>
{
	using impl = mirror::metaobject<MO>;

	static constexpr auto get_base_name(void) {
		return envelope<mirror::get_base_name<impl>>{};
	}

	static constexpr auto get_full_name(void) {
		return envelope<mirror::get_full_name<impl>>{};
	}

	static constexpr auto get_scope(void) {
		return envelope<mirror::get_scope<impl>>{};
	}
};

template <typename MoS>
struct wrapped<mirror::metaobject_sequence<MoS>>
{
	using impl = mirror::metaobject_sequence<MoS>;

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

