/**
 * @file puddle/meta_named_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_META_NAMED_OPS_1105240825_HPP
#define PUDDLE_META_NAMED_OPS_1105240825_HPP

#include <mirror/is_anonymous.hpp>
#include <mirror/get_base_name.hpp>
#include <mirror/get_full_name.hpp>
#include <mirror/get_display_name.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto is_anonymous(X)
noexcept
{
	return mirror::is_anonymous<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_base_name(X)
noexcept
{
	return mirror::get_base_name<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_full_name(X)
noexcept
{
	return mirror::get_full_name<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_display_name(X)
noexcept
{
	return mirror::get_display_name<X>{};
}

} // namespace puddle

#endif //include guard

