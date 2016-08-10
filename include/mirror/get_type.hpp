/**
 * @file mirror/get_type.hpp
 * @brief Implementation of `get_type` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_TYPE_1105240825_HPP
#define MIRROR_GET_TYPE_1105240825_HPP

#include <reflexpr>
#include "metaobjects.hpp"
#include "conditional.hpp"
#include "none.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_type;

template <typename MO>
struct op_get_type<meta_object<MO>>
 : conditional<
	bool_<std::meta::Typed<MO>>,
	meta_object<std::meta::get_type_m<MO>>,
	none
> { };

} // namespace _aux

template <typename X>
using get_type = eval<_aux::op_get_type<X>>;

} // namespace mirror

#endif //include guard

