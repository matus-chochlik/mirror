/**
 * @file mirror/get_aliased.hpp
 * @brief Implementation of `get_aliased` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_ALIASED_1105240825_HPP
#define MIRROR_GET_ALIASED_1105240825_HPP

#include "metaobject_ops.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_aliased;

template <typename MO>
struct op_get_aliased<metaobject<MO>>
 : make_metaobject_if_c<
	reflbase::Alias<MO>,
	reflbase::get_aliased<MO>, MO
> { };

template <>
struct op_get_aliased<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_aliased = eval<_aux::op_get_aliased<X>>;

} // namespace mirror

#endif //include guard

