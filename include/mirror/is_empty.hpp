/**
 * @file mirror/is_empty.hpp
 * @brief Implementation of the `is_empty` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_EMPTY_1105240825_HPP
#define MIRROR_IS_EMPTY_1105240825_HPP

#include "integers.hpp"
#include "range.hpp"
#include "string.hpp"
#include "optional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_empty;

template <typename T>
struct op_is_empty<optional<T>>
 : false_
{ };

template <>
struct op_is_empty<optional<none>>
 : true_
{ };

template <typename ... P>
struct op_is_empty<range<P...>>
 : bool_<sizeof ... (P) == 0>
{ };

template <typename Char, Char ... C>
struct op_is_empty<basic_string<Char, C...>>
 : bool_<sizeof ... (C) == 0>
{ };

} // namespace _aux

template <typename X>
using is_empty = eval<_aux::op_is_empty<X>>;

} // namespace mirror

#endif //include guard

