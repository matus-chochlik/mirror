/**
 * @file mirror/is_static.hpp
 * @brief Implementation of the `is_static` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_STATIC_1105240825_HPP
#define MIRROR_IS_STATIC_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_static;

template <>
struct op_is_static<none>
 : false_
{ };

template <typename MO>
struct op_is_static<metaobject<MO>>
 : lazy_conditional_c<
 	reflbase::Variable<MO>,
	reflbase::is_static<MO>,
	false_
> { };

} // namespace _aux

template <typename X>
using is_static = eval<_aux::op_is_static<X>>;

} // namespace mirror

#endif //include guard

