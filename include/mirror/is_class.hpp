/**
 * @file mirror/is_class.hpp
 * @brief Implementation of the `is_class` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_CLASS_1105240825_HPP
#define MIRROR_IS_CLASS_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_class;

template <>
struct op_is_class<none>
 : false_
{ };

template <typename MO>
struct op_is_class<metaobject<MO>>
 : lazy_conditional_c<
 	reflbase::TagType<MO>,
	reflbase::is_class<MO>,
	false_
> { };

} // namespace _aux

template <typename X>
using is_class = eval<_aux::op_is_class<X>>;

} // namespace mirror

#endif //include guard

