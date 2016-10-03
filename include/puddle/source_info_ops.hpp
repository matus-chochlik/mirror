/**
 * @file puddle/source_info_ops.hpp
 * @brief Implementation of the source location operations.
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_SOURCE_INFO_OPS_1105240825_HPP
#define PUDDLE_SOURCE_INFO_OPS_1105240825_HPP

#include <mirror/has_source_info.hpp>
#include <mirror/get_source_file.hpp>
#include <mirror/get_source_line.hpp>
#include <mirror/get_source_column.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X>
static constexpr inline
auto has_source_info(X)
noexcept
{
	return mirror::has_source_info<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_source_file(X)
noexcept
{
	return mirror::get_source_file<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_source_line(X)
noexcept
{
	return mirror::get_source_line<X>{};
}

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_source_column(X)
noexcept
{
	return mirror::get_source_column<X>{};
}

} // namespace puddle

#endif //include guard

