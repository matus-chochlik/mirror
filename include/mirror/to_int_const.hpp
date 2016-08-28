/**
 * @file mirror/to_int_const.hpp
 * @brief Implementation of the `to_int_const` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_TO_INT_CONST_1105240825_HPP
#define MIRROR_TO_INT_CONST_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename Int, typename ICC>
struct op_to_int_const
 : int_const<Int, ICC::value>
{ };

template <typename X>
struct op_to_int_const<none, X>
 : none
{ };

} // namespace _aux

template <typename Int, typename ICC>
using to_int_const = eval<_aux::op_to_int_const<Int, ICC>>;

} // namespace mirror

#endif //include guard

