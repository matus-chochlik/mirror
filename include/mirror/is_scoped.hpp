/**
 * @file mirror/is_scoped.hpp
 * @brief Implementation of the `is_scoped` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_IS_SCOPED_1105240825_HPP
#define MIRROR_IS_SCOPED_1105240825_HPP

#include "int_const.hpp"
#include "none.hpp"
#include "metaobjects.hpp"
#include "conditional.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_is_scoped;

template <>
struct op_is_scoped<none>
 : true_
{ };

template <typename MO>
struct op_is_scoped<metaobject<MO>>
 : lazy_conditional_c<
 	std::meta::Enum<MO>,
	std::meta::is_scoped<MO>,
	bool_<std::meta::ScopeMember<MO>>
> { };

} // namespace _aux

template <typename X>
using is_scoped = eval<_aux::op_is_scoped<X>>;

} // namespace mirror

#endif //include guard

