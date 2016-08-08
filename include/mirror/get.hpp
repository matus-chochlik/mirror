/**
 * @file mirror/get.hpp
 * @brief Implementation of the `get` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_1105240825_HPP
#define MIRROR_GET_1105240825_HPP

#include "int_const.hpp"
#include "optional.hpp"
#include "range.hpp"
#include "string.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get;

template <>
struct op_get<empty_range>
 : none
{ };

template <typename T>
struct op_get<optional<T>>
 : identity<T>
{ };

template <typename H, typename ... T>
struct op_get<range<H, T...>>
 : identity<H>
{ };

template <typename Char>
struct op_get<basic_string<Char>>
 : int_const<Char, Char(0)>
{ };

template <typename Char, Char CH, Char ... CT>
struct op_get<basic_string<Char, CH, CT...>>
 : int_const<Char, CH>
{ };

} // namespace _aux

template <typename X>
using get = eval<_aux::op_get<X>>;

} // namespace mirror

#endif //include guard

