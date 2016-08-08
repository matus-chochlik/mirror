/**
 * @file mirror/push_front.hpp
 * @brief Implementation of the `push_front` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_PUSH_FRONT_1105240825_HPP
#define MIRROR_PUSH_FRONT_1105240825_HPP

#include "int_const.hpp"
#include "range.hpp"
#include "string.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X, typename E>
struct op_push_front;

template <typename E>
struct op_push_front<empty_range, E>
 : range<E>
{ };

template <typename ... T, typename E>
struct op_push_front<range<T...>, E>
 : range<E, T...>
{ };

template <typename Char, Char E>
struct op_push_front<basic_string<Char>, int_const<Char, E>>
 : basic_string<Char, E>
{ };

template <typename Char, Char ... C, Char E>
struct op_push_front<basic_string<Char, C...>, int_const<Char, E>>
 : basic_string<Char, E, C...>
{ };

} // namespace _aux

template <typename X, typename E>
using push_front = eval<_aux::op_push_front<X, E>>;

} // namespace mirror

#endif //include guard

