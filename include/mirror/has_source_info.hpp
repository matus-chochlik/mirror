/**
 * @file mirror/has_source_info.hpp
 * @brief Implementation of the `has_source_info` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_HAS_SOURCE_LOCATION_1105240825_HPP
#define MIRROR_HAS_SOURCE_LOCATION_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_has_source_info;

template <>
struct op_has_source_info<none>
 : false_
{ };

template <typename MO>
struct op_has_source_info<metaobject<MO>>
 : bool_<reflbase::get_source_line_v<MO> != 0u>
{ };

} // namespace _aux

template <typename X>
using has_source_info = eval<_aux::op_has_source_info<X>>;

} // namespace mirror

#endif //include guard

