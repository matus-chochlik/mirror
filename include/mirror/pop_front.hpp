/**
 * @file mirror/pop_front.hpp
 * @brief Implementation of the `pop_front` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_POP_FRONT_1105240825_HPP
#define MIRROR_POP_FRONT_1105240825_HPP

#include "int_const.hpp"
#include "range.hpp"
#include "string.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_pop_front;

template <>
struct op_pop_front<empty_range>
 : empty_range
{ };

template <typename H, typename ... T>
struct op_pop_front<range<H, T...>>
 : range<T...>
{ };

template <typename Char>
struct op_pop_front<basic_string<Char>>
 : basic_string<Char>
{ };

template <typename Char, Char CH, Char ... CT>
struct op_pop_front<basic_string<Char, CH, CT...>>
 : basic_string<Char, CT...>
{ };

} // namespace _aux

template <typename X>
using pop_front = eval<_aux::op_pop_front<X>>;

} // namespace mirror

#endif //include guard

