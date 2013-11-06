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

#ifndef MIRROR_TRAITS_1310291537_HPP
#define MIRROR_TRAITS_1310291537_HPP

#include <mirror/stddef.hpp>

namespace mirror {

template <typename X>
struct is_metaobject
 : false_type
{ };

template <typename T, typename M>
struct is_metaobject<meta<T, M>>
 : true_type
{ };

template <typename X>
struct is_specifier
 : false_type
{ };

template <typename T>
struct is_specifier<spec<T>>
 : true_type
{ };

template <typename X>
struct has_name
 : false_type
{ };

template <typename X>
struct has_scope
 : false_type
{ };

template <typename X>
struct is_scope
 : false_type
{ };

template <typename X>
struct is_class_member
 : false_type
{ };

template <typename X>
struct has_template
 : false_type
{ };

template <typename X>
struct is_template
 : false_type
{ };


} // namespace mirror

#endif // include guard
