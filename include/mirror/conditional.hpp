/**
 * @file mirror/conditional.hpp
 * @brief Implementation of the `conditional` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_CONDITIONAL_1105240825_HPP
#define MIRROR_CONDITIONAL_1105240825_HPP

#include "int_const.hpp"

namespace mirror {
namespace _aux {

template <typename Bool, typename IfTrue, typename IfFalse>
struct op_conditional;

template <typename IfTrue, typename Unused>
struct op_conditional<true_, IfTrue, Unused>
 : identity<IfTrue>
{ };

template <typename Unused, typename IfFalse>
struct op_conditional<false_, Unused, IfFalse>
 : identity<IfFalse>
{ };

} // namespace _aux

template <typename Bool, typename IfTrue, typename IfFalse>
using conditional = typename _aux::op_conditional<Bool, IfTrue, IfFalse>::type;

} // namespace mirror

#endif //include guard

