/**
 * @file puddle/meta_record_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_META_RECORD_OPS_1105240825_HPP
#define PUDDLE_META_RECORD_OPS_1105240825_HPP

#include <mirror/is_class.hpp>
#include <mirror/is_struct.hpp>
#include <mirror/is_union.hpp>
#include <mirror/get_data_members.hpp>
#include <mirror/get_public_data_members.hpp>
#include <mirror/get_member_types.hpp>
#include <mirror/get_public_member_types.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto is_class(X)
noexcept
{
	return mirror::is_class<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto is_struct(X)
noexcept
{
	return mirror::is_struct<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto is_union(X)
noexcept
{
	return mirror::is_union<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_data_members(X)
noexcept
{
	return mirror::get_data_members<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_public_data_members(X)
noexcept
{
	return mirror::get_public_data_members<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_member_types(X)
noexcept
{
	return mirror::get_member_types<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_public_member_types(X)
noexcept
{
	return mirror::get_public_member_types<X>{};
}

} // namespace puddle

#endif //include guard

