/**
 * @file mirror/empty.hpp
 * @brief Implementation of the `empty` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_EMPTY_1105240825_HPP
#define MIRROR_EMPTY_1105240825_HPP

#include "integers.hpp"
#include "range.hpp"
#include "string.hpp"

namespace mirror {

template <typename X>
struct op_empty;

template <typename T>
struct op_empty<optional<T>>
 : false_
{ };

template <>
struct op_empty<optional<nil_t>>
 : true_
{ };

template <typename ... P>
struct op_empty<range<P...>>
 : bool_<sizeof ... (P) == 0>
{ };

template <typename Char, Char ... C>
struct op_empty<basic_string<Char, C...>>
 : bool_<sizeof ... (C) == 0>
{ };

template <typename X>
struct empty = typename op_empty<X>::type;

} // namespace mirror

#endif //include guard

