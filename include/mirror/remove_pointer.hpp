/**
 * @file mirror/remove_pointer.hpp
 * @brief Implementation of `remove_pointer` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_REMOVE_POINTER_1105240825_HPP
#define MIRROR_REMOVE_POINTER_1105240825_HPP

#include "metaobject_ops.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_remove_pointer;

template <typename MO>
struct op_remove_pointer<metaobject<MO>>
 : conditional<
	bool_<reflbase::Typed<MO>>,
	metaobject<reflbase::get_type_m<MO>>,
	none
> { };

} // namespace _aux

template <typename X>
using get_remove_pointer = eval<_aux::op_remove_pointer<X>>;

} // namespace mirror

#endif //include guard

