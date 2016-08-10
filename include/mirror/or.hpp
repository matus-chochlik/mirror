/**
 * @file mirror/or.hpp
 * @brief Implementation of the `or_` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_OR_1105240825_HPP
#define MIRROR_OR_1105240825_HPP

#include "int_const.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename ... P>
struct op_or;

template <bool B>
struct op_or<bool_<B>>
 : bool_<B>
{ };

template <bool BL, typename BoolR>
struct op_or<bool_<BL>, BoolR>
 : conditional<bool_<BL>, true_, BoolR>
{ };

template <bool B1, typename Bool2, typename Bool3, typename ... BoolP>
struct op_or<bool_<B1>, Bool2, Bool3, BoolP...>
 : conditional<bool_<B1>, true_, op_or<Bool2, Bool3, BoolP...>> 
{ };

} // namespace _aux

template <typename ... P>
using or_ = eval<_aux::op_or<P...>>;

} // namespace mirror

#endif //include guard

