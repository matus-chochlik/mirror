/**
 * @file mirror/get_member_types.hpp
 * @brief Implementation of `get_member_types` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_MEMBER_TYPES_1105240825_HPP
#define MIRROR_GET_MEMBER_TYPES_1105240825_HPP

#include "metaobject_ops.hpp"
#include "range.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_member_types;

template <typename MO>
struct op_get_member_types<metaobject<MO>>
 : make_metaobject_sequence_if_c<
	reflbase::Record<MO>,
	reflbase::get_member_types<MO>
> { };

template <>
struct op_get_member_types<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_member_types = eval<_aux::op_get_member_types<X>>;

} // namespace mirror

#endif //include guard

