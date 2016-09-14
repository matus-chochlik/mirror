/**
 * @file puddle/meta_enum_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_META_ENUM_OPS_1105240825_HPP
#define PUDDLE_META_ENUM_OPS_1105240825_HPP

#include <mirror/is_enum.hpp>
#include <mirror/is_scoped_enum.hpp>
#include <mirror/get_enumerators.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto is_enum(X)
noexcept
{
	return mirror::is_enum<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto is_scoped_enum(X)
noexcept
{
	return mirror::is_scoped_enum<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_enumerators(X)
noexcept
{
	return mirror::get_enumerators<X>{};
}

} // namespace puddle

#endif //include guard

