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
#include <mirror/get_display_name.hpp>
#include <mirror/get_aliased.hpp>
#include <mirror/get_type.hpp>
#include <mirror/get_scope.hpp>
#include <mirror/get_enumerators.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_public_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_public_member_types.hpp>
#include <mirror/get_base_classes.hpp>
#include <mirror/get_public_base_classes.hpp>
#include <mirror/get_base_class.hpp>

#include <mirror/is_class.hpp>
#include <mirror/is_struct.hpp>
#include <mirror/is_union.hpp>
#include <mirror/is_enum.hpp>
#include <mirror/is_scoped_enum.hpp>

#include <mirror/get_reflected_type.hpp>

#include <mirror/is_empty.hpp>
#include <mirror/get_size.hpp>
#include <mirror/for_each.hpp>
#include "envelope.hpp"
#include "type.hpp"

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

	static constexpr auto get_display_name(void) {
		return envelope<mirror::get_display_name<impl>>{};
	}

	static constexpr auto get_aliased(void) {
		return envelope<mirror::get_aliased<impl>>{};
	}

	static constexpr auto get_reflected_type(void) {
		return envelope<mirror::get_reflected_type<impl>>{};
	}

	static constexpr auto get_type(void) {
		return envelope<mirror::get_type<impl>>{};
	}

	static constexpr auto get_scope(void) {
		return envelope<mirror::get_scope<impl>>{};
	}

	static constexpr auto is_class(void) {
		return envelope<mirror::is_class<impl>>{};
	}

	static constexpr auto is_struct(void) {
		return envelope<mirror::is_struct<impl>>{};
	}

	static constexpr auto is_union(void) {
		return envelope<mirror::is_union<impl>>{};
	}

	static constexpr auto is_enum(void) {
		return envelope<mirror::is_enum<impl>>{};
	}

	static constexpr auto is_scoped_enum(void) {
		return envelope<mirror::is_scoped_enum<impl>>{};
	}

	static constexpr auto get_enumerators(void) {
		return envelope<mirror::get_enumerators<impl>>{};
	}

	static constexpr auto get_data_members(void) {
		return envelope<mirror::get_data_members<impl>>{};
	}

	static constexpr auto get_public_data_members(void) {
		return envelope<mirror::get_public_data_members<impl>>{};
	}

	static constexpr auto get_member_types(void) {
		return envelope<mirror::get_member_types<impl>>{};
	}

	static constexpr auto get_public_member_types(void) {
		return envelope<mirror::get_public_member_types<impl>>{};
	}

	static constexpr auto get_base_classes(void) {
		return envelope<mirror::get_base_classes<impl>>{};
	}

	static constexpr auto get_public_base_classes(void) {
		return envelope<mirror::get_public_base_classes<impl>>{};
	}

	static constexpr auto get_base_class(void) {
		return envelope<mirror::get_base_class<impl>>{};
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

	template <typename Func>
	static constexpr auto for_each(Func func) {
		return mirror::for_each<impl>::apply(func);
	}

	template <typename Func, typename Sep>
	static constexpr auto for_each(Func func, Sep sep) {
		return mirror::for_each<impl>::apply(func, sep);
	}
};

} // namespace dazzle

#endif //include guard

