/**
 * @file mirror/get_base_class.hpp
 * @brief Implementation of `get_base_class` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_BASE_CLASS_1105240825_HPP
#define MIRROR_GET_BASE_CLASS_1105240825_HPP

#include "metaobject_ops.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_base_class;

template <typename MO>
struct op_get_base_class<metaobject<MO>>
 : make_metaobject_if_c<
	reflbase::Inheritance<MO>,
	reflbase::get_base_class<MO>
> { };

template <>
struct op_get_base_class<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_base_class = eval<_aux::op_get_base_class<X>>;

} // namespace mirror

#endif //include guard

