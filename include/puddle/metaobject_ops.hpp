/**
 * @file puddle/metaobject_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_METAOBJECT_OPS_1105240825_HPP
#define PUDDLE_METAOBJECT_OPS_1105240825_HPP

#include <mirror/get_source_file.hpp>
#include <mirror/get_source_line.hpp>
#include <mirror/get_source_column.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_display_name.hpp>
#include <mirror/get_scope.hpp>
#include <mirror/get_type.hpp>
#include <mirror/get_base_classes.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_enumerators.hpp>
#include <mirror/enable_if.hpp>
#include <mirror/traits.hpp>

namespace puddle {

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_source_file(X)
noexcept
{
	return mirror::get_source_file<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_source_line(X)
noexcept
{
	return mirror::get_source_line<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_source_column(X)
noexcept
{
	return mirror::get_source_column<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_base_name(X)
noexcept
{
	return mirror::get_base_name<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_display_name(X)
noexcept
{
	return mirror::get_display_name<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_scope(X)
noexcept
{
	return mirror::get_scope<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_type(X)
noexcept
{
	return mirror::get_type<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_base_classes(X)
noexcept
{
	return mirror::get_base_classes<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_data_members(X)
noexcept
{
	return mirror::get_data_members<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_meta_object<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_member_types(X)
noexcept
{
	return mirror::get_member_types<X>{};
}


} // namespace puddle

#endif //include guard

