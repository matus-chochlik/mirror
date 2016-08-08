/**
 * @file mirror/plus.hpp
 * @brief Implementation of the `plus` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_PLUS_1105240825_HPP
#define MIRROR_PLUS_1105240825_HPP

#include "int_const.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename L, typename R>
struct op_plus;

template <typename Int, Int IL, Int IR>
struct op_plus<int_const<Int, IL>, int_const<Int, IR>>
 : int_const<Int, IL+IR>
{ };

} // namespace _aux

template <typename L, typename R>
using plus = eval<_aux::op_plus<L, R>>;

} // namespace mirror

#endif //include guard

