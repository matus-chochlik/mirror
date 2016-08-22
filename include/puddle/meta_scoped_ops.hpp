/**
 s* @file puddle/meta_scoped_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_META_SCOPED_OPS_1105240825_HPP
#define PUDDLE_META_SCOPED_OPS_1105240825_HPP

#include <mirror/get_scope.hpp>
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
auto get_scope(X)
noexcept
{
	return mirror::get_scope<X>{};
}

} // namespace puddle

#endif //include guard

