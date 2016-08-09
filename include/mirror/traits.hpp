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
#include "optional.hpp"
#include "metaobjects.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct is_string
 : false_
{ };

template <typename Char, Char ... C>
struct is_string<basic_string<Char, C...>>
 : true_
{ };

template <typename X>
struct is_range
 : false_
{ };

template <typename ... P>
struct is_range<range<P...>>
 : true_
{ };

template <typename X>
struct is_optional
 : false_
{ };

template <typename T>
struct is_optional<optional<T>>
 : true_
{ };

template <typename X>
struct is_meta_object
 : false_
{ };

template <typename MO>
struct is_meta_object<meta_object<MO>>
 : true_
{ };

} // namespace _aux

template <typename X>
using is_string = eval<_aux::is_string<X>>;

template <typename X>
using is_range = eval<_aux::is_range<X>>;

template <typename X>
using is_optional = eval<_aux::is_optional<X>>;

template <typename X>
using is_meta_object = eval<_aux::is_meta_object<X>>;

} // namespace mirror

#endif //include guard

