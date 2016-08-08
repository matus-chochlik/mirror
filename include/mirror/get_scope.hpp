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

#include <reflexpr>
#include "metaobjects.hpp"
#include "conditional.hpp"
#include "optional.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_scope;

template <typename MO>
struct op_get_scope<meta_object<MO>>
 : conditional<
	bool_<std::meta::ScopeMember<MO>>,
	optional<meta_object<std::meta::get_scope_m<MO>>>,
	empty_optional
> { };

} // namespace _aux

template <typename X>
using get_scope = eval<_aux::op_get_scope<X>>;

} // namespace mirror

#endif //include guard

