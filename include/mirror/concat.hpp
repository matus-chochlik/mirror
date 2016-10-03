/**
 * @file mirror/concat.hpp
 * @brief Implementation of the `concat` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_CONCAT_1105240825_HPP
#define MIRROR_CONCAT_1105240825_HPP

#include "identity.hpp"
#include "none.hpp"
#include "range.hpp"
#include "string.hpp"

namespace mirror {
namespace _aux {

template <typename ... X>
struct op_concat;

template <typename H1, typename H2, typename H3, typename ... T>
struct op_concat<H1, H2, H3, T...>
 : op_concat<eval<_aux::op_concat<H1, H2>>, H3, T...>
{ };

// none
template <>
struct op_concat<none, none>
 : none
{ };

template <typename R>
struct op_concat<none, R>
 : identity<R>
{ };

template <typename R>
struct op_concat<R, none>
 : identity<R>
{ };

// range
template <typename ... P>
struct op_concat<range<P...>>
 : range<P...>
{ };

template <typename ... PL, typename ... PR>
struct op_concat<range<PL...>, range<PR...>>
 : range<PL..., PR...>
{ };

// basic_string
template <typename Char, Char ... C>
struct op_concat<basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename Char, Char ... CL, Char ... CR>
struct op_concat<basic_string<Char, CL...>, basic_string<Char, CR...>>
 : basic_string<Char, CL..., CR...>
{ };

} // namespace _aux

template <typename ... X>
using concat = eval<_aux::op_concat<X...>>;

} // namespace mirror

#endif //include guard

