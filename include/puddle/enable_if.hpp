/**
 * @file puddle/enable_if.hpp
 * @brief Declaration of enable_if utility
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef PUDDLE_ENABLE_IF_1105240825_HPP
#define PUDDLE_ENABLE_IF_1105240825_HPP

#include <mirror/enable_if.hpp>
#include <mirror/traits.hpp>

namespace puddle {

template <typename X>
using enable_if_int_const
 = mirror::enable_if_any<mirror::is_int_const<X>>;

template <typename X>
using enable_if_metaobject
 = mirror::enable_if_any<mirror::is_metaobject<X>>;

template <typename X>
using enable_if_opt_metaobject
 = mirror::enable_if_any<mirror::is_metaobject<X>, mirror::is_none<X>>;

template <typename X>
using enable_if_any_opt_sequence
 = mirror::enable_if_any<
	mirror::is_metaobject_sequence<X>,
	mirror::is_string<X>,
	mirror::is_range<X>,
	mirror::is_none<X>
>;

template <typename X>
using enable_if_opt_metaobject_sequence
 = mirror::enable_if_any<
	mirror::is_metaobject_sequence<X>,
	mirror::is_none<X>
>;

template <typename X>
using enable_if_opt_eager_sequence
 = mirror::enable_if_any<
	mirror::is_string<X>,
	mirror::is_range<X>,
	mirror::is_none<X>
>;

} // namespace puddle

#endif //include guard

