/**
 * @file mirror/get_fingerprint.hpp
 * @brief Implementation of `get_fingerprint` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_FINGERPRINT_1105240825_HPP
#define MIRROR_GET_FINGERPRINT_1105240825_HPP

#include <reflexpr>

namespace mirror {

// TODO: do something better here?
using fingerprint = uint64_t;

namespace _aux {

template <typename X>
struct op_get_fingerprint;

template <__metaobject_id MOID>
struct op_get_fingerprint<metaobject<std::__metaobject<MOID>>>
 : std::integral_constant<uint64_t, __metaobject_get_id_value(MOID)>
{ };

template <>
struct op_get_fingerprint<none>
 : std::integral_constant<uint64_t, 0>
{ };

} // namespace _aux

template <typename X>
constexpr fingerprint get_fingerprint = _aux::op_get_fingerprint<X>::value;


} // namespace mirror

#endif //include guard

