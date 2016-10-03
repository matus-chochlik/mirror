/**
 * @file mirror/is_private.hpp
 * @brief Implementation of the `is_private` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_PRIVATE_1105240825_HPP
#define MIRROR_IS_PRIVATE_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_private;

template <>
struct op_is_private<none>
 : none
{ };

template <typename MO>
struct op_is_private<metaobject<MO>>
 : lazy_conditional_c<
 	reflbase::RecordMember<MO> ||
	reflbase::Inheritance<MO>,
	reflbase::is_private<MO>,
	none
> { };

} // namespace _aux

template <typename X>
using is_private = eval<_aux::op_is_private<X>>;

} // namespace mirror

#endif //include guard

