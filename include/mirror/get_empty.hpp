/**
 * @file mirror/get_empty.hpp
 * @brief Implementation of the `get_empty` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_EMPTY_1105240825_HPP
#define MIRROR_GET_EMPTY_1105240825_HPP

#include "int_const.hpp"
#include "range.hpp"
#include "string.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_empty;

template <>
struct op_get_empty<none>
 : none
{ };

template <typename ... P>
struct op_get_empty<range<P...>>
 : empty_range
{ };

template <typename Char, Char ... C>
struct op_get_empty<basic_string<Char, C...>>
 : basic_string<Char>
{ };

} // namespace _aux

template <typename X>
using get_empty = eval<_aux::op_get_empty<X>>;

} // namespace mirror

#endif //include guard

