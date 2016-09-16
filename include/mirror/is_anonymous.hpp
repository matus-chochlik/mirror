/**
 * @file mirror/is_anonymous.hpp
 * @brief Implementation of the `is_anonymous` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_ANONYMOUS_1105240825_HPP
#define MIRROR_IS_ANONYMOUS_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_anonymous;

template <>
struct op_is_anonymous<none>
 : true_
{ };

template <typename MO>
struct op_is_anonymous<metaobject<MO>>
 : lazy_conditional_c<
	reflbase::Named<MO>,
	reflbase::is_anonymous<MO>,
	true_
> { };

} // namespace _aux

template <typename X>
using is_anonymous = eval<_aux::op_is_anonymous<X>>;

} // namespace mirror

#endif //include guard

