/**
 * @file mirror/is_union.hpp
 * @brief Implementation of the `is_union` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_UNION_1105240825_HPP
#define MIRROR_IS_UNION_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_union;

template <>
struct op_is_union<none>
 : false_
{ };

template <typename MO>
struct op_is_union<metaobject<MO>>
 : lazy_conditional_c<
 	reflbase::TagType<MO>,
	reflbase::is_union<MO>,
	false_
> { };

} // namespace _aux

template <typename X>
using is_union = eval<_aux::op_is_union<X>>;

} // namespace mirror

#endif //include guard

