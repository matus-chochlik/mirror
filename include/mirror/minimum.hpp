/**
 * @file mirror/minimum.hpp
 * @brief Implementation of `minimum` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_MINIMUM_1105240825_HPP
#define MIRROR_MINIMUM_1105240825_HPP

#include "conditional.hpp"
#include "int_const.hpp"

namespace mirror {
namespace _aux {

template <typename L, typename R>
struct op_minimum;

// int_const
template <typename IL, typename IR, IL VL, IR VR>
struct op_minimum<int_const<IL, VL>, int_const<IR, VR>>
 : conditional_c<(VL <  VR), int_const<IL, VL>, int_const<IR, VR>>
{ };

} // namespace _aux

template <typename L, typename R>
using minimum = eval<_aux::op_minimum<L, R>>;

} // namespace mirror

#endif //include guard

