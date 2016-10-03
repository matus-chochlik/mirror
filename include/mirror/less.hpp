/**
 * @file mirror/less.hpp
 * @brief Implementation of `less` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_LESS_1105240825_HPP
#define MIRROR_LESS_1105240825_HPP

#include "int_const.hpp"
#include "range.hpp"
#include "string.hpp"

namespace mirror {
namespace _aux {

template <typename L, typename R>
struct op_less;

template <typename L, typename R>
struct op_less_equal;

// int_const
template <typename IL, typename IR, IL VL, IR VR>
struct op_less<int_const<IL, VL>, int_const<IR, VR>>
 : bool_<bool(VL <  VR)>
{ };

// int_const
template <typename IL, typename IR, IL VL, IR VR>
struct op_less_equal<int_const<IL, VL>, int_const<IR, VR>>
 : bool_<bool(VL <= VR)>
{ };

} // namespace _aux

template <typename L, typename R>
using less = eval<_aux::op_less<L, R>>;

template <typename L, typename R>
using less_equal = eval<_aux::op_less_equal<L, R>>;

} // namespace mirror

#endif //include guard

