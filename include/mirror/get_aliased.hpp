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

#include <reflexpr>
#include "conditional.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_aliased;

template <typename MO>
struct op_get_aliased<metaobject<MO>>
 : lazy_conditional_c<
	std::meta::Alias<MO>,
	metaobject<std::meta::get_aliased_m<MO>>,
	metaobject<MO>
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

