/**
 * @file mirror/equal.hpp
 * @brief Implementation of `equal` operations
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_EQUAL_1105240825_HPP
#define MIRROR_EQUAL_1105240825_HPP

#include "integers.hpp"
#include "range.hpp"
#include "string.hpp"
#include "optional.hpp"

namespace mirror {
namespace _aux {

template <typename L, typename R>
struct op_equal;

// integers
template <typename IL, typename IR, IL VL, IR VR>
struct op_equal<std::integral_constant<IL, VL>, std::integral_constant<IR, VR>>
 : bool_<bool(VL == VR)>
{ };

// range
template <typename ... P>
struct op_equal<range<P...>, range<P...>>
 : true_
{ };

template <typename ... PL, typename ... PR>
struct op_equal<range<PL...>, range<PR...>>
 : false_
{ };

// basic_string
template <typename Char, Char ... C>
struct op_equal<basic_string<Char, C...>, basic_string<Char, C...>>
 : true_
{ };

template <typename CharL, typename CharR, CharL ... CL, CharR ... CR>
struct op_equal<basic_string<CharL, CL...>, basic_string<CharR, CR...>>
 : false_
{ };

// optional
template <typename P>
struct op_equal<optional<P>, optional<P>>
 : true_
{ };

template <typename PL, typename PR>
struct op_equal<optional<PL>, optional<PR>>
 : false_
{ };


} // namespace _aux

template <typename L, typename R>
using equal = eval<_aux::op_equal<L, R>>;

} // namespace mirror

#endif //include guard

