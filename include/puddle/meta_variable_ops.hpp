/**
 * @file puddle/meta_variable_ops.hpp
 * @brief Implementation of the metaobject operation wrappers
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_META_VARIABLE_OPS_1105240825_HPP
#define PUDDLE_META_VARIABLE_OPS_1105240825_HPP

#include <mirror/get_pointer.hpp>
#include <mirror/dereference.hpp>
#include <puddle/enable_if.hpp>

namespace puddle {

template <typename X, typename = enable_if_opt_metaobject<X>>
static constexpr inline
auto get_pointer(X)
noexcept
{
	return mirror::get_pointer<X>{};
}

template <typename MO, typename = enable_if_metaobject<MO>>
static constexpr inline
auto& dereference(MO)
{
	return mirror::dereference<MO>::apply();
}

template <typename MO, typename T, typename = enable_if_metaobject<MO>>
static constexpr inline
auto& dereference(MO, T& inst)
{
	return mirror::dereference<MO>::apply(inst);
}

} // namespace puddle

#endif //include guard

