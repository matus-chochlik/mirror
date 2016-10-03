/**
 * @file mirror/get_elaborated_type_specifier.hpp
 * @brief Implementation of `get_elaborated_type_specifier` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_ELABORATED_TYPE_SPECIFIER_1105240825_HPP
#define MIRROR_GET_ELABORATED_TYPE_SPECIFIER_1105240825_HPP

#include "metaobject_ops.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_elaborated_type_specifier;

template <typename MO>
struct op_get_elaborated_type_specifier<metaobject<MO>>
 : make_metaobject_if_c<
	reflbase::TagType<MO>,
	reflbase::get_elaborated_type_specifier<MO>
> { };

template <>
struct op_get_elaborated_type_specifier<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_elaborated_type_specifier =
	eval<_aux::op_get_elaborated_type_specifier<X>>;

} // namespace mirror

#endif //include guard

