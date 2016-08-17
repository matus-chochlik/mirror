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
#include <mirror/get_full_name.hpp>
#include <mirror/get_display_name.hpp>
#include <mirror/get_scope.hpp>
#include <mirror/get_type.hpp>
#include <mirror/get_aliased.hpp>
#include <mirror/get_elaborated_type_specifier.hpp>
#include <mirror/get_access_specifier.hpp>
#include <mirror/get_base_classes.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_enumerators.hpp>
#include <mirror/get_reflected_type.hpp>
#include <mirror/is_class.hpp>
#include <mirror/is_struct.hpp>
#include <mirror/is_union.hpp>
#include <mirror/is_enum.hpp>
#include <mirror/is_scoped_enum.hpp>
#include <mirror/enable_if.hpp>
#include <mirror/traits.hpp>

namespace puddle {

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_full_name(X)
noexcept
{
	return mirror::get_full_name<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_aliased(X)
noexcept
{
	return mirror::get_aliased<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_elaborated_type_specifier(X)
noexcept
{
	return mirror::get_elaborated_type_specifier<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_access_specifier(X)
noexcept
{
	return mirror::get_access_specifier<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto is_class(X)
noexcept
{
	return mirror::is_class<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto is_struct(X)
noexcept
{
	return mirror::is_struct<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto is_union(X)
noexcept
{
	return mirror::is_union<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto is_enum(X)
noexcept
{
	return mirror::is_enum<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto is_scoped_enum(X)
noexcept
{
	return mirror::is_scoped_enum<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
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
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_member_types(X)
noexcept
{
	return mirror::get_member_types<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_enumerators(X)
noexcept
{
	return mirror::get_enumerators<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto get_reflected_type(X)
noexcept
{
	return mirror::identity<mirror::get_reflected_type<X>>{};
}


} // namespace puddle

#endif //include guard

