/**
 * @file mirror/get_element.hpp
 * @brief Implementation of the `get_element` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_GET_ELEMENT_1105240825_HPP
#define MIRROR_GET_ELEMENT_1105240825_HPP

#include "int_const.hpp"
#include "range.hpp"
#include "string.hpp"
#include "identity.hpp"
#include "metaobject_ops.hpp"
#include "none.hpp"

namespace mirror {
namespace _aux {

template <typename X, typename Idx>
struct op_get_element;

template <typename MOS, typename Int, Int Idx>
struct op_get_element<metaobject_sequence<MOS>, int_const<Int, Idx>>
 : make_metaobject_if_c<
	(reflbase::get_size_v<MOS> > unsigned(Idx)),
	reflbase::get_element<MOS, Idx>
> { };

template <typename Idx>
struct op_get_element<none, Idx>
 : none
{ };

template <typename Idx>
struct op_get_element<empty_range, Idx>
 : none
{ };

template <typename H, typename ... T, typename Int>
struct op_get_element<range<H, T...>, int_const<Int, Int(0)>>
 : identity<H>
{ };

template <typename H, typename ... T, typename Int, Int I>
struct op_get_element<range<H, T...>, int_const<Int, I>>
 : op_get_element<range<T...>, int_const<Int, I-1>>
{ };

template <typename Idx>
struct op_get_element<empty_string, Idx>
 : none
{ };

template <typename Char, Char H, Char ... T, typename Int>
struct op_get_element<basic_string<Char, H, T...>, int_const<Int, Int(0)>>
 : int_const<Char, H>
{ };

template <typename Char, Char H, Char ... T, typename Int, Int I>
struct op_get_element<basic_string<Char, H, T...>, int_const<Int, I>>
 : op_get_element<basic_string<Char, T...>, int_const<Int, I-1>>
{ };

} // namespace _aux

template <typename X, typename Idx>
using get_element = eval<_aux::op_get_element<X, Idx>>;

} // namespace mirror

#endif //include guard

