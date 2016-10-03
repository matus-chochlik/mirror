/**
 * @file mirror/get_constant.hpp
 * @brief Implementation of `get_constant` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_CONSTANT_1105240825_HPP
#define MIRROR_GET_CONSTANT_1105240825_HPP

#include "metaobject.hpp"
#include "conditional.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_constant;

template <typename MO>
struct op_get_constant<metaobject<MO>>
 : lazy_conditional_c<
	reflbase::Constant<MO>,
	reflbase::get_constant<MO>,
	none
> { };

template <>
struct op_get_constant<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_constant = eval<_aux::op_get_constant<X>>;

} // namespace mirror

#endif //include guard

