/**
 * @file mirror/get_public_base_classes.hpp
 * @brief Implementation of `get_public_base_classes` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_PUBLIC_BASE_CLASSES_1105240825_HPP
#define MIRROR_GET_PUBLIC_BASE_CLASSES_1105240825_HPP

#include "metaobject_ops.hpp"
#include "range.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_public_base_classes;

template <typename MO>
struct op_get_public_base_classes<metaobject<MO>>
 : make_metaobject_sequence_if_c<
	reflbase::Class<MO>,
	reflbase::get_public_base_classes<MO>
> { };

template <>
struct op_get_public_base_classes<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_public_base_classes = eval<_aux::op_get_public_base_classes<X>>;

} // namespace mirror

#endif //include guard

