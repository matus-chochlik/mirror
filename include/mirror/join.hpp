/**
 * @file mirror/join.hpp
 * @brief Implementation of the `join` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_JOIN_1105240825_HPP
#define MIRROR_JOIN_1105240825_HPP

#include "concat.hpp"

namespace mirror {
namespace _aux {

template <typename Sep, typename ... X>
struct op_join;

template <typename ... P>
struct op_join<range<P...>>
 : empty_range
{ };

template <typename Char, Char ... C>
struct op_join<basic_string<Char, C...>>
 : basic_string<Char>
{ };

template <typename ... PS, typename ... P>
struct op_join<range<PS...>, range<P...>>
 : range<P...>
{ };

template <typename Char, Char ... CS, Char ... C>
struct op_join<basic_string<Char, CS...>, basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename Sep, typename H1, typename H2, typename ... T>
struct op_join<Sep, H1, H2, T...>
 : concat<H1, Sep, eval<op_join<Sep, H2, T...>>>
{ };

} // namespace _aux

template <typename Sep, typename ... X>
using join = eval<_aux::op_join<Sep, X...>>;

} // namespace mirror

#endif //include guard

