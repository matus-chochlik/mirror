/**
 * @file mirror/get_data_members.hpp
 * @brief Implementation of `get_data_members` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_DATA_MEMBERS_1105240825_HPP
#define MIRROR_GET_DATA_MEMBERS_1105240825_HPP

#include "metaobject_ops.hpp"
#include "range.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_data_members;

template <typename MO>
struct op_get_data_members<metaobject<MO>>
 : make_metaobject_sequence_if_c<
	reflbase::Record<MO>,
	reflbase::get_data_members<MO>
> { };

template <>
struct op_get_data_members<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_data_members = eval<_aux::op_get_data_members<X>>;

} // namespace mirror

#endif //include guard

