/**
 * @file mirror/get_reflected_type.hpp
 * @brief Implementation of `get_reflected_type` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_REFLECTED_TYPE_1105240825_HPP
#define MIRROR_GET_REFLECTED_TYPE_1105240825_HPP

#include "metaobject.hpp"
#include "conditional.hpp"
#include "none.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_reflected_type;

template <typename MO>
struct op_get_reflected_type<metaobject<MO>>
 : identity<lazy_conditional_c<
	reflbase::Type<MO>,
	reflbase::get_reflected_type<MO>,
	none
>> { };

} // namespace _aux

template <typename X>
using get_reflected_type = eval<_aux::op_get_reflected_type<X>>;

} // namespace mirror

#endif //include guard

