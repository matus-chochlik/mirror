/**
 *  @file mire/mirror/traits.hpp
 *  @brief Metaobject traits
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_TRAITS_1310291537_HPP
#define MIRE_MIRROR_TRAITS_1310291537_HPP

#include <mire/ct/int_const.hpp>

namespace mire {
namespace mirror {

template <typename X>
struct is_metaobject
 : ct::false_type
{ };

template <typename T, typename M>
struct is_metaobject<meta<T, M>>
 : ct::true_type
{ };

template <typename X>
struct is_specifier
 : ct::false_type
{ };

template <typename T>
struct is_specifier<spec<T>>
 : ct::true_type
{ };

template <typename X>
struct has_name
 : ct::false_type
{ };

template <typename X>
struct has_scope
 : ct::false_type
{ };

template <typename X>
struct is_scope
 : ct::false_type
{ };

template <typename X>
struct is_class_member
 : ct::false_type
{ };

template <typename X>
struct has_template
 : ct::false_type
{ };

template <typename X>
struct is_template
 : ct::false_type
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
