/**
 * @file mirror/is_virtual.hpp
 * @brief Implementation of the `is_virtual` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_VIRTUAL_1105240825_HPP
#define MIRROR_IS_VIRTUAL_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_virtual;

template <>
struct op_is_virtual<none>
 : false_
{ };

template <typename MO>
struct op_is_virtual<metaobject<MO>>
 : lazy_conditional_c<
 	reflbase::Inheritance<MO>,
	reflbase::is_virtual<MO>,
	false_
> { };

} // namespace _aux

template <typename X>
using is_virtual = eval<_aux::op_is_virtual<X>>;

} // namespace mirror

#endif //include guard

