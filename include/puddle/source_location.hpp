/**
 * @file puddle/source_location.hpp
 * @brief Implementation of the source location operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_SOURCE_LOCATION_1105240825_HPP
#define PUDDLE_SOURCE_LOCATION_1105240825_HPP

#include <mirror/get_source_file.hpp>
#include <mirror/get_source_line.hpp>
#include <mirror/get_source_column.hpp>
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

} // namespace puddle

#endif //include guard

