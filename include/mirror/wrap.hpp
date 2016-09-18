/**
 * @file mirror/wrap.hpp
 * @brief Implementation of the `wrap_if_not_special` operation
 *
 * Copyright Matus Chochlik.
 * Distributed under the Boost Software License, Version 1.0.
 * See accompanying file LICENSE_1_0.txt or copy at
 *  http://www.boost.org/LICENSE_1_0.txt
 */

#ifndef MIRROR_WRAP_1105240825_HPP
#define MIRROR_WRAP_1105240825_HPP

#include "none.hpp"
#include "int_const.hpp"
#include "metaobject.hpp"
#include "string.hpp"
#include "range.hpp"
#include "identity.hpp"

namespace mirror {
namespace _aux {

template <typename T>
struct op_wrap_if_not_spec
{
	using type = identity<T>;
};

template <>
struct op_wrap_if_not_spec<none>
 : none
{ };

template <typename Int, Int I>
struct op_wrap_if_not_spec<int_const<Int, I>>
 : int_const<Int, I>
{ };

template <typename ... P>
struct op_wrap_if_not_spec<range<P...>>
 : range<P...>
{ };

template <typename Char, Char ... C>
struct op_wrap_if_not_spec<basic_string<Char, C...>>
 : basic_string<Char, C...>
{ };

template <typename O>
struct op_wrap_if_not_spec<metaobject<O>>
 : metaobject<O>
{ };

template <typename S>
struct op_wrap_if_not_spec<metaobject_sequence<S>>
 : metaobject_sequence<S>
{ };

} // namespace _aux

template <typename T>
using wrap_if_not_special = eval<_aux::op_wrap_if_not_spec<T>>;

} // namespace mirror

#endif //include guard

