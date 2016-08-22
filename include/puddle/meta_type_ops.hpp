/**
 * @file puddle/meta_type_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_META_TYPE_OPS_1105240825_HPP
#define PUDDLE_META_TYPE_OPS_1105240825_HPP

#include <mirror/get_reflected_type.hpp>
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
auto get_reflected_type(X)
noexcept
{
	return mirror::identity<mirror::get_reflected_type<X>>{};
}

} // namespace puddle

#endif //include guard

