/**
 * @file mirror/minus.hpp
 * @brief Implementation of the `minus` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_MINUS_1105240825_HPP
#define MIRROR_MINUS_1105240825_HPP

#include "int_const.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename L, typename R>
struct op_minus;

template <typename Int, Int IL, Int IR>
struct op_minus<int_const<Int, IL>, int_const<Int, IR>>
 : int_const<Int, IL-IR>
{ };

} // namespace _aux

template <typename L, typename R>
using minus = eval<_aux::op_minus<L, R>>;

} // namespace mirror

#endif //include guard

