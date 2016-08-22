/**
 * @file puddle/specifier_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_SPECIFIER_OPS_1105240825_HPP
#define PUDDLE_SPECIFIER_OPS_1105240825_HPP

#include <mirror/get_elaborated_type_specifier.hpp>
#include <mirror/get_access_specifier.hpp>
#include <mirror/is_static.hpp>
#include <mirror/is_virtual.hpp>
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
auto is_static(X)
noexcept
{
	return mirror::is_static<X>{};
}

template <
	typename X,
	typename = mirror::enable_if_any<
		mirror::is_metaobject<X>,
		mirror::is_none<X>
	>
> static constexpr inline
auto is_virtual(X)
noexcept
{
	return mirror::is_virtual<X>{};
}

} // namespace puddle

#endif //include guard

