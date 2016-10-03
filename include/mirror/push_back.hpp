/**
 * @file mirror/push_back.hpp
 * @brief Implementation of the `push_back` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_PUSH_BACK_1105240825_HPP
#define MIRROR_PUSH_BACK_1105240825_HPP

#include "int_const.hpp"
#include "range.hpp"
#include "string.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X, typename E>
struct op_push_back;

template <typename E>
struct op_push_back<empty_range, E>
 : range<E>
{ };

template <typename ... T, typename E>
struct op_push_back<range<T...>, E>
 : range<T..., E>
{ };

template <typename ... T>
struct op_push_back<range<T...>, none>
 : range<T...>
{ };

template <typename Char, Char E>
struct op_push_back<basic_string<Char>, int_const<Char, E>>
 : basic_string<Char, E>
{ };

template <typename Char, Char ... T, Char E>
struct op_push_back<basic_string<Char, T...>, int_const<Char, E>>
 : basic_string<Char, T..., E>
{ };

template <typename Char, Char ... T>
struct op_push_back<basic_string<Char, T...>, none>
 : basic_string<Char, T...>
{ };

} // namespace _aux

template <typename X, typename E>
using push_back = eval<_aux::op_push_back<X, E>>;

} // namespace mirror

#endif //include guard

