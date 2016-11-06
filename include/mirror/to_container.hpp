/**
 * @file mirror/to_container.hpp
 * @brief Implementation of the `to_container` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_TO_CONTAINER_1105240825_HPP
#define MIRROR_TO_CONTAINER_1105240825_HPP

#include "int_const.hpp"
#include "range.hpp"
#include "string.hpp"
#include "none.hpp"
#include "identity.hpp"
#include "metaobject.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_to_container;

template <>
struct op_to_container<none>
 : none
{ };

template <typename P>
struct op_to_container<identity<P>>
 : range<P>
{ };

template <typename ... P>
struct op_to_container<range<P...>>
 : range<P...>
{ };

template <typename Char, Char ... C>
struct op_to_container<basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename Char, Char C>
struct op_to_container<int_const<Char, C>>
 : basic_string<Char, C>
{ };

template <typename MO>
struct op_to_container<metaobject<MO>>
 : metaobject<MO>
{ };

template <typename MOS>
struct op_to_container<metaobject_sequence<MOS>>
 : metaobject_sequence<MOS>
{ };

} // namespace _aux

template <typename X>
using to_container = eval<_aux::op_to_container<X>>;

} // namespace mirror

#endif //include guard

