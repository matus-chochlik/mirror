/**
 * @file mirror/value.hpp
 * @brief Implementation of the `value` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_VALUE_1105240825_HPP
#define MIRROR_VALUE_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_value;

template <typename Int, Int I>
struct op_value<int_const<Int, I>>
 : int_const<Int, I>
{ };

template <typename Int, Int I>
struct op_value<int_const<const Int, I>>
 : int_const<Int, I>
{ };

template <>
struct op_value<none>
 : int_const<int, 0>
{ };

} // namespace _aux

template <typename X>
constexpr auto value = _aux::op_value<eval<X>>::value;

} // namespace mirror

#endif //include guard

