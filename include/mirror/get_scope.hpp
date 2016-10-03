/**
 * @file mirror/get_scope.hpp
 * @brief Implementation of `get_scope` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_SCOPE_1105240825_HPP
#define MIRROR_GET_SCOPE_1105240825_HPP

#include "metaobject_ops.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_scope;

template <typename MO>
struct op_get_scope<metaobject<MO>>
 : make_metaobject_if_c<
	reflbase::ScopeMember<MO> && !reflbase::GlobalScope<MO>,
	reflbase::get_scope<MO>
> { };

template <>
struct op_get_scope<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_scope = eval<_aux::op_get_scope<X>>;

} // namespace mirror

#endif //include guard

