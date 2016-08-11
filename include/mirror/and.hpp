/**
 * @file mirror/and.hpp
 * @brief Implementation of the `and_` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_AND_1105240825_HPP
#define MIRROR_AND_1105240825_HPP

#include "int_const.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename ... P>
struct op_and;

template <bool B>
struct op_and<bool_<B>>
 : bool_<B>
{ };

template <bool BL, typename BoolR>
struct op_and<bool_<BL>, BoolR>
 : conditional<bool_<BL>, BoolR, false_>
{ };

template <bool B1, typename Bool2, typename Bool3, typename ... BoolP>
struct op_and<bool_<B1>, Bool2, Bool3, BoolP...>
 : conditional<bool_<B1>, op_and<Bool2, Bool3, BoolP...>, false_> 
{ };

} // namespace _aux

template <typename ... P>
using and_ = eval<_aux::op_and<P...>>;

} // namespace mirror

#endif //include guard

