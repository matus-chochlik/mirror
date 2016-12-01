/**
 * @file mirror/get_size.hpp
 * @brief Implementation of the `get_size` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_SIZE_1105240825_HPP
#define MIRROR_GET_SIZE_1105240825_HPP

#include "to_container.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_size;

template <>
struct op_get_size<none>
 : size_t_<0u>
{ };

template <typename ... P>
struct op_get_size<range<P...>>
 : size_t_<sizeof ... (P)>
{ };

template <typename Char, Char ... C>
struct op_get_size<basic_string<Char, C...>>
 : size_t_<sizeof ... (C)>
{ };

template <typename MO>
struct op_get_size<metaobject_sequence<MO>>
 : size_t_<reflbase::get_size_v<MO>>
{ };

} // namespace _aux

template <typename X>
using get_size = eval<_aux::op_get_size<to_container<X>>>;

template <typename X>
using size = get_size<X>;

} // namespace mirror

#endif //include guard

