/**
 * @file mirror/get_display_name.hpp
 * @brief Implementation of `get_display_name` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_DISPLAY_NAME_1105240825_HPP
#define MIRROR_GET_DISPLAY_NAME_1105240825_HPP

#include "metaobject.hpp"
#include "none.hpp"
#include "to_string.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_display_name;

template <typename MO>
struct op_get_display_name<metaobject<MO>>
 : to_string_if_c<
	reflbase::Named<MO>, char,
	reflbase::get_display_name<MO>
> { };

template <>
struct op_get_display_name<none>
 : empty_string
{ };

} // namespace _aux

template <typename X>
using get_display_name = eval<_aux::op_get_display_name<X>>;

} // namespace mirror

#endif //include guard

