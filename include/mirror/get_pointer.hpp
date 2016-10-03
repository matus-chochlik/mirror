/**
 * @file mirror/get_pointer.hpp
 * @brief Implementation of `get_pointer` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_POINTER_1105240825_HPP
#define MIRROR_GET_POINTER_1105240825_HPP

#include "metaobject.hpp"
#include "conditional.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_pointer;

template <typename MO>
struct op_get_pointer<metaobject<MO>>
 : lazy_conditional_c<
	reflbase::Variable<MO>,
	reflbase::get_pointer<MO>,
	none
> { };

template <>
struct op_get_pointer<none>
 : none
{ };

} // namespace _aux

template <typename X>
using get_pointer = eval<_aux::op_get_pointer<X>>;

} // namespace mirror

#endif //include guard

