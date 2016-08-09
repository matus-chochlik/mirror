/**
 * @file mirror/traits.hpp
 * @brief Implementation of traits
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_TRAITS_1105240825_HPP
#define MIRROR_TRAITS_1105240825_HPP

#include "int_const.hpp"
#include "string.hpp"
#include "range.hpp"
#include "metaobjects.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_string
 : false_
{ };

template <typename Char, Char ... C>
struct op_is_string<basic_string<Char, C...>>
 : true_
{ };

template <typename X>
struct op_is_range
 : false_
{ };

template <typename ... P>
struct op_is_range<range<P...>>
 : true_
{ };

template <typename X>
struct op_is_meta_object
 : false_
{ };

template <typename MO>
struct op_is_meta_object<meta_object<MO>>
 : true_
{ };

template <typename MOS>
struct op_is_meta_object<meta_object_sequence<MOS>>
 : true_
{ };

template <typename X>
struct op_is_none
 : false_
{ };

template <>
struct op_is_none<none>
 : true_
{ };

} // namespace _aux

template <typename X>
using is_string = eval<_aux::op_is_string<X>>;

template <typename X>
using is_range = eval<_aux::op_is_range<X>>;

template <typename X>
using is_meta_object = eval<_aux::op_is_meta_object<X>>;

template <typename X>
using is_none = eval<_aux::op_is_none<X>>;

} // namespace mirror

#endif //include guard

