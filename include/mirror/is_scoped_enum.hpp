/**
 * @file mirror/is_scoped_enum.hpp
 * @brief Implementation of the `is_scoped_enum` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_SCOPED_ENUM_1105240825_HPP
#define MIRROR_IS_SCOPED_ENUM_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobject.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_scoped_enum;

template <>
struct op_is_scoped_enum<none>
 : false_
{ };

template <typename MO>
struct op_is_scoped_enum<metaobject<MO>>
 : lazy_conditional_c<
 	reflbase::Enum<MO>,
	reflbase::is_scoped_enum<MO>,
	false_
> { };

} // namespace _aux

template <typename X>
using is_scoped_enum = eval<_aux::op_is_scoped_enum<X>>;

} // namespace mirror

#endif //include guard

