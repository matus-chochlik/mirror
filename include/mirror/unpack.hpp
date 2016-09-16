/**
 * @file mirror/unpack.hpp
 * @brief Implementation of the `unpack` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_UNPACK_1105240825_HPP
#define MIRROR_UNPACK_1105240825_HPP

#include "metaobject.hpp"
#include "identity.hpp"
#include "range.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_unpack;

template <typename ... MO>
using mo_range = range<metaobject<MO>...>;

template <typename MOS>
struct op_unpack<metaobject_sequence<MOS>>
 : reflbase::unpack_sequence<MOS, mo_range>
{ };

template <typename ... P>
struct op_unpack<range<P...>>
 : range<P...>
{ };

template <>
struct op_unpack<none>
 : empty_range
{ };

} // namespace _aux

template <typename X>
using unpack = eval<_aux::op_unpack<X>>;

} // namespace mirror

#endif //include guard

