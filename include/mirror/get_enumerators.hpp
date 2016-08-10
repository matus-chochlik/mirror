/**
 * @file mirror/get_enumerators.hpp
 * @brief Implementation of `get_enumerators` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_ENUMERATORS_1105240825_HPP
#define MIRROR_GET_ENUMERATORS_1105240825_HPP

#include <reflexpr>
#include "metaobjects.hpp"
#include "conditional.hpp"
#include "range.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_enumerators;

template <typename MO>
struct op_get_enumerators<meta_object<MO>>
 : conditional<
	bool_<std::meta::Enum<MO>>,
	meta_object_sequence<std::meta::get_enumerators_m<MO>>,
	none
> { };

} // namespace _aux

template <typename X>
using get_enumerators = eval<_aux::op_get_enumerators<X>>;

} // namespace mirror

#endif //include guard

