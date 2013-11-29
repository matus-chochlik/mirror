/**
 *  @file mire/mirror/elaborated_type.hpp
 *  @brief Implementation of the elaborated_type metafunction.
 *
 *  @author Matus Chochlik
 *
 *  Copyright 2006-2013 Matus Chochlik. Distributed under the Boost
 *  Software License, Version 1.0. (See accompanying file
 *  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
 */

#ifndef MIRE_MIRROR_ELABORATED_TYPE_1310291537_HPP
#define MIRE_MIRROR_ELABORATED_TYPE_1310291537_HPP

#include <mire/mirror/default.hpp>
#include <mire/mirror/tags.hpp>

namespace mire {
namespace mirror {
namespace _aux {

template <typename Reg, typename MOC>
struct elaborated_type
 : mirror::spec<spec_none_tag>
{ };

template <typename Reg>
struct elaborated_type<Reg, mirror::meta_enum_tag>
 : mirror::spec<typename Reg::elaborated_type>
{ };

template <typename Reg>
struct elaborated_type<Reg, mirror::meta_class_tag>
 : mirror::spec<typename Reg::elaborated_type>
{ };

template <typename Reg>
struct elaborated_type<Reg, mirror::meta_typedef_tag>
 : mirror::spec<typename Reg::typedef_type::elaborated_type>
{ };

} // namespace _aux

template <typename R, typename M>
struct elaborated_type<meta<R, M>>
 : _aux::elaborated_type<R, typename R::category>
{ };

} // namespace mirror
} // namespace mire

#endif // include guard
