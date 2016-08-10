/**
 * @file mirror/get_full_name.hpp
 * @brief Implementation of `get_full_name` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_FULL_NAME_1105240825_HPP
#define MIRROR_GET_FULL_NAME_1105240825_HPP

#include "get_base_name.hpp"
#include "get_scope.hpp"
#include "get_reflected_type.hpp"
#include "conditional.hpp"
#include "traits.hpp"
#include "concat.hpp"

namespace mirror {
namespace _aux {

template <typename X>
struct op_get_full_name;

template <typename MO, typename T>
struct do_get_full_name;

template <>
struct op_get_full_name<none>
 : empty_string
{ };

template <typename MO>
struct op_get_full_name<metaobject<MO>>
 : do_get_full_name<
	metaobject<std::meta::get_underlying_object_m<MO>>,
	get_reflected_type<metaobject<MO>>
>
{ };

template <>
struct do_get_full_name<none, none>
 : empty_string
{ };

template <typename MO, typename T>
struct do_get_full_name
 : concat<
	lazy_conditional<
		is_none<get_scope<MO>>,
		empty_string,
		concat<
			eval<do_get_full_name<get_scope<MO>, none>>,
			string<':',':'>
		>
	>,
	eval<op_get_base_name<MO>>
> { };

template <typename MO, typename T>
struct do_get_full_name<MO, T*>
 : concat<
	eval<do_get_full_name<MO, std::remove_pointer_t<T*>>>,
	string<'*'>
> { };

template <typename MO, typename T>
struct do_get_full_name<MO, T&>
 : concat<
	eval<do_get_full_name<MO, std::remove_reference_t<T&>>>,
	string<'&'>
> { };

template <typename MO, typename T>
struct do_get_full_name<MO, const T>
 : concat<
	eval<do_get_full_name<MO, T>>,
	string<' ','c','o','n','s','t'>
> { };

template <typename MO, typename T>
struct do_get_full_name<MO, volatile T>
 : concat<
	eval<do_get_full_name<MO, T>>,
	string<' ','v','o','l','a','t','i','l','e'>
> { };

} // namespace _aux

template <typename X>
using get_full_name = eval<_aux::op_get_full_name<X>>;

} // namespace mirror

#endif //include guard

